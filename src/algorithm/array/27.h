class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if(nums.size() == 0) {
            return 0;
        }

        size_t wPos = 0; 
        size_t currIdx = 0;
        while(currIdx < nums.size()) {
            if(nums[currIdx] != val) {
                if(wPos < currIdx) {
                    nums[wPos++] = nums[currIdx];
                } else {
                    wPos++;
                }
            } else {
                // 
            }
            ++currIdx;
        }
        return wPos;
    }
};