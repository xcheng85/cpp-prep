class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries,
                                vector<string>& dictionary) {
        //  lowercase English letters and have the same length
        vector<string> res;
        for (const auto& q : queries) {
            for (const auto& d : dictionary) {
                if (distance(q, d) > 2) {
                    continue;
                } else {
                    res.emplace_back(q);
                    break;
                }
            }
        }
        return res;
    }

    int distance(const string& w1, const string& w2) {
        int diff(0);
        assert(w1.length() == w2.length());
        for (int i = 0; i < w1.length(); ++i) {
            if (w1[i] != w2[i]) {
                ++diff;
            }
        }
        return diff;
    }
};