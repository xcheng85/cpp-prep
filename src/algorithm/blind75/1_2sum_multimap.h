#include <map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        multimap<int, int> s;
        for (int i = 0; i < nums.size(); ++i)
        {
            s.insert(make_pair(nums[i], i));
        }
        // if a number is visited, then igore
        unordered_set<int> visited;
        for (const auto &n : nums)
        {
            if (visited.find(n) != visited.end())
            {
                continue;
            }
            auto other = target - n;
            if (other != n)
            {
                if (s.find(other) != s.end())
                {
                    // answer in any order
                    return {s.find(n)->second, s.find(other)->second};
                }
            }
            else
            {
                if (s.count(n) > 1)
                {
                    auto pairOfItr = s.equal_range(n);
                    auto itr1 = pairOfItr.first;
                    auto itr2 = itr1;
                    std::advance(itr2, 1);

                    return {
                        itr1->second,
                        itr2->second};
                }
            }
            visited.insert(n);
            visited.insert(other);
        }
        return {0, 0};
    }
};