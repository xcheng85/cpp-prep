#include <vector>
#include <string>
#include <numeric>

using namespace std;

// Input: nums = [1,2,3], target = 4
// Output: 7
// Explanation:
// The possible combination ways are:
// (1, 1, 1, 1)
// (1, 1, 2)
// (1, 2, 1)
// (1, 3)
// (2, 1, 1)
// (2, 2)
// (3, 1)
// Note that different sequences are counted as different combinations.

// where is the definition of sub-problems ?
// what is the range of sub-problems ? this will decide the size of dp array
// 1 + 3
// sub problem of 3
//

// 1 + (1 + 2)

// highly similar to word break and coin change
// All the elements of nums are unique.
class Solution
{
public:
    int combinationSum4(vector<int> &nums, int target)
    {
        // init to be impossible
        vector<int> dp(target + 1, std::numeric_limits<int>::max());
        dp[0] = 1;

        for (int i = 1; i <= target; i++)
        {
            int64_t numCombinations = 0;
            for (const auto &n : nums)
            {
                if(i - n >= 0 && dp[i - n] != std::numeric_limits<int>::max()) {
                    numCombinations += dp[i - n];
                }
            }
            dp[i] = numCombinations;
        }

        return dp[target];
    }
};