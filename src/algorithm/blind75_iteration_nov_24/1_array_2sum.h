// 1. only 1 solution
// 2. element use once

#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
class Solution {
public:
    // two pointers
     vector<int> twoSum(vector<int> &nums, int target)
    {
        // original index could be ignored
        // default ascending
        vector<std::pair<int, int>> numsWithIndex;
        numsWithIndex.reserve(nums.size());
        for(size_t i = 0; i < nums.size(); ++i) {
            numsWithIndex.emplace_back(make_pair(nums[i], i));
        }
        // sorting with pairs took the first
        sort(numsWithIndex.begin(), numsWithIndex.end());
        int l = 0, r = numsWithIndex.size() - 1;
        while (l < r)
        {
            auto sum = numsWithIndex[l].first + numsWithIndex[r].first;
            if (sum == target)
            {
                break;
            }
            else if (sum > target)
            {
                --r;
            }
            else
            {
                ++l;
            }
        }
        return {numsWithIndex[l].second, numsWithIndex[r].second};
    }
};