// 121. one transaction k = 1

// ith day
// buy k times
// 0: not own stock; 1 own stock

// last day, max k buy and not own stock
// goal maximize: dp[n-1][k][0]

// state: dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
//                          do nothing      sell


// state: dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
//                          do nothing      buy

// k = 1: one transaction 

// state: dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + prices[i])
//                          do nothing      sell


// state: dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - prices[i])
//                          do nothing      buy

// no transaction, profit is 0
// dp[i-1][0][0] = 0

// state: dp[i][1][1] = max(dp[i-1][1][1],  0 - prices[i])
//                          do nothing      buy

// simply to two state

// dp_i_no_stock, dp_i_own_stock 

// goal: dp_i_no_stock at n-1


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // -infitiy:  imposiible to has stock 
        int profit_i_nostock = 0, profit_i_hasstock = numeric_limits<int>::min();

        for(int i = 0; i < prices.size(); ++i) {
            profit_i_nostock = max(profit_i_nostock, profit_i_hasstock + prices[i]);
            // only 1 transaction
            profit_i_hasstock = max(profit_i_hasstock, 0 - prices[i]);
        }

        return profit_i_nostock;
    }
};