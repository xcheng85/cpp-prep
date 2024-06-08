//1. based on the two bounds
// 2. cache results: leftForRightbound to accelerate the right bound calculation


class Solution {
public:
    // left bound and right bound of binary search
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res = {-1, -1};
        int left = 0, right = nums.size() - 1;
        int leftForRightbound = -1;
        // left bound
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else if (nums[mid] == target) {
                // cache for the faster right-bound if possible
                if (leftForRightbound == -1)
                    leftForRightbound = mid + 1;
                right = mid - 1;
            }
        }
        // no need for right bound
        if (leftForRightbound==-1||left == -1 || nums[left] != target) {
            return {-1, -1};
        }
        res[0] = left;
        // left faster
        left = leftForRightbound;
        right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            }
        }
        res[1] = right;
        return res;
    }
};