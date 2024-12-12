// size_t -- overflow

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        auto n = nums.size();
        vector<int> prefixProduct(n, 1);
        vector<int> suffixProduct(n, 1);

        for(size_t i = 1; i < n; i++) {
            prefixProduct[i] = prefixProduct[i - 1] * nums[i - 1];
        }
        // size_t overflow
        for(int i = n - 2; i >= 0; i--) {
            suffixProduct[i] = suffixProduct[i + 1] * nums[i + 1];
        }

        vector<int> res(n, 1);
        for(size_t i = 0; i < n; i++) {
           res[i] *= (prefixProduct[i] * suffixProduct[i]);
        }
        return res;
    }
};