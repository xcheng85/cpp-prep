#include <algorithm>
#include <assert.h>
#include <thread>
#include <chrono>
#include <thrust/device_vector.h>
#include <cuPredefines.h>
#include "kernel.h"

using namespace std::chrono;

__constant__ float constScale[NUM_SCALEFACTOR];

void setScaleFactor(const float *coeff)
{
    cudaMemcpyToSymbol(constScale, coeff, NUM_SCALEFACTOR * sizeof(float));
}

// v1: to be overwritten
__global__ void vectorAdd(float *v1, float *v2, int N)
{
    extern __shared__ float intermediates[];
    // only supports 1d
    int globalThreadId = blockDim.x * blockIdx.x + threadIdx.x;
    // two global memory access
    // debug in kernel
    if (globalThreadId < N)
    {
        printf("calling kernel: %d\n", globalThreadId);
        v1[globalThreadId] += v2[globalThreadId];
        v1[globalThreadId] *= constScale[0];
    }
}

thrust::host_vector<float> runVectorAdd(thrust::host_vector<float> &v1,
                                        thrust::host_vector<float> &v2,
                                        dim3 numThreadsInBlock)
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
    cudaEventCreate(&start);
    auto err = cudaGetLastError();
    if (err != cudaSuccess)
    {
        std::cerr << cudaGetErrorString(err) << std::endl;
    }
    cudaEventCreate(&stop);
    // stream 0
    cudaEventRecord(start, 0);
    dim3 numBlocksPerGrid((N + numThreadsInBlock.x - 1) / numThreadsInBlock.x);

    // 2d
    // dim3 numBlocksPerGrid(32, 32, 1);
    int blockSize = 0;
    int numBlocks = 0;
    cudaOccupancyMaxPotentialBlockSize(&numBlocks, &blockSize, vectorAdd);
    // Potential: 768, 152
    std::cout << "Potential: " << blockSize << ", " << numBlocks << std::endl;

    vectorAdd<<<numBlocksPerGrid, numThreadsInBlock, sizeof(float) * N>>>(ptr1, ptr2, N);
    // GPU kernels are asynchronous with host by default
    int numItr = 5;
    while (numItr--)
    {
        std::cout << "cpu itr: " << numItr << std::endl;
        std::this_thread::sleep_for(1s);
    }

    cudaEventRecord(stop, 0);
    // Waits for an event to complete.
    cudaEventSynchronize(stop);

    float elapsedTimeInMs;
    cudaEventElapsedTime(&elapsedTimeInMs, start, stop);

    std::cout << "kernel runs: " << elapsedTimeInMs << " ms " << std::endl;

    res = v1Device;
    return res;
}
