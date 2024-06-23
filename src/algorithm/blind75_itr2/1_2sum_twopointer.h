class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<pair<int, int>> numsWithIndex(nums.size());
        for(int i = 0; i < numsWithIndex.size(); ++i) {
            numsWithIndex[i].first = nums[i];
            numsWithIndex[i].second = i;
        }

        sort(numsWithIndex.begin(), numsWithIndex.end());

        // two pointer
        int l = 0, r = numsWithIndex.size() - 1;
        //  you may not use the same element twice
        while(l < r) {
            if(numsWithIndex[l].first + numsWithIndex[r].first == target) {
                return {numsWithIndex[l].second, numsWithIndex[r].second};
            } else if(numsWithIndex[l].first + numsWithIndex[r].first < target) {
                ++l;
            } else {
                --r;
            }
        }
        return {-1, -1};
    }
};