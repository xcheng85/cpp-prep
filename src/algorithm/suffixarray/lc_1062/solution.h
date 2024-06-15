#include <string>
#include <algorithm>
#include <format>
#include <cstring>
#include <vector>
#include <numeric>
#include <iterator>
#include <iostream>
// suffix sort solution + largest commmon prefix

// page876 Algorithm [Robert Sedgewick]
using namespace std;

// aabcaabdaab
struct suffix
{
    const char *data;
    int length; // string's length, for lcp
    int offset; // to the beginning of string, [0, s.size()-1]
    suffix() = delete;
    suffix(const string &s, int length, int offset)
        : length{length},
          offset{offset}
    {
        data = s.data() + offset;
    }
    suffix(const suffix &) = default;
    suffix &operator=(suffix &) = default;
    // const string& s will be problem with
    suffix &operator=(suffix &&) noexcept = default;

    inline std::string to_string() const
    {
        return std::string(data);
    }
};

std::ostream &operator<<(std::ostream &os, const suffix &s)
{
    //os << format("rank {}, {}\n", s.offset, s.data);
    return os;
}

bool operator<(const suffix &s1, const suffix &s2)
{
    // be careful the < 0 missing
    return strcmp(s1.data, s2.data) < 0;
}

class Solution
{
public:
    int longestRepeatingSubstring(string s)
    {
        auto sortedSuffix = buildSuffixArray(s);

        int res{0};
        for (size_t i = 1; i < sortedSuffix.size(); ++i)
        {
           // cout <<  format("i: {}, max: {}\n",i, res);
            res = std::max({res, largestCommonPrefixSize(
                                     sortedSuffix[i - 1].data, sortedSuffix[i - 1].length - sortedSuffix[i - 1].offset,
                                     sortedSuffix[i].data, sortedSuffix[i].length) -
                                     sortedSuffix[i].offset});
        }
        return res;
    }

private:
    int largestCommonPrefixSize(const char *s1, int length1, const char *s2, int length2)
    {
       // cout << format("largestCommonPrefixSize {}, {}\n", s1, s2);
        size_t n = std::min({length1, length2});
        for (size_t i = 0; i < n; ++i)
        {
            if (*(s1 + i) != *(s2 + i))
            {
                return i;
            }
        }
        //cout << format("lcp {}, {}, {}\n", s1, s2, n);
        return n;
    }

    vector<suffix> buildSuffixArray(string s)
    {
        vector<suffix> res;
        for (size_t i = 0; i < s.size(); ++i)
        {
            res.emplace_back(s, s.size(), i);
        }
        sort(res.begin(), res.end());
        return res;
    }
};