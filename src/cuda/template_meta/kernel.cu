#include <concepts>
#include <cooperative_groups.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <kernel.h>

using namespace cooperative_groups;

// each launched kernel (1D case) has number of threads in total
// gridDim.x * blockDim.x

// assuming input size >> number of threads launched in kernel
// pass1: reduce everything beyond (gridDim.x * blockDim.x) to the (gridDim.x * blockDim.x)
// pass2: reduce everything beyond (blockDim.x) to the result of thread group0.
__device__ float reducePass1(float *__restrict input, int n)
{
    float sum = 0;

    // vector memory access
    for (int i = blockIdx.x * blockDim.x + threadIdx.x;
         i < n / 4;
         i += blockDim.x * gridDim.x)
    {
        float4 in = ((float4 *)input)[i];
        sum += in.x + in.y + in.z + in.w;
    }
    return sum;
}

// tg is provided runtime
__device__ float reducePass2(thread_group tg, float *__restrict outputSM, float reduceResultFromPass1PerThread)
{
    // goal in pass2, is reduce everything to the tg granulariy
    int threadIdInTg = tg.thread_rank();
    int threadGroupSize = tg.size();

    for (int dt = threadGroupSize / 2; dt > 0; dt /= 2)
    {
        // shared memory is isolated per tg.
        outputSM[threadIdInTg] = reduceResultFromPass1PerThread;
        // cannot use warpsync here due to size could > 32.
        // ensure all the output[threadIdInTg] is written for all threads
        tg.sync();

        if (threadIdInTg < dt)
        {
            // is a copy anyway
            reduceResultFromPass1PerThread += outputSM[threadIdInTg + dt];
        }
        // make sure read of outputSM is done before overwritten in the next for iteration
        tg.sync();
    }
    return reduceResultFromPass1PerThread;
}

// template-meta programming: compiler optimzation
template <typename TG>
concept IsThreadGroup = requires(TG x) {
    x.thread_rank();
    x.size();
};

// template <std::integral T>
// constexpr bool isWarpSize = (T == 32);

// integral concept
// created from the type_traits value
// template< class T >
// concept integral = std::is_integral_v<T>;
template <typename T>
concept IsWarpSizeThreadGroup = std::integral<T>;
//&& isWarpSize<T>;

template <int TG>
__device__ float reduceWithinThreadGroup(thread_block_tile<TG> tg, float reduceResultFromPass1PerThread)
{
    // goal in pass2, is reduce everything to the tg granulariy
    int threadGroupSize = tg.size();

// threadGroupSize is known in compile time
// with shfl_down, no need to use shared memory
#pragma unroll
    for (int dt = threadGroupSize / 2; dt > 0; dt /= 2)
    {
        // Now if the TG is in warp-size granularity
        // which is guarded by the c++ concept
        // https://developer.nvidia.com/blog/faster-parallel-reductions-kepler/
        reduceResultFromPass1PerThread += tg.shfl_down(reduceResultFromPass1PerThread, dt);
    }
    return reduceResultFromPass1PerThread;
}

#if defined(TILED_PARTITION)
// indent is needed
#if defined(TEMPLATE_META)
template <int TileSize>
__global__ void kernel_reduce(float *__restrict input, float *__restrict output, int n)
{
    float sumGlobalThread = reducePass1(input, n);
    // cannot do this + template
    // thread_group tg = this_thread_block();
    thread_block_tile<TileSize> tile = tiled_partition<TileSize>(this_thread_block());
    int sumTile = reduceWithinThreadGroup<TileSize>(tile, sumGlobalThread);

    if (tile.thread_rank() == 0)
    {
        // number of atomicAdd will more after the tiled_partition
        // every warp-size
        printf("[template metaprogramming]: atomicAdd: %d:\n", blockIdx.x * blockDim.x + threadIdx.x);
        atomicAdd(output, sumTile);
    }
}
#else
__global__ void kernel_reduce(float *__restrict input, float *__restrict output, int n)
{
    float sumGlobalThread = reducePass1(input, n);

    extern __shared__ float sharedmemory[];

    thread_group tg = this_thread_block();

    // divide within thread block by warp-size
    auto tileIdx = tg.thread_rank() / 32;
    // share memory size remains unchanged.
    // but reference with offset
    float *sharedmemory32 = &sharedmemory[32 * tileIdx];

    // tiled_partition return same type: thread_group, just size is 32, known compile time
    thread_group tg32 = tiled_partition(tg, 32);

    // for each threadBlock, only the first thread in that block has the final sum per block
    float sumBlockThread = reducePass2(tg32, sharedmemory32, sumGlobalThread);

    if (tg32.thread_rank() == 0)
    {
        // number of atomicAdd will more after the tiled_partition
        // every warp-size
        printf("atomicAdd: %d:\n", blockIdx.x * blockDim.x + threadIdx.x);
        atomicAdd(output, sumBlockThread);
    }
}
#endif
#else
__global__ void kernel_reduce(float *__restrict input, float *__restrict output, int n)
{
    float sumGlobalThread = reducePass1(input, n);

    extern __shared__ float sharedmemory[];

    thread_group tg = this_thread_block();

    // for each threadBlock, only the first thread in that block has the final sum per block
    float sumBlockThread = reducePass2(tg, sharedmemory, sumGlobalThread);

    if (tg.thread_rank() == 0)
    {
        // number of printf should = numThreadBlocks;
        printf("atomicAdd: %d:\n", blockIdx.x * blockDim.x + threadIdx.x);
        atomicAdd(output, sumBlockThread);
    }
}
#endif

float run_kernel(thrust::host_vector<float> &vHost)
{
    auto N = vHost.size();
    thrust::device_vector<float> vDeviceInput(N);
    // copy data from host to device through PCI-bus
    vDeviceInput = vHost;
    auto numThreadsInBlock = 64;
    auto numThreadBlocks = 4;

    thrust::device_vector<float> vDeviceOutput(1);
    auto sharedMemorySizeInBytes = numThreadsInBlock * sizeof(float);

#ifdef TEMPLATE_META
    kernel_reduce<32><<<numThreadBlocks, numThreadsInBlock>>>(
        vDeviceInput.data().get(),
        vDeviceOutput.data().get(),
        N);
#else
    kernel_reduce<<<numThreadBlocks, numThreadsInBlock, sharedMemorySizeInBytes>>>(
        vDeviceInput.data().get(),
        vDeviceOutput.data().get(),
        N);
#endif

    // gpu->cpu
    return vDeviceOutput[0];
}