#include <thrust/device_vector.h>
#include "kernel.h"

// cuda kernel function always return void, pass in pointer to write
__global__ void kernel_integrate(
    float *sumArrayW, int numSteps, int numTerms, float stepSize)
{
    // threads in a warp and sm are continuous access the memory
    // gridDim.xyz: number of thread blocks in the grid
    // blockDim.xyz: number of threads in a block in three direction
    // blockIdx.x: [0, gridDim.x - 1];
    // gridDim.x * blockDim.x: all the number of threads in x direction.

    auto step = blockIdx.x * blockDim.x + threadIdx.x;

    if (step < numSteps)
    {
        int x = stepSize * step;
        sumArrayW[x] = sinAtX(x, numTerms);
    }
}

float run_kernel_integrate(int numBlocks, int numThreadsInBlock, int numSteps, int numTerms, float stepSize)
{
    // gpu vector can only be compiled in cuda
    thrust::device_vector<float> sumArrayW(numSteps);
    float *ptr = thrust::raw_pointer_cast(&sumArrayW[0]);

    // 1D grid
    // how many threads: numThreadsInBlock * numBlocks
    kernel_integrate<<<numBlocks, numThreadsInBlock>>>(
        ptr,
        numSteps,
        numTerms,
        stepSize);

    // reduce is host runnable
    auto sum = thrust::reduce(sumArrayW.begin(), sumArrayW.end());

    return sum;
}