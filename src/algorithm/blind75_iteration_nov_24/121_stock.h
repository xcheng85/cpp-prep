#include <vector>
#include <algorithm>
#include <utility>
#include <numeric>
#include <array>

using namespace std;

// ith day
// buy k times
// 0: not own stock; 1 own stock

// last day, max k buy and not own stock
// goal maximize: dp[n-1][k][0]

// state: dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
//                          do nothing            sell the stock

// state: dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
//                          do nothing             buy the stock

// what about the initial state ?
// initial state (no stock) dp[0][k][0] = 0
// initial state (has stock which is impossible): dp[0][k][1] = -inf

// limitation on k = 1
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int prevNoStock = 0, prevStock = std::numeric_limits<int>::min();
        for (const auto &p : prices)
        {
            int currNoStock = std::max(prevNoStock, prevStock + p); // sell
            // prevNoStock - p is incorrect.
            // you only have one buy prevNoStock - p should be -p.
            int currStock = std::max(prevStock, 0 - p); // buy

            // advance state
            // this will not consider the 1 transaction
            prevNoStock = currNoStock;
            prevStock = currStock;
        }
        return prevNoStock;
    }
};

// without limitation on k: generic implementation
// dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
// dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        // 3: 3 possiblity of buying transactions, 0, 1, 2 transaction(s)
        // 2: owning or not owning stocks, you cannot own multiple stockes at the same time
        vector<std::array<int, 2>> dp(n);

        // when k is out of equation, this part does not apply anymore
        // // for k = 0: no transaction
        // for (int i = 0; i < n; i++)
        // {
        //     dp[i][0][0] = 0;
        //     dp[i][0][1] = std::numeric_limits<int>::min(); // impossible to own stock without buying any: k==0
        // }

        // // key to this question.
        // for (int k = maxK; k >= 1; k--)
        // {
        //     dp[0][k][0] = 0;
        //     dp[0][k][1] = -prices[0]; // key
        // }

        // when k is out of equation, the above become
        dp[0][0] = 0;
        dp[0][1] = -prices[0];

        for (int i = 1; i < n; i++)
        {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        }
        return dp[n - 1][0];
    }
};

// with transaction fee, once per buy/sell
// without limitation on k: generic implementation
// dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
// dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
class Solution
{
public:
    int maxProfit(vector<int> &prices, int fee)
    {
        int n = prices.size();
        // 3: 3 possiblity of buying transactions, 0, 1, 2 transaction(s)
        // 2: owning or not owning stocks, you cannot own multiple stockes at the same time
        vector<std::array<int, 2>> dp(n);

        // when k is out of equation, this part does not apply anymore
        // // for k = 0: no transaction
        // for (int i = 0; i < n; i++)
        // {
        //     dp[i][0][0] = 0;
        //     dp[i][0][1] = std::numeric_limits<int>::min(); // impossible to own stock without buying any: k==0
        // }

        // // key to this question.
        // for (int k = maxK; k >= 1; k--)
        // {
        //     dp[0][k][0] = 0;
        //     dp[0][k][1] = -prices[0]; // key
        // }

        // when k is out of equation, the above become
        dp[0][0] = 0;
        dp[0][1] = -prices[0] - fee;

        for (int i = 1; i < n; i++)
        {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i] - fee);
        }
        return dp[n - 1][0];
    }
};


// without limitation on k: generic implementation
// without 1 day cooling down
// dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
// dp[i][1] = std::max(dp[i - 1][1], dp[i - 2][0] - prices[i]);
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        // 3: 3 possiblity of buying transactions, 0, 1, 2 transaction(s)
        // 2: owning or not owning stocks, you cannot own multiple stockes at the same time
        vector<std::array<int, 2>> dp(n);

        // when k is out of equation, this part does not apply anymore
        // // for k = 0: no transaction
        // for (int i = 0; i < n; i++)
        // {
        //     dp[i][0][0] = 0;
        //     dp[i][0][1] = std::numeric_limits<int>::min(); // impossible to own stock without buying any: k==0
        // }

        // // key to this question.
        // for (int k = maxK; k >= 1; k--)
        // {
        //     dp[0][k][0] = 0;
        //     dp[0][k][1] = -prices[0]; // key
        // }

        // when k is out of equation, the above become
        dp[0][0] = 0;
        dp[0][1] = -prices[0];

        if(n < 2) {
            return dp[0][0];
        }

        // After you sell your stock, you cannot buy stock on the next day
        // no limitation to sell here
        dp[1][0] = std::max(dp[0][0], dp[0][1] + prices[1]);
        dp[1][1] = std::max(-prices[0], -prices[1]);

        for (int i = 2; i < n; i++)
        {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = std::max({dp[i - 1][1], dp[i - 2][1], dp[i - 2][0] - prices[i]});
        }
        return dp[n - 1][0];
    }
};

// without limitation on k
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int prevNoStock = 0, prevStock = std::numeric_limits<int>::min();
        for (const auto &p : prices)
        {
            int currNoStock = std::max(prevNoStock, prevStock + p); // sell
            // prevNoStock - p is incorrect.
            // you only have one buy prevNoStock - p should be -p.
            int currStock = std::max(prevStock, prevNoStock - p); // buy

            // advance state
            // this will not consider the 1 transaction
            prevNoStock = currNoStock;
            prevStock = currStock;
        }
        return prevNoStock;
    }
};

// limitation k = 2
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        // 3: 3 possiblity of buying transactions, 0, 1, 2 transaction(s)
        // 2: owning or not owning stocks, you cannot own multiple stockes at the same time
        auto dp = new int[n][3][2];
        const int maxK = 2;

        // for k = 0: no transaction
        for (int i = 0; i < n; i++)
        {
            dp[i][0][0] = 0;
            dp[i][0][1] = std::numeric_limits<int>::min(); // impossible to own stock without buying any: k==0
        }

        // key to this question.
        for (int k = maxK; k >= 1; k--)
        {
            dp[0][k][0] = 0;
            dp[0][k][1] = -prices[0]; // key
        }

        for (int i = 1; i < n; i++)
        {
            // for (int k = 1; k <= maxK; ++k)
            // why reverse order ? because the dependency of state transfer function: k depends on k - 1, so we must do k first
            // k-1 not depends on k
            for (int k = maxK; k >= 1; k--)
            {
                dp[i][k][0] = std::max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i]);
                dp[i][k][1] = std::max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i]);
            }
        }
        return dp[n - 1][maxK][0];
    }
};

// limitation any k as input
class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size();
        // 3: 3 possiblity of buying transactions, 0, 1, 2 transaction(s)
        // 2: owning or not owning stocks, you cannot own multiple stockes at the same time
        const int maxK = k;
        vector<vector<std::array<int, 2>>> dp(n, vector<std::array<int, 2>>(maxK + 1));

        // for k = 0: no transaction
        for (int i = 0; i < n; i++)
        {
            dp[i][0][0] = 0;
            dp[i][0][1] = std::numeric_limits<int>::min(); // impossible to own stock without buying any: k==0
        }

        // key to this question.
        for (int k = maxK; k >= 1; k--)
        {
            dp[0][k][0] = 0;
            dp[0][k][1] = -prices[0]; // key
        }

        for (int i = 1; i < n; i++)
        {
            // for (int k = 1; k <= maxK; ++k)
            // why reverse order ? because the dependency of state transfer function: k depends on k - 1, so we must do k first
            // k-1 not depends on k
            for (int k = maxK; k >= 1; k--)
            {
                dp[i][k][0] = std::max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i]);
                dp[i][k][1] = std::max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i]);
            }
        }
        return dp[n - 1][maxK][0];
    }
};
