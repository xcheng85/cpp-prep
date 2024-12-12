class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int res = numeric_limits<int>::max();
        int n = nums.size();
        for (int arrayLength = l; arrayLength <= r; arrayLength++) {
            int sum = 0;
            for (int i = 0; i < arrayLength; i++) {
                sum += nums[i];
            }
            if (sum > 0) {
                res = std::min(res, sum);
            }
            for (int i = arrayLength; i < n; i++) {
                sum += nums[i];
                sum -= nums[i - arrayLength];
                if (sum > 0) {
                    res = std::min(res, sum);
                }
            }
        }
        if (res == numeric_limits<int>::max()) {
            return -1;
        }
        return res;
    }
};