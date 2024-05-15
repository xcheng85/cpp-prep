
#include <mathUtils.h>

namespace core::cuda
{
    __device__ int pow2ceil(int n)
    {
        int pow2 = 1 << (31 - __clz(n));
        if (n > pow2)
            pow2 = (pow2 << 1);
        return pow2;
    }
}