// subsequence: is not consecutive
// text1 = "abcde", text2 = "ace"

// abc  and ac

// dp[6][4]

// dp[1][1] = max(dp[0][0] + 0/1, dp[1][0], dp[0][1]); 1; //a == a
// dp[1][2] = max(dp[1][1] + 0/1, dp[2][2]);

1; // a, ac
// dp[2][1] = 1; // ab, a
// dp[2][2] = 1; // max(dp[1][1] + 0/1, dp[1][2], dp[2][1]);

// dp[3][2] = max(dp[3-1][2-1] + 0/1, dp[3-1][2], dp[3][1]);
// dp[2][3] = max(dp[1][2] + 0/1, dp[2][2]);

// dp[3][3] = 2; // abc , ace
// dp[4][3] =

#include <string>
#include <vector>

using namespace std;
class Solution
{
public:
    int longestCommonSubsequence(string text1, string text2)
    {
        int n1 = text1.size(), n2 = text2.size();
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

        for (int i = 1; i <= n1; i++)
        {
            for (int j = 1; j <= n2; j++)
            {
                // cout << "dp["<<i-1<<"]["<<j-1<<"]" << dp[i-1][j-1] << endl;
                dp[i][j] = std::max({dp[i - 1][j - 1] + (text1[i - 1] == text2[j - 1] ? 1 : 0), dp[i - 1][j], dp[i][j - 1]});
                // cout << "dp["<<i<<"]["<<j<<"]" << dp[i][j] << endl;
            }
        }
        return dp[n1][n2];
    }
};