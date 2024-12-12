class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        dp[1][1] = 1;
        // the first row and the first column only have 1 way
        for (int r = 1; r <= m; r++)
        {
            dp[r][1] = 1;
        }
        for (int c = 1; c <= n; c++)
        {
            dp[1][c] = 1;
        }

        for (int r = 2; r <= m; r++)
        {
            for (int c = 2; c <= n; c++)
            {
                dp[r][c] = dp[r - 1][c] + dp[r][c - 1];
            }
        }
        return dp[m][n];
    }
};