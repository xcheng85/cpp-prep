#pragma once

#include <cuda_runtime.h>

using namespace std;

namespace core::cuda
{
    __device__ int pow2ceil(int i);
}