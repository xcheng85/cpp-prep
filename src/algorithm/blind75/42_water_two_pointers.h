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
        // // 数组充当备忘录
        // vector<int> leftMax(n, 0);
        // vector<int> rightMax(n, 0);
        int left = 0, right = n - 1;
        int leftMax = 0, rightMax = 0;
        int res = 0;
        while (left < right)
        {
            // left max is real max
            leftMax = max(leftMax, height[left]);
            // right max is not necessary the max
            rightMax = max(rightMax, height[right]);

            // it is decided by smaller height, rightmax is incorrect, does not matter
            if (leftMax < rightMax)
            {
                res += leftMax - height[left];
                // current bin is completed
                left++;
            }
            else
            {
                // very tricky here
                // refine the right side until it become precise
                // maxright is at the right side, then result is good
                // maxright is at the left side(in the future), 
                res += rightMax - height[right];
                right--;
            }
        }
        return res;
    }
};