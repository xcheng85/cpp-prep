#include <map>
#include <algorithm>
#include <unordered_set>
#include <utility>
#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    string minWindow(string s, string t)
    {
        string res; // restore by start and len
        // state to reproduce the final result
        int start = 0;
        int len = 0;
        // optimal result
        int minStrLen = numeric_limits<int>::max();

        // state of sliding window
        unordered_map<char, int> need, windowCharCounter;
        int matchedCharWindow = 0; // goal is need.size();
        for (char c : t)
            need[c]++;

        int l = 0, r = 0;
        while (r < s.size())
        {
            char c = s[r++];
            // igore the counter if this char is not in the t
            if (need.count(c))
            {
                // closer to the destination
                windowCharCounter[c]++;
                if (windowCharCounter[c] == need[c])
                    matchedCharWindow++;
            }

            // when to update result
            while (matchedCharWindow == need.size() && l < r)
            {
                if (r - l < minStrLen)
                {
                    start = l;
                    len = r - l;
                    minStrLen = r-l;
                }
                // when to shift left
                // try to shift left
                auto charToDelete = s[l];
                if (need.count(charToDelete))
                {
                    --windowCharCounter[charToDelete];
                    if (windowCharCounter[charToDelete] < need[charToDelete])
                    {
                        --matchedCharWindow;
                    }
                }
                l++;
            }
        }
        // final result
        return s.substr(start, len);
    }
};