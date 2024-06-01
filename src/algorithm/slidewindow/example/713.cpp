// multiple case to reset left/right and restart the sliding window

class Solution {
public:
    // hint continous subarray
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int count = 0;
        int product = 1;

        int left = 0, right = 0;
        while(right < nums.size() ) {
            auto num = nums[right++]; // [left, right)
            product *= num;
            if(product < k) {
                //cout << "l: " << left << "r: " << right << endl;
                ++count;
                if(right == nums.size()) {
                    ++left;
                    right = left;
                    product = 1;
                }
            } else {
                // current left is done and reset left and right at the same place
                ++left;
                right = left;
                product = 1;
            }
        }
        return count;
    }
};