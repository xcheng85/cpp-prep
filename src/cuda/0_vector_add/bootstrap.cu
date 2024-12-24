#include <cmath>
#include <chrono>
#include <random>
#include <format>
#include <iostream>

// Thrust: The C++ Parallel Algorithms Library
#include <thrust/host_vector.h>
#include <cuDevice.h>
#include <cuPredefines.h>
#include <kernel.h>

using namespace std::chrono;
using namespace core::cuda;

extern float run_kernel_reduce(thrust::host_vector<float> &);

int main(int argc, char **argv)
{
    checkDevice();

    thrust::host_vector<float> v1Host = {1, 2, 3, 4, 5};
    thrust::host_vector<float> v2Host = {1, 2, 3, 4, 5};

    auto res = runVectorAdd(v1Host, v2Host, 1, 5);

    CUDACHECK(cudaPeekAtLastError());

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