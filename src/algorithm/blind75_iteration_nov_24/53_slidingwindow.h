class Solution {
public:
    //1. continous sliding window
    //2. [l,r)
    //3. when to shrink
    //4. global optimal
    //5. current state
    int maxSubArray(vector<int>& nums) {
        int l = 0, r = 0; // include nothing
        // 5.
        int sumWindow = 0;
        // 4.
        int gSum = std::numeric_limits<int>::min();

        while(r < nums.size()) {
            // sliding right and update result
            sumWindow += nums[r];
            gSum = std::max(gSum, sumWindow);
            ++r;
            // all the left part is negative contribution
            if(sumWindow - nums[r - 1] < 0 ) {
                //cout << "shrinking left from: " << l << " to " << r-1 << endl; 
                l = r - 1;
                // sliding left, and update result
                sumWindow = nums[l];
                gSum = std::max(gSum, sumWindow);
            }
        }
        return gSum;
    }
};