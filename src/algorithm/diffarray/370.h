// how to know it should use diffarray

// frequent add/delete (-value) with subrange


class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> diff(length);
        for(const auto& update: updates) {
            // o(1)
            auto s = update[0], e = update[1], delta = update[2];
            diff[s] += delta;
            if(e + 1 < length){
                diff[e + 1] -= delta;
            }
        }
        for(size_t i = 1; i < diff.size(); ++i) {
            diff[i] += diff[i-1];
        }
        return diff;
    }
};