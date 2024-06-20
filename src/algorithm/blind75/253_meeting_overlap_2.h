#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <complex>
using namespace std;

// 差分数组的主要适用场景是频繁对原始数组的某个区间的元素进行增减

// intervals = [[0,30],[5,10],[15,20]]

class DifferenceArray
{
public:
    DifferenceArray(const vector<int> &origin) : _array(origin.size(), 0)
    {
        assert(origin.size() > 0);
        _array[0] = origin[0];
        // build difference array
        //
        for (int i = 1; i < _array.size(); ++i)
        {
            _array[1] = origin[i] - origin[i - 1];
        }
    }

    // + and - [i, j]
    void update(int i, int j, int val) {
        _array[i] += val;
        if(j + 1 < _array.size()){
            //compansate
            _array[j+1] -= val;
        }
    }

    vector<int> rebuild() const
    {
        vector<int> res(_array.size(), _array[0]);
        for(int i = 1; i < _array.size(); ++i) {
            res[i] = res[i-1] + _array[i];
        }
        return res;
    }

private:
    vector<int> _array;
};
class Solution
{
public:
    int minMeetingRooms(vector<vector<int>> &intervals)
    {
        // 0 <= starti < endi <= 106

        DifferenceArray da(vector<int>(pow(10, 6) + 1, 0));

        for(const auto& i : intervals) {
            //边界相同并不算相交。
            int s = i[0], e = i[1]-1; // [[1,13]] means the last one is 12, so -1
            da.update(s, e, 1);
        }

        auto overlapArray = da.rebuild();
        int maxOverlap = 0;
        for(const auto& overlap: overlapArray) {
            maxOverlap = max(overlap, maxOverlap);
        }
        return maxOverlap;
    }
};