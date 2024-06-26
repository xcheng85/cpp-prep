#include <string>
using namespace std;

// 对于两个字符串求子序列的问题，都是用两个指针 i 和 j 分别在两个字符串上移动，大概率是动态规划思路。
class Solution
{
public:
    int longestCommonSubsequence(string text1, string text2)
    {
        _memo.resize(text1.size(), vector<int>(text2.size(), -1));

        return dp(text1, 0, text2, 0);
    }

    // lcs between [i, ...] and [j,...]
    // recursive + store state
    int dp(string s1, int i, string s2, int j)
    {
        // recursive terminating condition
        if (i == s1.length() || j == s2.length())
        {
            return 0;
        }

        if (_memo[i][j] != -1)
        {
            return _memo[i][j];
        }

        if (s1[i] == s2[j])
        {
            // s1[i] 和 s2[j] 必然在 lcs 中，
            // 加上 s1[i+1..] 和 s2[j+1..] 中的 lcs 长度，就是答案
            int res = 1 + dp(s1, i + 1, s2, j + 1);
            _memo[i][j] = res;
            return res;
        }
        else
        {
            int res = max({// 情况一、s1[i] 不在 lcs 中
                       dp(s1, i + 1, s2, j),
                       // 情况二、s2[j] 不在 lcs 中
                       dp(s1, i, s2, j + 1),
                       // 情况三、都不在 lcs 中
                       dp(s1, i + 1, s2, j + 1)});
            _memo[i][j] = res;
            return res;
        }
    }

private:
    // 备忘录，消除重叠子问题
    vector<vector<int>> _memo;
};