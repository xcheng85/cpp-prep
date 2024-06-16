#include <map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        vector<pair<int, int>> numsWithIdx;
        numsWithIdx.reserve(nums.size());
        for (int i = 0; i < nums.size(); ++i)
        {
            numsWithIdx.push_back(make_pair(nums[i], i));
        }
        sort(numsWithIdx.begin(), numsWithIdx.end());
        // 左右指针
        int l = 0, r = numsWithIdx.size() - 1;
        // number cannot be reused
        while (l < r)
        {
            int sum = numsWithIdx[l].first + numsWithIdx[r].first;
            // 根据 sum 和 target 的比较，移动左右指针
            if (sum < target)
            {
                l++;
            }
            else if (sum > target)
            {
                r--;
            }
            else if (sum == target)
            {
                return {numsWithIdx[l].second, numsWithIdx[r].second};
            }
        }
        return {};
    }
};