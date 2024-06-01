// 1. left move condition trick
// 2. know when a new better result could occur.

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // substring problem
        int res = 0;
        // no need
        unordered_set<char> cache;

        int left = 0, right = 0;

        while(right < s.size()) {
            auto c = s[right++]; // [left, right)
            if(cache.find(c) == cache.end()) {
                res = max(res, right - left);
                cache.insert(c);
            } else {
                // move left until any prev c are deleted
                // stop condition for left move
                while(cache.find(c) != cache.end()) {
                    auto toDelete = s[left++];
                    cache.erase(toDelete);
                }
                cache.insert(c);
            }
        }
        return res;
    }
};