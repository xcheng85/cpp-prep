#pragma once

#include <cuda_runtime.h>

// shared function by host and device
// sin(x): at x
// numTerms: taylor seris (to do with approximation)
__host__ __device__ inline float sinAtX(float x, int numTerms)
{
    // 3, 5, 7, 9
    // 2 * 3, 4 * 5, 6 * 7
    float xx = x * x;
    float currentTerm{x};
    float sum{x};

    for (int i{1}; i < numTerms; ++i)
    {
        currentTerm *= (-1 * xx / (2 * i * (2 * i + 1)));
        sum += currentTerm;
    }
    return sum;
}

float run_kernel_integrate(int blocks, int threadsInBlock, int numSteps, int numTerms, float stepSize);