// remove the buy k times constraints 
// add transaction fee

// state: dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
//                          do nothing      sell

// add -fee

// state: dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i] - fee)
//                        do nothing,    buy


class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        // state: dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
        //                          do nothing      sell

        // add -fee

        // state: dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i] - fee)
        //                        do nothing,    buy

        int dp_no_stock = 0, dp_has_stock = numeric_limits<int>::min();
        for(int i = 0; i < prices.size(); ++i) {
            auto tmp = dp_no_stock;
            dp_no_stock = max(dp_no_stock, dp_has_stock + prices[i]);
            dp_has_stock = max(dp_has_stock, tmp - prices[i] - fee);
        }
        return dp_no_stock;
    }
};