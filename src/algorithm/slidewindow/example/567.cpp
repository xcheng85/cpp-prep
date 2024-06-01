class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        // define need,
        // define what current window has

        unordered_map<char, int> need, window;
        for (const auto& c : s1) {
            need[c]++;
        }
        // initial window size
        // [left, right)
        int left = 0, right = 0;

        int numMatchedNeedChars = 0;

        // sliding right side
        while (right < s2.size()) {
            char c = s2[right];
            right++; //  [left, right)
            if (need.count(c)) {
                ++window[c];
                if (window[c] == need[c]) {
                    ++numMatchedNeedChars;
                }
                // all matched
                while (numMatchedNeedChars == need.size()) {
                    // no extra char
                    if (right - left == s1.size()) {
                        return true;
                    }
                    // d is to be deleted from the window map
                    char d = s2[left];
                    ++left;
                    if (need.count(d)) {
                        if (window[d] == need[d]) {
                            // left sliding is done.
                            --numMatchedNeedChars;
                        }
                        --window[d];
                    }
                }
            }
        }
        return false;
    }
};