// figure out what is sorted and to binary search on that sorted part
// and then keep divide and conqur

// like tree preorder traversal. 

class Solution
{
public:
    int search(vector<int> &nums, int target)
    {
        int l = 0, r = nums.size() - 1;
        int mid = l + (r - l) / 2;

        // figure out what is sorted
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (nums[l] <= nums[mid])
            {
                int index = binarySearch(nums, l, mid, target);
                if (index != -1)
                {
                    return index;
                }
                else
                {
                    l = mid + 1;
                }
            }

            if (nums[mid] <= nums[r])
            {
                int index = binarySearch(nums, mid, r, target);
                if (index != -1)
                {
                    return index;
                }
                else
                {
                    r = mid - 1;
                }
            }
        }
        return -1;
    }

    // think this like a preorder traversal
    // ascending order
    int binarySearch(vector<int> &nums, int l, int r, int target)
    {
        if (target < nums[l] || target > nums[r])
        {
            return -1;
        }

        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] > target)
            {
                r = mid - 1;
            }
            else if (nums[mid] < target)
            {
                l = mid + 1;
            }
            else
            {
                return mid;
            }
        }
        return -1;
    }
};