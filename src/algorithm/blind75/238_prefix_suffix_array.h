class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        // suffix array
        // prefix array
        int n = nums.size();
        vector<int> prefixMul(n, 1);
        vector<int> suffixMul(n, 1);
        for(int i = 1; i < prefixMul.size(); ++i) {
            prefixMul[i] = prefixMul[i-1] * nums[i - 1];
        }

        for(int i = n - 2; i >= 0; --i) {
            suffixMul[i] = suffixMul[i+1] * nums[i+1];
        }

        vector<int> res(n, 0);
        for(int i = 0; i < n; ++i){
            res[i] = prefixMul[i] * suffixMul[i];
        }
        return res;
    }
};