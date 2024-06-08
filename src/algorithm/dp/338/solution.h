
// Input: n = 5
// Output: [0,1,1,2,1,2]
// Explanation:
// 0 --> 0
// 1 --> 1

// 2 --> 10  1    number of 1: 1
// 3 --> 11       number of 1: 1 + 1
// 4 --> 100   2 * 2
// 5 --> 101   /2 = 2
// 6 --> 110   /2 = 3 : 11
// 7 --> 111   3 * 2 + 1
// 8 ---> 1000

#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> countBits(int n)
    {
        // bottom up
        vector<int> dp(n + 1);
        dp[0] = 0;
        if (n >= 1)
            dp[1] = 1;

        for (int i = 2; i <= n; ++i)
        {
            auto multi = i / 2;
            auto numberofOne = dp[multi];
            auto mod = i % 2;
            // number of 1
            if (mod)
            {
                ++numberofOne;
            }
            dp[i] = numberofOne;
        }
        return dp;
    }
};