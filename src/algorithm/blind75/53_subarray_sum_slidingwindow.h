#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // slide window
        // don't forget negative value
        int maxSubarraySum = numeric_limits<int>::min();
        int l = 0, r = 0;
        int slidingSum = 0;

        while (r < nums.size()) {
            // move right pointer first
            // [0, 1)
            auto c = nums[r++];
            slidingSum += c;

            maxSubarraySum = max(maxSubarraySum, slidingSum);
            //cout << "window: [" << l << ", " <<r << ")" <<endl;
            // when to move left pointer
            // last element is non-negative contribution, just leave that one
            if (slidingSum < 0 || nums[r - 1] >= slidingSum) {
                
                slidingSum = nums[r - 1];
                int tmp = l;
                l = r - 1;
                maxSubarraySum = max(maxSubarraySum, slidingSum);
                //cout << "left moving from " << nums[tmp] << " to " << nums[l] << endl;
            }
        }

        return maxSubarraySum;
    }
};
