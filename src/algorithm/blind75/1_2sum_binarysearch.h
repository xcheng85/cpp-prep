#include <map>
#include <algorithm>
#include <unordered_set>
#include <utility>
#include <vector>

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
        // ascending
        sort(numsWithIdx.begin(), numsWithIdx.end());

        for (int i = 0; i < numsWithIdx.size(); ++i)
        {
            const auto &[v1, index1] = numsWithIdx[i];

            const auto v2 = target - v1;
            const auto &[v, index2] = binarysearch(numsWithIdx, i + 1, numsWithIdx.size() - 1, v2);
            if (index2 != -1)
            {
                return {index1, index2};
            }
        }
        return {0, -1};
    }

    pair<int, int> binarysearch(
        const vector<pair<int, int>> &numsWithIdx,
        int l, int r,
        int target)
    {
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (target < numsWithIdx[mid].first)
            {
                r = mid - 1;
            }
            else if (target > numsWithIdx[mid].first)
            {
                l = mid + 1;
            }
            else
            {
                return numsWithIdx[mid];
            }
        }
        return {0, -1};
    }
};