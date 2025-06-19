#include <vector>

// one transaction

// ith day, k=1 transaction, 0, not own stock

using namespace std;

class Solution
{
public:
    // state: dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + prices[i])
    //                          do nothing      sell

    // key is dp[i-1][0][0] we know it is 0, key

    // state: dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - prices[i])
    //                          do nothing      buy

    // using DayState = std::array<std::array<int,2>, 2>;
    class Solution
    {
    public:
        // state: dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + prices[i])
        //                          do nothing      sell

        // state: dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - prices[i])
        //                          do nothing      buy

        int maxProfit(vector<int> &prices)
        {
            int n = prices.size();
            vector<std::array<std::array<int, 2>, 2>> dp(n + 1);
            dp[0][0][0] = 0;
            dp[0][0][1] = std::numeric_limits<int>::min();
            dp[0][1][0] = std::numeric_limits<int>::min();
            dp[0][1][1] = std::numeric_limits<int>::min();

            for (int i = 1; i <= n; i++)
            {
                dp[i][1][0] = max(dp[i - 1][1][0], dp[i - 1][1][1] + prices[i - 1]);
                dp[i][1][1] = max(dp[i - 1][1][1], dp[i - 1][0][0] - prices[i - 1]);

                // std::cout << "dp[i][1][0]: " << dp[i][1][0] << std::endl;
                // std::cout << "dp[i][1][1] : " << dp[i][1][1] << std::endl;
            }
            //  If you cannot achieve any profit, return 0.
            return std::max(dp[n][1][0], 0);
        }
    };
};