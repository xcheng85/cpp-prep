// 备忘录消除重叠子问题: 带备忘录的 DFS 算法
//  「遍历」和「分解问题」

// 遍历: 排列组合的视角思考这个问题
//  子问题的

// 单词匹配 s 的前缀 s[0..k]，那么只要我能拼出 s[k+1..]

class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        _memo.resize(s.size(), -1);

        return dp(s, 0, wordDict);
    }

    // i: 0,
    // top down: memo + dfs
    bool dp(string s, int i, vector<string> &wordDict)
    {
        // base case，s[i..] 是空串
        if (i == s.length())
        {
            return true;
        }

        if (_memo[i] != -1)
        {
            return _memo[i];
        }

        // 遍历 wordDict，看看哪些单词是 s[i..] 的前缀
        for (const auto &word : wordDict)
        {
            if (s.substr(i, word.length()) == word)
            {
                int len = word.length();
                // 只要 s[i+len..] 可以被拼出，s[i..] 就能被拼出
                if (dp(s, i + len, wordDict) == true)
                {
                    _memo[i] = true;
                    return true;
                }
            }
        }
        _memo[i] = false;
        return false;
    }

private:
    vector<int> _memo;
};
