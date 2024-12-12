// nums are unique, sorted in ascending order and then rotated
#include <vector>
using namespace std;

// tricky part, two == 
// line48:         while (l <= r)
// line27:         if(nums[l] <= nums[mid]) {

class Solution
{
public:
    int search(vector<int> &nums, int target)
    {
        // 5,6,7,0,1,2,4
        // 6,7,0,1,2,4,5
        // 2,4,5,6,7,0,1
        return searchUtils(nums, target, 0, nums.size() - 1);
    }

    int searchUtils(vector<int> &nums, int target, int l, int r)
    {
        cout << "searchUtils: " << l << "," << r << endl; 
        if(r < l) {
            return -1;
        }
        int mid = l + (r - l) / 2;
        if(nums[l] <= nums[mid]) {
            // left part sorted
            if(nums[l] <= target && nums[mid] >= target) {
                return binarySearch(nums, target, l, mid);
            } else {
                // not falling into the sorted part
                return searchUtils(nums, target, mid + 1, r);
            }
        } else {
            // right part sorted
            if(nums[mid] <= target && nums[r] >= target) {
                return binarySearch(nums, target, mid, r);
            } else {
                // not falling into the sorted part
                return searchUtils(nums, target, l, mid-1);
            }
        }
    }

    int binarySearch(vector<int> &sortedAscending, int target, int l, int r)
    {
        cout << "binarySearch: " << l << "," << r << endl;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (sortedAscending[mid] < target)
            {
                l = mid + 1;
            }
            else if (sortedAscending[mid] == target)
            {
                return mid;
            }
            else
            {
                r = mid - 1;
            }
        }
        return -1;
    }
};