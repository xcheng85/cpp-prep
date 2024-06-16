#include <vector>
using namespace std;
class Solution
{
public:
    int search(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
            {
                return mid;
            }
            if (nums[mid] >= nums[left])
            {
                // [left..mid] 有序
                if (target >= nums[left] && target < nums[mid])
                {
                    right = mid - 1;
                }
                else
                {
                    // target 落在 [mid+1..right] 中, not necessarily ordered
                    left = mid + 1;
                }
            }
            else
            {
                // mid 落在断崖右边，此时 nums[mid..right] 有序
                if (target <= nums[right] && target > nums[mid])
                {
                    // target 落在 [mid+1..right] 中
                    left = mid + 1;
                }
                else
                {
                    // target 落在 [left..mid-1] 中
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};