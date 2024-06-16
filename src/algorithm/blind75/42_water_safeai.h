#include <map>
#include <algorithm>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
public:
    int trap(vector<int> &height)
    {
        int n = height.size();
        // 数组充当备忘录
        vector<int> leftMax(n, 0);
        vector<int> rightMax(n, 0);
        // 初始化 base case
        leftMax[0] = height[0];
        rightMax[n - 1] = height[n - 1];
        // 从左向右计算 l_max
        for (int i = 1; i < n; i++)
        {
            leftMax[i] = max(height[i], leftMax[i - 1]);
        }

        // 从右向左计算 r_max
        for (int i = n - 2; i >= 0; i--)
        {
            rightMax[i] = max(height[i], rightMax[i + 1]);
        }
        int res = 0;
        for (int i = 1; i < n - 1; i++)
            res += min(rightMax[i], leftMax[i]) - height[i];

        return res;
    }
};