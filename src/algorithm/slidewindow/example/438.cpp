class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        // define what is needed
        unordered_map<char, int> need, window;
        //
        for (const auto& c : p) {
            ++need[c];
        }

        int left = 0, right = 0;
        int numMatchedNeedChars = 0;

        while (right < s.size()) {
            char c = s[right++]; // [left, right)
            if(need.count(c)) {
                // only react if relevant
                 ++window[c];
                 if(window[c] == need[c]) {
                    // one char is enough
                    ++numMatchedNeedChars;
                 }
                 // check if all needs are satisfied
                 while(numMatchedNeedChars == need.size()) {
                    // check if there is no extra char
                    if (right - left == p.size()) {
                        res.emplace_back(left);
                    }
                    // start to move left
                    char toDelete = s[left];
                    ++left;
                    // relevant char
                    if(need.count(toDelete)){
                        // going to miss the need
                        if(window[toDelete] == need[toDelete]) {
                            --numMatchedNeedChars;
                            // break the inner while loop, right start to move
                        }
                        --window[toDelete];
                    }
                 }
            }
        }
        return res;
    }
};