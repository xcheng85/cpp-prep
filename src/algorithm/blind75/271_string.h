#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <utility>
#include <queue>
#include <map>

using namespace std;

class Codec {
public:
    // non-ASCII delimiter:  Unicode characters
    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string res;
        for(const auto& s:strs) {
            res += to_string(s.size()) + "#" + s;
        }
        return res;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> decodedStrings;
        size_t i = 0;
        while (i < s.size()) {
            size_t delim = s.find_first_of("#", i);
            // this substr should left with 1 char which indicate length of coming stirng
            int length = stoi(s.substr(i, delim - i));
            // skip #
            string str = s.substr(delim + 1, length);

            decodedStrings.emplace_back(str);
            i = delim + 1 + length;
        }
        return decodedStrings;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));