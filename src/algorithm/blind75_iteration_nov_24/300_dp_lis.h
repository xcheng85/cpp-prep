class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        // contain how many char
        // every one at least itself
        vector<int> dp(n + 1, 1);
        // 1 <= nums.length <= 2500
        for(int i = 2; i <= n; i++) {
            // how to update subproblem based on previous smaller subproblems, try all the possibilities
            // all the previous subproblems. 
            for(int j = 1; j < i; j++) {
                // compare values
                if(nums[i - 1] > nums[j - 1]) {
                    //cout << nums[i - 1] << ">" << nums[j - 1] << endl;
                    //cout << "max(" << dp[i] << ", " << dp[j] << "+1)" <<endl; 
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
        }
        // this is wrong: return dp[n];
        return *std::max_element(dp.begin(), dp.end());
    }
};