// key is:  // key is the <= not the < 

class Solution {
public:
// O(log n) time indicate binary search
// All the integers of nums are unique.
    int findMin(vector<int>& nums) {
        // [3,4,5,1,2]: min in the other half
        // [4,5,1,2,3]: min alway in the unsorted half
        // [5,1,2,3,4]
        int l = 0, r = nums.size() - 1;
        int res;
        while(l <= r) {
            if(nums[l] < nums[r]) {
                // always select the unsorted part
                // if it become sorted, it means the end
                // end of recursive
                res = nums[l];
                break;
            }
            int mid =  (l + r)/2;
            // we know here nums[l] > nums[r] from line 12: unique is not allowed
            // this means nums[mid] > nums[r]
            // key is the <= not the < 
            if(nums[l] <= nums[mid]) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return res;
    }
};