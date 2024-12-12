#include <vector>

// In a concrete business context, this problem may be presented as follows: 
// Suppose we have an array representing video watch times, 
// where each segment consists of the start and stop times of a user watching a video.
// The task is to calculate the total number of unique minutes watched across all the video segments.
//  This is fundamentally the same question.

using namespace std;

class Solution {
public:
    // non-overlapping intervals intervals
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size(), i = 0;
        vector<vector<int>> res;

        // Case 1: no overlapping case before the merge intervals
        // Compare ending point of intervals to starting point of newInterval
        while (i < n && intervals[i][1] < newInterval[0]) {
            res.push_back(intervals[i]);
            i++;
        }

        // now the intervals[i][1] >= newInterval[0]
        // [1, 3] and [2, 5]
        // [1,5] and [2, 5]

        // [5, 7] and [2, 5]

        // [6, 7] and [2, 5]

//         Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
// Output: [[1,5],[6,9]]

         // Case 2: overlapping case and merging of intervals
        while (i < n && newInterval[1] >= intervals[i][0]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }

        //  newInterval[1] < intervals[i][0]
        // end


        // Case 3: no overlapping of intervals after newinterval being merged
        while (i < n) {
            res.push_back(intervals[i]);
            i++;
        }
        res.push_back(newInterval);
    }
};