class Solution {
public:
    int characterReplacement(string s, int k) {
        int res = 0;
        // state of sliding window
        // s consists of only uppercase English letters.
        
        // set to order the counter a waste. only need the max counter
        // 
        vector<int> wordCounter(26, 0);
        int maxWordCounterInWindow = 0;

        int l = 0, r = 0;
        while (r < s.length()) {
            wordCounter[s[r] - 'A']++;
            // only this char updated, only he possibly updated the result
            maxWordCounterInWindow = max(maxWordCounterInWindow, wordCounter[s[r] - 'A']);
            r++;
            while(r - l - maxWordCounterInWindow > k && l < r) {
                // this may affect the maxWordCounterInWindow
                --wordCounter[s[l++] - 'A'];
                // no way to update the result
            }
            res = max(res, r -l);
        }
        return res;
    }
};