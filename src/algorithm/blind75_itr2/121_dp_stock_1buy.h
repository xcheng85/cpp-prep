class Solution {
public:
   // one transaction
    int maxProfit(vector<int>& prices) {
        int numDays = prices.size();
        int prevHasStock = numeric_limits<int>::min(); // impossible before day 0
        int prevNoStock = 0;

        for(int i = 0; i < numDays; ++i) {
            //cout << "day: " << i << endl;
            int todayNoStock = max(prevNoStock, prevHasStock + prices[i]);

            // difference between 1 transaction and any transactions
            // int todayHasStock = max(prevHasStock, prevNoStock - prices[i]);
            // only allow one purchase, it alwasy start with balance 0
            int todayHasStock = max(prevHasStock, 0 - prices[i]);

            prevNoStock = todayNoStock;
            prevHasStock = todayHasStock;

            //cout << "todayNoStock: " << todayNoStock << endl;
            //cout << "todayHasStock: " << todayHasStock << endl;
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