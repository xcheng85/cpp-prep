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
        int res = 0;
        for (int i = 1; i < n - 1; i++)
        {
            int l_max = 0, r_max = 0;
            // 找右边最高的柱子

            r_max = *std::max_element(height.begin() + i, height.end());

            // for (int j = i; j < n; j++)
            //     r_max = max(r_max, height[j]);
            // 找左边最高的柱子
            // for (int j = i; j >= 0; j--)
            //     l_max = max(l_max, height[j]);
            l_max = *std::max_element(height.begin(), height.begin() + i + 1);
            // 如果自己就是最高的话，
            // l_max == r_max == height[i]
            res += min(l_max, r_max) - height[i];
        }
        return res;
    }
};