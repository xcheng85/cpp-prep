class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) { 
        sort(intervals.begin(), intervals.end(), [](auto& interval1, auto& interval2){
            return interval1[0] < interval2[0];
        });

        for(int i = 0; i < intervals.size(); ++i){
            cout << "[" << intervals[i][0] << "," << intervals[i][1] << "]" << endl;
        }

        vector<vector<int>> res;
        vector<int> curr = intervals[0];
        for(int i = 1; i < intervals.size(); ++i) {
            if(intervals[i][0] <= curr[1]) {
                curr[1] = max(intervals[i][1], curr[1]);
            } else {
                // no overlap
                res.emplace_back(curr);
                curr = intervals[i];
            }
        }
        res.emplace_back(curr);
        return res;
    }
};