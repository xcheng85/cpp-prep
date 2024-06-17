// i & (i-1), remove last 1 bit
// a number: power of 2 only have one 1 bit, after remove rightmost 1 bit, it will be 0

int highestPowerof2(int n)
{
    int res = 0;
    for (int i = n; i >= 1; i--)
    {
        // if i = 1000
        // i-1 = 0111
        if ((i & (i - 1)) == 0)
        {
            res = i;
            break;
        }
    }
    return res;
}

int highestPowerof2(unsigned int n)
{
    // Invalid input
    if (n < 1)
        return 0;
    int res = 1;
    // Try all powers starting from 2^1

    for (int leftmovebit = 0; leftmovebit < 8 * sizeof(unsigned int); ++leftmovebit)
    {
        int curr = 1 << leftmovebit;
        // If current power is more than n, break
        if (curr > n)
            break;
        // update result
        res = curr;
    }
    return res;
}

int highestPowerof2(int n)
{
   int p = (int)log2(n);
   return (int)pow(2, p); 
}

long largest_power(long N)
{
    // changing all right side bits to 1.
    N = N | (N >> 1);
    N = N | (N >> 2);
    N = N | (N >> 4);
    N = N | (N >> 8);
    N = N | (N >> 16);
    return (N + 1) >> 1;
}

int main()
{
}