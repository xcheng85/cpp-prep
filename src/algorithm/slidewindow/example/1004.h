
#include <map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

// flip 0 to achieve longtest 1

class Solution
{
public:
    int longestOnes(vector<int> &nums, int k)
    {
        int res = 0;
        int left = 0, right = 0;
        int windowOneCount = 0;
        while (right < nums.size())
        {
            if (nums[right++] == 1)
            {
                windowOneCount++;
            }
            // count of flipping 0
            // shift left pointer
            while (right - left - windowOneCount > k)
            {
                if (nums[left] == 1)
                {
                    windowOneCount--;
                }
                left++;
            }
            res = max(res, right - left);
        }
        return res;
    }
};