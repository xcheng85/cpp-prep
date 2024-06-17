#include <cstdint>

class Solution
{
public:
    // 1. get the last bit: n & 0x1
    //    get the 2nd last bet: (n >> 1) & 0x1
    // 2. write to a certain ith bit: res |= 1<<i

    // 0, 31 1 << 31
    // 1, 30
    // 2, 29 1 << 29

    // 31, 0

    uint32_t reverseBits(uint32_t n)
    {
        unsigned int mask = 1 << 31, res = 0;
        for (int i = 0; i < 32; ++i)
        {
            if (n & 1)
                res |= mask;
            mask >>= 1;
            n >>= 1;
        }
        return res;
    }

    // get the last bit mast 0x01   write to and then left shift
    // get the 2nd last bit, 0x10
    // get the 3rd last bit, 0x100

    uint32_t reverseBits(uint32_t n)
    {
        uint32_t mask = 1, ret = 0;
        for (int i = 0; i < 32; ++i)
        {
            ret <<= 1;
            if (mask & n)
                ret |= 1;
            mask <<= 1;
        }
        return ret;
    }
};