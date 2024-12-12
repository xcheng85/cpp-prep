#include <vector>
#include <string>
#include <numeric>

using namespace std;

// s = "leetcode", wordDict = ["leet","code"]

// 1. substr(i, len);
// 2. subproblem: all the candidate length and do substr, no match done,
// 3. recursive first

// recursive version
class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        //  if (s.substr(i, word.length()) =
        return dfs(s, wordDict, 0);
    }

    bool dfs(const string &s, const vector<string> &wordDict, int startIndex)
    {
        if (startIndex >= s.size())
        {
            return true;
        }
        bool res = false;
        for (const auto &word : wordDict)
        {
            int n = word.size();
            if (s.substr(startIndex, n) == word)
            {
                res = dfs(s, wordDict, startIndex + n);
                if (res)
                {
                    return true;
                }
            }
        }
        return res;
    }
};

// optimization

// "a","aa" aaa

class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        //
        _dfs.resize(s.size() + 1, std::numeric_limits<int>::max());
        _dfs[0] = true;
        //  if (s.substr(i, word.length()) =
        return dfs(s, wordDict, 0);
    }

    bool dfs(const string &s, const vector<string> &wordDict, int startIndex)
    {
        auto remainingChar = s.size() - startIndex;
        // memorization
        if (_dps[remainingChar] != std::numeric_limits<int>::max())
        {
            return _dps[remainingChar] == 1;
        }

        bool res = false;
        for (const auto &word : wordDict)
        {
            int n = word.size();
            if (s.substr(startIndex, n) == word)
            {
                res = dfs(s, wordDict, startIndex + n);
                _dps[remainingChar] = res;
                if (res)
                {
                    // early trim branch
                    return res;
                }
            }
        }

        return res;
    }

private:
    // how many char left
    // 
    vector<int> _dfs; //
};

// root: leetcode, left leet and right code