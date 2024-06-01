class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        long long res = 0;

        int maxvalue = *(max_element(nums.begin(), nums.end()));

        int left = 0, right = 0;

        int countK = 0;

        while (right < nums.size()) {
            auto c = nums[right++];
            if (c == maxvalue) {
                ++countK;
            }
            if (countK == k) {
                res += (nums.size() - right + 1);
                // move left
                while (countK == k) {
                    auto d = nums[left++];
                    if (d != maxvalue) {
                        res += (nums.size() - right + 1);
                    } else {
                        --countK; // break and right start to move
                    }
                }
            }
        }
        return res;
    }
};