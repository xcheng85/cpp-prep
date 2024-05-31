class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        size_t currW = 0;
        for(size_t i = 0; i < nums.size(); ++i) {
            if(nums[i]) {
                nums[currW++] = nums[i];
            }
        }
        //
        memset(&nums[currW], 0, sizeof(int) * (nums.size() - currW));
        // for(size_t i = currW; i < nums.size(); ++i) {
        //     nums[i] = 0;
        // }
    }
};