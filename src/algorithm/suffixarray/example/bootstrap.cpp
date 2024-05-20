#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <format>
#include <cstring>

using namespace std;

struct suffix
{
    // string s;
    const char *data;
    int length; // string's length, for lcp
    int offset; // to the beginning of string, [0, s.size()-1]
    suffix() = delete;
    suffix(const string &s, int length, int offset)
        : // s{s},
          offset{offset},
          length{length}
    {
        data = s.data() + offset;
    }
    suffix(const suffix &) = default;
    suffix &operator=(suffix &) = default;
    // const string& s will be problem with
    suffix &operator=(suffix &&) noexcept = default;
};

std::ostream &operator<<(std::ostream &os, const suffix &s)
{
    // os << format("rank {}, {}\n", s.offset, s.s);
    os << format("rank {}, fulllength {}, {}\n", s.offset, s.length, s.data);
    return os;
}

bool operator<(const suffix &s1, const suffix &s2)
{
    // return s1.s < s2.s;
    // be careful the < 0 missing
    return strcmp(s1.data, s2.data) < 0;
}

vector<suffix> buildSuffixArray(const string &s)
{
    vector<suffix> res;
    for (size_t i = 0; i < s.size(); ++i)
    {
        // res.emplace_back(s.substr(i), i);
        res.emplace_back(s, s.size(), i);
    }
    // sort: operator <
    sort(res.begin(), res.end());
    return res;
}

// binary search
bool binearySearch(
    const string &pattern,
    const string &searchedString,
    const vector<suffix> &suffixArray)
{
    int l{0}, r{suffixArray.size() - 1};
    while (l <= r)
    {
        auto mid = l + (r - l) / 2;
        const suffix &curr = suffixArray[mid];
        // cout << curr.s << endl;
        cout << curr.data << endl;
        cout << pattern << endl;
        // rely on the string.compare
        // == cstring strmcmp
        // const auto res = curr.s.compare(0, pattern.size(), pattern);
        // only compare n characters
        const auto res = strncmp(curr.data, pattern.c_str(), pattern.size());
        if (res == 0)
        {
            return true;
        }
        else if (res > 0)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return false;
}

int main()
{
    const auto suffixArray = buildSuffixArray("banana");
    std::copy(std::begin(suffixArray), std::end(suffixArray), std::ostream_iterator<suffix>(std::cout, " "));
    cout << binearySearch("nan", "banana", suffixArray);
    return 0;
}