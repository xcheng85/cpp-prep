// 647. Palindromic Substrings

#include <map>
#include <algorithm>
#include <unordered_set>
#include <utility>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    int countSubstrings(string s)
    {
        int count = 0;

        // basically iterate all the cases at every position
        for (size_t i = 0; i < s.size(); ++i)
        {
            auto c1 = countPalindromeWithinRange(s, i, i);
            auto c2 = countPalindromeWithinRange(s, i, i + 1);

            count += c1;
            count += c2;
        }
        return count;
    }
    // [center left, center right]
    // odd:
    // even:
    // int palindromeLength(const string &s, int cl, int cr)
    int countPalindromeWithinRange(const string &s, int cl, int cr)
    {
        int count = 0;
        while (cl >= 0 && cr < s.size())
        {
            if (s[cl] != s[cr])
            {
                break;
            }
            ++count;
            --cl;
            ++cr;
        }
        return count;
    }
};