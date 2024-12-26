#include <cmath>
#include <chrono>
#include <random>
#include <format>
#include <iostream>

// Thrust: The C++ Parallel Algorithms Library
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/mr/host_memory_resource.h>
#include <thrust/mr/device_memory_resource.h>
#include <thrust/mr/universal_memory_resource.h>
#include <thrust/mr/allocator.h>

#include <cuDevice.h>
#include <cuPredefines.h>
#include <kernel.h>

using namespace std::chrono;
using namespace core::cuda;

extern float run_kernel_reduce(thrust::host_vector<float> &);

int main(int argc, char **argv)
{
    selectDevice();

    thrust::host_vector<float> v1Host = {1, 2, 3, 4, 5};
    thrust::host_vector<float> v2Host = {1, 2, 3, 4, 5};
    //   - New `thrust::universal_host_pinned_memory_resource` for allocating memory
    //   that can be accessed from the host and the device but always resides in
    //   host memory (e.g. `cudaMallocHost`).

    /*! The host pinned memory resource for the CUDA system. Uses
     *  <tt>cudaMallocHost</tt> and wraps the result with \p
     *  cuda::universal_pointer.
     */

    thrust::host_vector<int, thrust::mr::stateless_resource_allocator<int, thrust::universal_host_pinned_memory_resource>> v1Device = v1Host;
    auto raw_ptr = thrust::raw_pointer_cast(v1Device.data());



    for (int i = 0; i < v1Device.size(); i++)
    {
        std::cout << v1Device[i] << std::endl;
    }

    float scaleFactor[NUM_SCALEFACTOR] = {2.0f};
    setScaleFactor(scaleFactor);

    //   Max Threads per block 1024.0
    // exceed 1024, fail the kernel
    auto res = runVectorAdd(v1Host, v2Host, 1024);
    // auto res = runVectorAdd(v1Host, v2Host, 2048);

    // CUDACHECK(cudaPeekAtLastError());

    // wait for gpu to finish
    // like fence
    // device synchronization
    cudaDeviceSynchronize();

    for (int i = 0; i < res.size(); i++)
    {
        std::cout << res[i] << std::endl;
    }

    return 0;
}