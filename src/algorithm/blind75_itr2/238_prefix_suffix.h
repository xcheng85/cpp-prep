class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> prefixMulti(nums.size(), 1);
        vector<int> suffixMulti(nums.size(), 1);
        vector<int> res(nums.size(), 1);

        for(int i = 1; i < prefixMulti.size(); ++i) {
            prefixMulti[i] = prefixMulti[i-1] * nums[i-1];
        }

        for(int i = prefixMulti.size() - 2; i >= 0; --i) {
            suffixMulti[i] = suffixMulti[i + 1] * nums[i+1];
        }

        for(int i = 0; i < res.size(); ++i) {
            res[i] = prefixMulti[i] * suffixMulti[i];
        }
        return res;
    }
};