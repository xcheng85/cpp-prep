// nums 中可能有多对儿元素之和都等于 target，请你的算法返回所有和为 target 的元素对儿
#include <map>
#include <algorithm>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
// nums = [1,3,1,2,2,3], target = 4，那么算法返回的结果就是：[[1,3],[2,2]]
vector<vector<int>> twoSumValueMultiPairsNoDuplicates(vector<int> &sorted, int l, int target)
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
            while(l + 1 < sorted.size() ) {
                if(sorted[l] == sorted[l + 1]) {
                    ++l;
                }
            }
        }
    }
    return res;
}