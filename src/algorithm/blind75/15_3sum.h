#include <map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        // based on two sum
        int i = 0;
        int sumTarget = 0;
        while (i < nums.size())
        {
            auto other = twoSumValue(nums, i + 1, sumTarget - nums[i]);
            if (other.size() > 0)
            {
               // std::move(other.begin(), other.end(), std::back_inserter(res));
               for(const auto& v : other) {
                    res.push_back({nums[i], v[0], v[1]});
               }
            }
            ++i;
            while (i < nums.size() && nums[i] == nums[i - 1])
            {
                ++i;
            }
        }
        return res;
    }

    vector<vector<int>> twoSumValue(vector<int> &sorted, int l, int target)
    {
        // 1, 1, 2, 2, 3, 3
        // 1, 3
        // skip 1: 2, 2. skip 2,
        // 3, there is nothing on the left side

        vector<vector<int>> res;
        // 左右指针
        int r = sorted.size() - 1;
        // number cannot be reused
        while (l < r)
        {
            int sum = sorted[l] + sorted[r];
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
                res.push_back({sorted[l], sorted[r]});

                ++l;

                while (l < sorted.size() && sorted[l] == sorted[l - 1])
                {
                    ++l;
                }
            }
        }
        return res;
    }
};