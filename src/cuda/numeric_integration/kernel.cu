#include <thrust/device_vector.h>
#include "kernel.h"

// cuda kernel function always return void, pass in pointer to write
__global__ void kernel_integrate(
    float *sumArrayW, int numSteps, int numTerms, float stepSize)
{
    auto step = blockIdx.x * blockDim.x + threadIdx.x;
    if (step < numSteps)
    {
        int x = stepSize * step;
        sumArrayW[x] = sinAtX(x, numTerms);
    }
}

void run_kernel_integrate(int blocks, int threadsInBlock, int numSteps, int numTerms, float stepSize)
{
    // gpu vector can only be compiled in cuda
    thrust::device_vector<float> sumArrayW(numSteps);
    float *ptr = thrust::raw_pointer_cast(&sumArrayW[0]);

    kernel_integrate<<<blocks, threadsInBlock>>>(
        ptr,
        numSteps,
        numTerms,
        stepSize);
    return;
}