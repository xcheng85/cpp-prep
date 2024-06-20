#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
           //边界相同并不算相交。
        // sorting based on the end 
        // intervals = [[1,2],[2,3],[3,4],[1,3]]

        // [1, 2] 
        //       [2, 3]
        // [1        3]
        
        // sorting by end
        sort(intervals.begin(), intervals.end(), [](const auto& i1, const auto& i2){
            return i1[1] < i2[1];
        });
        int res = 1;
        int currentE = intervals[0][1];

        for(int i = 1; i < intervals.size(); ++i) {
            if(intervals[i][0] >= currentE) {
                ++res;
                currentE = intervals[i][1];
            }
        }
        return intervals.size()-res;
    }
};