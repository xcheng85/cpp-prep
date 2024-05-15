#include <algorithm>
#include <thrust/device_vector.h>
#include <mathUtils.h>
#include "kernel.h"

using namespace core::cuda;

#if defined(SHARED_MEMORY)
// output's size is numThreadBlocks
// each thread block uses shared_memory to compute 1 value and write it to the output
__global__ void kernel_reduce_pass(float *__restrict input, float *__restrict output, int N)
{
    // to use shared_memory, focus on threadIdx
    // shared_memory is per-thread block.
    // how many shared_memory resources are used ?
    // 48K per thread block: 48 * 1024 > 256 * 4 byte
    // numThreads * float

    // dynamic shared memory allocation, size is provided at 3rd param in the kernal launch
    // static shared memory allocation ex: __shared__ float partialsum[256];
    extern __shared__ float partialsum[];

    int globalThreadId = blockDim.x * blockIdx.x + threadIdx.x;
    int localThreadId = threadIdx.x;
    // stride to make unique access to global memory
    int stride = gridDim.x * blockDim.x;
    partialsum[localThreadId] = 0.f;
    for (int k = globalThreadId; k < N; k += stride)
    {
        partialsum[localThreadId] += input[k];
    }
    // partialsum[] are all filled
    // https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html
    __syncthreads();

    // partialsum[localThreadId] are ready to reduce: assume 256 threads in a block
    // [lowhalf, highhalf]
    // [lowhalf + highhalf, highhalf]: lowhalf is updated

    // if blockDim is not power of 2
    // 40 SM
    // Warp-size: 32
    // each SM: pow(2, m) * warp-size
    // Max Threads per Block: 1024
    // SM: m * warp

    auto dt = pow2ceil(blockDim.x) / 2;

    while (dt > 0)
    {
        // extra guard due to ceil op
        if (localThreadId < dt && localThreadId + dt < blockDim.x)
        {
            partialsum[localThreadId] += partialsum[localThreadId + dt];
        }
        // ensure all write is done, need to use updated value in the next while-iteration
        __syncthreads();
        dt /= 2;
    }

    // partialsum[0] is the sum of all this thread block
    if (localThreadId == 0)
    {
        output[blockIdx.x] = partialsum[0];
    }
}

#elif defined(WARP_OP)
// output's size is numThreadBlocks
// each thread block uses shared_memory to compute 1 value and write it to the output
__global__ void kernel_reduce_pass(float *__restrict input, float *__restrict output, int N)
{
    // to use shared_memory, focus on threadIdx
    // shared_memory is per-thread block.
    // how many shared_memory resources are used ?
    // 48K per thread block: 48 * 1024 > 256 * 4 byte
    // numThreads * float

    extern __shared__ float partialsum[];

    int globalThreadId = blockDim.x * blockIdx.x + threadIdx.x;
    int localThreadId = threadIdx.x;
    // stride to make unique access to global memory
    int stride = gridDim.x * blockDim.x;
    partialsum[localThreadId] = 0.f;
    for (int k = globalThreadId; k < N; k += stride)
    {
        partialsum[localThreadId] += input[k];
    }
    // partialsum[] are all filled
    // https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html
    __syncthreads();

    // partialsum[localThreadId] are ready to reduce: assume 256 threads in a block
    // [lowhalf, highhalf]
    // [lowhalf + highhalf, highhalf]: lowhalf is updated

    // if blockDim is not power of 2
    // 40 SM
    // Warp-size: 32
    // each SM: pow(2, m) * warp-size
    // Max Threads per Block: 1024
    // SM: m * warp

    // dt: 256, 128, ..., 0
    // assuming blockDim is not too big
    auto dt = pow2ceil(blockDim.x) / 2;
    // loop unrolling optimization
    // the if condition protected the read after write race condition.
    
    if (localThreadId < 256 && localThreadId + 256 < blockDim.x)
    {
        // no read-write race condition here,
        // no one is writing to partialsum[localThreadId + 256] at this stage
        partialsum[localThreadId] += partialsum[localThreadId + 256];
    }
    __syncthreads();
    if (localThreadId < 128)
    {
        // no read-write race condition here,
        partialsum[localThreadId] += partialsum[localThreadId + 128];
    }
    __syncthreads();
    if (localThreadId < 64)
    {
        // no read-write race condition here,
        partialsum[localThreadId] += partialsum[localThreadId + 64];
    }
    __syncthreads();
    if (localThreadId < 32)
    {
        // no read-write race condition here,
        partialsum[localThreadId] += partialsum[localThreadId + 32];
    }
    __syncthreads();

    // access is within warp-size: 32
    if (localThreadId < 16)
    {
        // no read-write race condition here,
        partialsum[localThreadId] += partialsum[localThreadId + 16];
    }
    __syncwarp();
    if (localThreadId < 8)
    {
        // no read-write race condition here,
        partialsum[localThreadId] += partialsum[localThreadId + 8];
    }
    __syncwarp();
    if (localThreadId < 4)
    {
        // no read-write race condition here,
        partialsum[localThreadId] += partialsum[localThreadId + 4];
    }
    __syncwarp();
    if (localThreadId < 2)
    {
        // no read-write race condition here,
        partialsum[localThreadId] += partialsum[localThreadId + 2];
    }
    __syncwarp();

    if (localThreadId == 0)
    {
        output[blockIdx.x] = partialsum[0] + partialsum[1];
    }
}

#endif

float run_kernel_reduce(thrust::host_vector<float> &vHost)
{
    auto N = vHost.size();
    thrust::device_vector<float> vDeviceInput(N);
    // copy data from host to device through PCI-bus
    vDeviceInput = vHost;
    auto numThreadsInBlock = 256;
    auto numThreadBlocks = 128;
    // each thread block will write to one value to this array
    thrust::device_vector<float> vDeviceOutput(numThreadBlocks);

    // third parameter: shared_memory size in bytes
    auto sharedMemorySizeInBytes = numThreadsInBlock * sizeof(float);
    kernel_reduce_pass<<<numThreadBlocks, numThreadsInBlock, sharedMemorySizeInBytes>>>(
        vDeviceInput.data().get(),
        vDeviceOutput.data().get(),
        N);
    // pass 2:
    // ping-pong, output of pass1 became input of pass2.
    // input's size: numThreadBlocks of pass1
    sharedMemorySizeInBytes = numThreadBlocks * sizeof(float);
    kernel_reduce_pass<<<1, numThreadBlocks, sharedMemorySizeInBytes>>>(
        vDeviceOutput.data().get(),
        vDeviceInput.data().get(),
        numThreadBlocks);

    // waiting for all the device op done.
    cudaDeviceSynchronize();
    // device -> host by demand, only one element
    auto result = vDeviceInput[0];
    return result;
}