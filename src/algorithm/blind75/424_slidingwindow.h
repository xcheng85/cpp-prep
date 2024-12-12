// what is the state that we need to model in the sliding window

// how many different Upper-case english charactor in that window. 
// if <= k, it is all good, we should update the result (local optimum)
// if > k, means not enough k to make the change, time to shrink left

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
                --wordCounter[s[l] - 'A'];
                // no way to update the result
                // shrink window
                ++l; 
            }
            res = max(res, r -l);
        }
        return res;
    }
};