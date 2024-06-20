class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // substring problem
        int res = 0;
       
        // no need
        unordered_set<char> cache;

        int left = 0, right = 0;

        while(right < s.size()) {
            // // c 是将移入窗口的字符
            auto c = s[right++]; // [left, right)
            if(cache.find(c) == cache.end()) {
                res = max(res, right - left);
                cache.insert(c);
            } else {
                // move left until any prev c are deleted
                // stop condition for left move
                while(cache.find(c) != cache.end()) {
                    // // 缩小窗口
                    auto toDelete = s[left++];
                     // 进行窗口内数据的一系列更新
                    cache.erase(toDelete);
                }
                 // 进行窗口内数据的一系列更新
                cache.insert(c);
            }
        }
        return res;
    }
};