#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    // Small half:    4 . 3 . 2 . 1 . 0 .
    // Large half:    . 9 . 8 . 7 . 6 . 5
    // ----------------------------------
    // Together:      4 9 3 8 2 7 1 6 0 5

    void wiggleSort(vector<int> &nums)
    {
        vector<int> sorted(nums);

        sort(sorted.begin(), sorted.end());

        // even position from small half: from j 
        // odd position from larger half: from k, i/2 + 1, ensure even length >= odd length

        for (int i = nums.size() - 1, j = 0, k = i / 2 + 1; i >= 0; i--)
            nums[i] = sorted[i & 1 ? k++ : j++];
    }
};