#include <algorithm>
#include <thrust/device_vector.h>
#include "kernel.h"

#if defined(V1)
// v2 is ~ 3 seconds in a2000
// cuda kernel function always return void, pass in pointer to write
// reduce pair per dt: pass1
// reduce pair per dt/2: pass2
__global__ void kernel_reduce_pass(float *x, int dt)
{
    int globalThreadId = blockDim.x * blockIdx.x + threadIdx.x;
    // two global memory access
    x[globalThreadId] += x[globalThreadId + dt];
}

float run_kernel_reduce(thrust::host_vector<float> &vHost)
{
    auto N = vHost.size();
    thrust::device_vector<float> vDevice(N);
    // copy data from host to device through PCI-bus
    vDevice = vHost;

    // iteration passes
    auto dt = N / 2;
    while (dt > 0)
    {
        // considering warp size
        auto numThreadsInBlock = std::min(256ul, dt);
        auto numThreadBlocks = std::max(dt / 256, 1ul);
        kernel_reduce_pass<<<numThreadBlocks, numThreadsInBlock>>>(vDevice.data().get(), dt);
        dt /= 2;
    }
    // waiting for all the device op done.
    cudaDeviceSynchronize();
    // device -> host by demand, only one element
    auto result = vDevice[0];
    return result;
}

#elif defined(V2)
// v2 is less than 2 seconds in a2000
// N for boundary check
__global__ void kernel_reduce_pass(float *x, int N)
{
    int globalThreadId = blockDim.x * blockIdx.x + threadIdx.x;
    float tsum = 0.0f;
    // this stride guarenteed no threads will overlap.
    // stride: max range kernel cover.
    // if N > stride, do sum here and stored in the lowerst offset.
    int stride = gridDim.x * blockDim.x;
    for (int k = globalThreadId; k < N; k += stride)
    {
        tsum += x[k];
    }
    x[globalThreadId] = tsum;
}

float run_kernel_reduce(thrust::host_vector<float> &vHost)
{
    auto N = vHost.size();
    thrust::device_vector<float> vDevice(N);
    // copy data from host to device through PCI-bus
    vDevice = vHost;

    auto numThreadsInBlock = 256;
    auto numThreadBlocks = 128;

    kernel_reduce_pass<<<numThreadsInBlock, numThreadBlocks>>>(vDevice.data().get(), N);
    // after pass1: all the partial sum result is in range: [0, numThreadsInBlock * numThreadBlocks]
    // all the threads should be passed to 32 warp engine
    // stride: 1 * numThreadsInBlock
    // numThreadBlocks elements are partial summed in pass2
    kernel_reduce_pass<<<1, numThreadsInBlock>>>(vDevice.data().get(), numThreadsInBlock * numThreadBlocks);
    // pass3: aggregate: numThreadsInBlock
    // stride is 1
    kernel_reduce_pass<<<1, 1>>>(vDevice.data().get(), numThreadsInBlock);
    // waiting for all the device op done.
    cudaDeviceSynchronize();
    // device -> host by demand, only one element
    auto result = vDevice[0];
    return result;
}

#endif
