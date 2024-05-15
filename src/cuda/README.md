# All about CUDA

## Arch

CPU vs GPU ? 

### GPU arch
32 thread group = warp

io, FP64, and SFUs are shared by warp

SM: m * warp 
SM occupancies are limited by shared memory consumption
SM has pool of shared memory and are divided by current residential thread blocks

GPU: n * SM 

Max number threads per block: prop.maxThreadsPerBlock

## Configure in Ubuntu 
gcc 14 does not work with nvcc

## concept
1. shared function between host and device
2. kernel: no reference, pass in address to write
3. any c++ classes or structs passed to a kernel must have __device__ versions of all their member functions. Need example

## Problems

### 1. When kernel launch fail ? 

1. requested shared memory > SM has

### 2. __syncthreads vs __syncwarps
thread subgroup >= warp size(query), sync across warps

__syncwarps requirs for new gpu, due to threads in same warp could have different program counter.


## References

1. https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html

## 2. Warp-level programming

## 3. cooperative_groups 
header:
namespace: 
benifits: partition threadBlock into different size for granularity

tiled_partition

## 4. cuda + template metaprogramming