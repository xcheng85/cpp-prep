#include <vector>
#include <string>
#include <numeric>
#include <queue>
#include <unordered_set>
#include <iterator>

using namespace std;

// Example 1:

// Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
// Output: [[1,5],[6,9]]
// Example 2:

// Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
// Output: [[1,2],[3,10],[12,16]]
// Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

// start of each interval is already sorted

// current iterated interval: 1, 2    4, 8, no intersection, next one    4 > 2 || 8 < 1
// 3, 5  and 4, 8 has intersection, min start and max end, 3, 8

// 3, 8 6, 7, intersection, min start and max end, 3 8

// 3, 8 vs 8, 10, intersection, min start and max end, 3, 10, done

class Solution
{
public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
    {
        // intervals.size() could be 0
        vector<vector<int>> res;
        vector<int> current = newInterval;

        // last index
        int lastIndexIterated = -1;
        for (int i = 0; i < intervals.size(); i++)
        {
            const auto &interval = intervals[i];
            // [12,16] vs [3, 10]
            if (interval[0] > current[1])
            {
                lastIndexIterated = i;
                // res.emplace_back(current); // and the rest
                // std::copy(intervals.begin() + i + 1, intervals.end(), std::back_inserter(res));
                break;
                // it is over
            }
            if (interval[1] < current[0])
            {
                // no effect to current
                // [1,2] vs [4,8]
                res.emplace_back(interval);
                continue;
            }

            // [3,5] vs [4, 8]
            // [8,10] vs [3, 8]
            // intersection
            current[0] = std::min(interval[0], current[0]);
            current[1] = std::max(interval[1], current[1]);
        }
        res.emplace_back(current); // and the rest
        // no: lastIndexIterated + 1
        if(lastIndexIterated >= 0)
            std::copy(intervals.begin() + lastIndexIterated, intervals.end(), std::back_inserter(res));
        return res;
    }
};