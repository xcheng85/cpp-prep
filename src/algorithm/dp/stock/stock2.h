// ith day
// buy k times
// 0: not own stock; 1 own stock

// last day, max k buy and not own stock
// goal maximize: dp[n-1][k][0]

// state: dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
//                          do nothing      sell


// state: dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
//                          do nothing      buy


// remove the buy k times constraints 
// state: dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
//                          do nothing      sell

// state: dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])
//                        do nothing,    buy

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // remove the buy k times constraints
        // state: dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
        //                          do nothing      sell

        // state: dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])
        //                        do nothing,    buy

        // initially own stock is impossible without buy
        int dp_no_stock = 0, dp_own_stock = numeric_limits<int>::min(); 

        for(int i = 0; i < prices.size(); ++i) {
            const auto tmp = dp_no_stock;

            dp_no_stock = max(dp_no_stock, dp_own_stock + prices[i]);
            dp_own_stock = max(dp_own_stock, tmp - prices[i]);
        }
        return dp_no_stock;
    }
};