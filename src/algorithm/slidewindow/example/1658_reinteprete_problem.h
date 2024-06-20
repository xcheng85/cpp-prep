#include <map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

// 注意：类似 713. 乘积小于 K 的子数组，之所以本题可以用滑动窗口，关键是题目说了 nums 中的元素都是正数，这就保证了只要有元素加入窗口，和一定变大，只要有元素离开窗口，和一定变小。

class Solution
{
public:
    int minOperations(vector<int> &nums, int x)
    {
        // sum - x

        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        int target = sum - x;
        int l = 0, r = 0;

        // window state
        int windowSum = 0;
        int maxWindowSize = 0;

        while (r < nums.size())
        {
            // [l, r)
            windowSum += nums[r++];

            if (windowSum < target)
            {
                continue;
            }
            // >=

            // shrink left
            // KEY: l < r don't forget 
            while (windowSum > target && l < r)
            {
                windowSum -= nums[l++];
            }
            // < or ==
            if (windowSum == target)
            {
                maxWindowSize = max(maxWindowSize, r - l);
            }
        }
        return maxWindowSize > 0 ? nums.size() - maxWindowSize : -1;
    }
};