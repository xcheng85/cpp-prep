#include <algorithm>
#include <thrust/device_vector.h>
#include "kernel.h"

// cuda kernel function always return void, pass in pointer to write
// reduce pair per dt: pass1
// reduce pair per dt/2: pass2
__global__ void kernel_reduce_pass(float *x, int dt)
{
    int globalThreadId = blockDim.x * blockIdx.x + threadIdx.x;
    x[globalThreadId] += x[globalThreadId + dt];
}

float run_kernel_reduce_v1(thrust::host_vector<float> &vHost)
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