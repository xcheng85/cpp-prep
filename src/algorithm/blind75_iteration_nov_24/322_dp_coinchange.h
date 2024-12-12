class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, std::numeric_limits<int>::max());
        dp[0] = 0;
        for(int i = 1; i <= amount; ++i) {
            for(const auto& c : coins) {
                int change = i - c;
                if(change < 0 || dp[change] == std::numeric_limits<int>::max())
                    continue;
                
                dp[i] = std::min(dp[i], dp[change] + 1);
            }
        }
        if(dp[amount] == std::numeric_limits<int>::max())
            return -1;
        return dp[amount];
    }
};