// 1 day cool down after sell

// remove the buy k times constraints 
// cool down restraint does not affect sell state transfer

// state: dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
//                          do nothing      sell

// cool down affect buy logic, i-1 , i-2
// state: dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i])
//                        do nothing,    buy

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // state: dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
        //                          do nothing      sell

        // cool down affect buy logic, i-1 , i-2
        // state: dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i])
        //                        do nothing,    buy

        int dp_no_stock = 0, dp_has_stock = numeric_limits<int>::min(), dp_no_stock_2 = 0;

        for(int i = 0; i < prices.size(); ++i) {
            auto tmp = dp_no_stock;
            dp_no_stock = max(dp_no_stock, dp_has_stock + prices[i]);
            dp_has_stock = max(dp_has_stock, dp_no_stock_2 - prices[i]);
            // -2 step
            dp_no_stock_2 = tmp; 
        }
        return dp_no_stock;
    }
};