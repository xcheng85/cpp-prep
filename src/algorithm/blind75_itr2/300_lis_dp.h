// longest strictly increasing subsequence
// not consecutive each other --> rule out slide window

// 「子序列」和「子串」这两个名词的区别，子串一定是连续的，而子序列不一定是连续的

// nums = [1, 4, 3, 4, 2, 3]

// every iteration, the subproblem exists the all the less previous dp

#include <vector>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        // dp[1], include first char
        // dp[n-1], consider all the characters

        // dp[i] 表示以 nums[i] 这个数结尾的最长递增子序列的长度。
        // 最终结果（子序列的最大长度）应该是 dp 数组中的最大值。

        vector<int> dp(n, 1);
        for (int i = 0; i < n; ++i) {
            // compare all the previous characters
            for(int j = 0; j < i; ++j) {
                if(nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        
        return *max_element(dp.begin(), dp.end());
    }
};