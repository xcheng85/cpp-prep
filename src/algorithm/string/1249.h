class Solution {
public:
    string minRemoveToMakeValid(string s) {
        string tmp;
        tmp.reserve(s.size());
        int leftCounter = 0;

        // left right
        for (const auto& c : s) {
            if (c >= 'a' && c <= 'z') {
                tmp += c;
                continue;
            }
            if (c == '(') {
                tmp += c;
                ++leftCounter;
                continue;
            }
            if (leftCounter > 0) {
                tmp += c;
                --leftCounter;
                continue;
            }
            if (leftCounter == 0) {
                // skip
            }
        }
        tmp.shrink_to_fit();


        string res;
        res.reserve(tmp.size());
        int rightCounter = 0;
        // right to left
        for (int i = tmp.size() - 1; i >= 0; --i) {
            const auto c = tmp[i];
            if (c >= 'a' && c <= 'z') {
                res += c;
                continue;
            }
            if (c == ')') {
                res += c;
                ++rightCounter;
                continue;
            }
            if (rightCounter > 0) {
                res += c;
                --rightCounter;
                continue;
            }
            if (rightCounter == 0) {
                // skip
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};