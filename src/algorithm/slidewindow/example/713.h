#include <map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int numSubarrayProductLessThanK(vector<int> &nums, int k)
    {
        // 记录符合条件的子数组（窗口）个数
        int count = 0;

        int left = 0, right = 0;
        // state within the sliding window
        int windowProduct = 1;

        while (right < nums.size())
        {
            // 扩大窗口
            windowProduct  *= nums[right++];
            // move left pointer condition
            while (windowProduct >= k && left < right )
            {
                // 缩小窗口
                windowProduct = windowProduct / nums[left];
                left++;
            }
            // 现在必然是一个合法的窗口，但注意思考这个窗口中的子数组个数怎么计算：
            // 比方说 left = 1, right = 4 划定了 [1, 2, 3] 这个窗口（right 是开区间）
            // 但不止 [left..right] 是合法的子数组，[left+1..right], [left+2..right] 等都是合法子数组
            // 所以我们需要记录 [1], [1,2], [1,2,3] 这 right - left 个子数组都加上
            count += right - left;
        }

        return count;
    }
};