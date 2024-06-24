// 1. mask to read
//  2. mask to write
//  3. |= write to a bit

uint32_t reverseBits(uint32_t n)
{
    unsigned int writemask = 1 << 31, res = 0;
    for (int i = 0; i < 32; ++i)
    {
        if (n & 1)
            res |= writemask;
        writemask >>= 1;
        n >>= 1;
    }
    return res;
}