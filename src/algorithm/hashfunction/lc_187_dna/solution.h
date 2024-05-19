#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <format>
#include <string>
#include <assert>

using namespace std;

class Solution
{
public:
    vector<string> findRepeatedDnaSequences(string s)
    {
        const auto charToInt = [](char c)
        {
            int base;
            if (c == 'A')
            {
                base = 1;
            }
            else if (c == 'C')
            {
                base = 2;
            }
            else if (c == 'G')
            {
                base = 3;
            }
            else if (c == 'T')
            {
                base = 4;
            }
            else
            {
                assert(false);
            }
            return base;
        };

        vector<string> res;

        if (s.size() < 10)
        {
            return res;
        }

        unordered_map<unsigned long long, int> hashtable;
        auto curr{s.substr(0, 10)};

        // avoid overflow
        unsigned long long number{0};
        auto base{0};
        for (size_t i = 0; i < 10; ++i)
        {
            // reverse bit
            number += (charToInt(curr[i]) * pow(10, 9 - i));
        }
        ++hashtable[number];

        unsigned long long p9 = pow(10, 9);
        for (size_t i = 10; i < s.size(); ++i)
        {
            number -= (charToInt(s[i - 10]) * p9);
            number *= 10;
            number += charToInt(s[i]);
            ++hashtable[number];
            for (size_t k = 0; k < 9; ++k)
            {
                curr[k] = curr[k + 1];
            }
            curr[9] = s[i];
            // must == 2
            if (hashtable[number] == 2)
            {
                res.emplace_back(curr);
            }
        }
        return res;
    }
};