// k == 2

// state: dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
//                          do nothing      sell


// state: dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
//                          do nothing      buy

// base case

// dp[0][k][0] = max(dp[-1][k][0], dp[-1][k][1] + prices[0]) = 0
// dp[0][k][1] = max(dp[-1][k][1], dp[-1][k-1][0] - prices[0]) = -price[0]

