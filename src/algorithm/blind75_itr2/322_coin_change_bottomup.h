class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        vector<int> dp(amount + 1, numeric_limits<int>::max());

        dp[0] = 0;

        for (int i = 1; i < dp.size(); i++)
        {
            for (int coin : coins)
            {
                // 子问题无解，跳过
                if (i - coin < 0)
                {
                    continue;
                }
                // overflow:  1 + dp[i - coin] ? 
                if(dp[i - coin] != numeric_limits<int>::max()) {
                    dp[i] = min(dp[i], 1 + dp[i - coin]);
                }
            }
        }

        if(dp[amount] == numeric_limits<int>::max())  {
            return -1;
        }
        return dp[amount] ;
    }
};