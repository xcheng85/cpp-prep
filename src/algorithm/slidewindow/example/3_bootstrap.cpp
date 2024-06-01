#include <string>
#include <unordered_map>
#include <numeric>

using namespace std;

//
string minCoverWindow(string s, string t)
{
    // compare window with need
    unordered_map<char, int> need, window;

    // minimum requirement for any solution

    // every charactor of target string is needed.
    // this cover the character appeared more than once
    for (const auto &c : t)
    {
        need[c]++;
    }
    // initally contain: 0 char
    // [left, right)
    int left = 0, right = 0;

    // depends on how many unique chars the target string has
    int numMatchedNeedChars = 0;

    // the start of minLen string
    // how to recover the best string, start + len
    int start = 0;

    // could use std::optional
    int minLen = std::numeric_limits<int>::max();

    // caterpillar-style two while loop
    // simulation ? two agents move based on each other
    while (right < s.size())
    {
        char c = s[right];
        right++;  //  [left, right)

        // check if the meet the need condition met for this new 'c'
        if (need.count(c))
        {
            ++window[c];
            if (window[c] == need[c]){
                ++numMatchedNeedChars;
            }
        }

        // find one solution, try to optimize
        while (numMatchedNeedChars == need.size())
        {
            // update minLen
            if (right - left < minLen)
            {
                start = left;
                minLen = right - left;
            }
            char d = s[left];
            ++left;

            if (need.count(d))
            {
                // left move finished.
                // go back to the right while loop
                if (window[d] == need[d]){
                    // left sliding is done.
                    --numMatchedNeedChars;
                }
                --window[d];
            }
        }
    }
    return minLen == std::numeric_limits<int>::max() ? "" : s.substr(start, minLen);
}