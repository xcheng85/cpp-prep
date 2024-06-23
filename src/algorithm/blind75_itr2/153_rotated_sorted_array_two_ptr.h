// key: every sorted segment generate a potential minVal, and iterative update

class Solution {
public:
    int findMin(vector<int>& nums) {
        int minVal = numeric_limits<int>::max();
        int l = 0, r = nums.size() - 1;

        while(l <= r) {
            int mid = l + (r - l) / 2;
            // All the integers of nums are unique.
            if(nums[l] <= nums[mid]) {
                // 
                minVal = min(minVal, nums[l]);
                l = mid + 1;
                continue;
            }
            if(nums[mid] <= nums[r]) {
                // 
                minVal = min(minVal, nums[mid]);
                r = mid - 1;
                continue;
            } 
        }

        return minVal;
    }
};