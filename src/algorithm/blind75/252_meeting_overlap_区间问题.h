#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution
{
public:
    bool canAttendMeetings(vector<vector<int>> &intervals)
    {
        // no overlap
        // ascending sorting
        sort(intervals.begin(), intervals.end(), [](const auto& i1, const auto& i2){
            return i1[0] < i2[0];
        });

        if(intervals.size() == 0) {
            return true;
        }

        vector<int> curr = intervals[0];

        for(int i = 1; i < intervals.size(); ++i) {

            if(intervals[i][0] < curr[1]){
                return false;
            } else {
                curr = intervals[i];
            }
        }
        return true;
    }
};