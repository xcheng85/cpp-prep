#pragma once

#include <cuda_runtime.h>
#include <thrust/host_vector.h>

thrust::host_vector<float> runVectorAdd(
    thrust::host_vector<float> &v1, 
    thrust::host_vector<float> &v2, 
    int threadsInBlock // SM / warpsize
);

#define NUM_SCALEFACTOR 1

void setScaleFactor(const float* f);
