#include <map>
#include <algorithm>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int left = 0, right = height.size() - 1;
        int res = 0;
        while (left < right)
        {
            // [left, right] 之间的矩形面积
            int cur_area = min(height[left], height[right]) * (right - left);
            res = max(res, cur_area);

            // key: 双指针技巧，移动较低的一边,
            // area is determined by the smaller height
            // like greedy
            if (height[left] < height[right])
            {
                left++;
            }
            else
            {
                right--;
            }
        }
        return res;
    }
};