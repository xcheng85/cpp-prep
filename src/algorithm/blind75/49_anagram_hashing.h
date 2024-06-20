class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> hashmap;
        for(const auto &s : strs) {
            hashmap[hashing(s)].emplace_back(s);
        }
        vector<vector<string>> res;
        for(const auto& [k, v] : hashmap) {
            res.push_back(v);
        }
        return res;
    }

    string hashing(string s) {
        string res(26, 0);
        // 0 <= strs[i].length <= 100
        // char: 8 bit is enough
        for(const auto& c : s) {
            ++res[c- 'a'];
        }
        return res;
    }
};