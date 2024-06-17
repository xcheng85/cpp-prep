// Input  : x = 12, y = 15
// Output : 12
// 12 & 13 & 14 & 15 = 12
// Input  : x = 10, y = 20
// Output : 0

// translate this question to : common prefix bits problem
// 9, 10, 11, 12

// 9: 1001
//10: 1010
//11: 1011
//12: 1100

// common prefix is 1
// shift three bits than all of them is equal, 9 and 12 will equal

// 8, 12
// 0100
// 1100

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int numBitsShifted = 0;
        while(left != right) {
            left >>= 1;
            right >>= 1;
            ++numBitsShifted;
        }
        return left << numBitsShifted;
    }
};


class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
            // Initialize result as the first number
        int res = left;

        // Traverse from x+1 to y
        for (int i = left + 1; i <= right; i++)
        {
            res = res & i;
        }

        return res;
    }
};

int rangeBitwiseAnd(int m, int n) {
    int a = 0;
    while(m != n) {
        m >>= 1;
        n >>= 1;
        a++;
    }
    return m<<a; 
}


class Solution
{
public:
    // 0 <= left <= right <= 2^31 - 1
    int rangeBitwiseAnd(int left, int right)
    {
        // Initialize result as the first number
        int res = left;

        // Traverse from x+1 to y
        for (int i = left + 1; i <= right; i++)
        {
            res = res & i;
        }

        return res;
    }

    int mostSignificantBit(int n)
    {
        int msb_p = -1;
        while (n)
        {
            n = n >> 1;
            msb_p++;
        }
        return msb_p;
    }
};