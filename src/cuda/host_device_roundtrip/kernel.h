#pragma once

#include <cuda_runtime.h>
#include <thrust/host_vector.h>

float run_kernel_reduce_v1(thrust::host_vector<float>&);