#include <algorithm>
#include <assert.h>
#include <thrust/device_vector.h>
#include <cuPredefines.h>
#include "kernel.h"

// v1: to be overwritten
__global__ void vectorAdd(float *v1, float *v2, int N)
{
    int globalThreadId = blockDim.x * blockIdx.x + threadIdx.x;
    // two global memory access
    // debug in kernel
    if (globalThreadId < N)
    {
        printf("calling kernel: %d\n", globalThreadId);
        v1[globalThreadId] += v2[globalThreadId];
    }
}

thrust::host_vector<float> runVectorAdd(thrust::host_vector<float> &v1,
                                        thrust::host_vector<float> &v2,
                                        int numThreadsInBlock)
{
    thrust::host_vector<float> res;
    assert(v1.size() == v2.size());
    auto N = v1.size();
    thrust::device_vector<float> v1Device(N), v2Device(N);

    // copy data from host to device through PCI-bus
    // deep down using cudaMemcpy

    v1Device = v1;
    v2Device = v2;

    float *ptr1 = thrust::raw_pointer_cast(&v1Device[0]);
    float *ptr2 = thrust::raw_pointer_cast(&v2Device[0]);

    cudaEvent_t start, stop;
    CUDACHECK(cudaEventCreate(&start));
    CUDACHECK(cudaEventCreate(&stop));

    // stream 0
    cudaEventRecord(start, 0);
    int numBlocksPerGrid = (N + numThreadsInBlock - 1) / numThreadsInBlock;
    vectorAdd<<<numBlocksPerGrid, numThreadsInBlock>>>(ptr1, ptr2, N);
    cudaEventRecord(stop, 0);
    // Waits for an event to complete.
    cudaEventSynchronize(stop);

    float elapsedTimeInMs;
    cudaEventElapsedTime(&elapsedTimeInMs, start, stop);

    std::cout << "kernel runs: " << elapsedTimeInMs << " ms " << std::endl;

    res = v1Device;
    return res;
}
