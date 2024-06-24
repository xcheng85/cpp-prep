#include <vector>
#include <numeric>
#include <map>
#include <algorithm>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

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

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        // -infitiy:  imposible to has stock
        int profit_i_nostock = 0, profit_i_hasstock = std::numeric_limits<int>::min();

        for (int i = 0; i < prices.size(); ++i)
        {
            // sell stock
            profit_i_nostock = max(profit_i_nostock, profit_i_hasstock + prices[i]);

            // only 1 transaction
            // starting from 0, -20, then sell 22, make 2 as profit
            profit_i_hasstock = max(profit_i_hasstock, 0 - prices[i]);
        }

        return profit_i_nostock;
    }
};

class Solution {
public:
   // one transaction
    int maxProfit(vector<int>& prices) {
        int numDays = prices.size();
        int prevHasStock = numeric_limits<int>::min(); // impossible before day 0
        int prevNoStock = 0;

        for(int i = 0; i < numDays; ++i) {
            cout << "day: " << i << endl;
            int todayNoStock = max(prevNoStock, prevHasStock + prices[i]);

            // difference between 1 transaction and any transactions
            // int todayHasStock = max(prevHasStock, prevNoStock - prices[i]);
            // only allow one purchase, it alwasy start with balance 0
            int todayHasStock = max(prevHasStock, 0 - prices[i]);

            prevNoStock = todayNoStock;
            prevHasStock = todayHasStock;

            cout << "todayNoStock: " << todayNoStock << endl;
            cout << "todayHasStock: " << todayHasStock << endl;
        }
        return prevNoStock;

        // base case
        // dp[]

        // ith day have stock
        // ith day does not have stock
        
        // only two state 
        // dp[i][0][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
        // dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);

        // max of dp[n-1][0]
    }
};