#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int> &nums)
    {
        // slide window
        double maxSubarrayProduct = -numeric_limits<double>::max();
        int l = 0, r = 0;
        double slidingProduct = 1;
        // [l, r)
        while (r < nums.size())
        {
            //cout << "sliding window: [" << l << "," << r << ")" << endl;

             // [1, -2, 2, 3, 0, 2, 2, 1, 0, 1, 2, 3]
            // condition to move left pointer: 
            // 1. run into 0, [1, -2, 2, 3], left should move from 1 to 2, this is local max between [, 0]
            // 2. restart from two zeros: [0, 2, 2, 1, 0]
            // 3. 0 to end: [0, 1, 2, 3]
            if (nums[r] == 0 && slidingProduct < 0 && l < r - 1)
            {
                //cout << "left pointer narrowing" << endl;
                // l will be at r - 1
                slidingProduct /= nums[l++];
                maxSubarrayProduct = max(maxSubarrayProduct, slidingProduct);
            }
            else if (nums[r] == 0) // slidingProduct > 0
            {
                //cout << "both pointers jump 0" << endl;
                // [-1, 0]
class Solution
{
public:
    //[2,3,-2,4]
    int maxProduct(vector<int> &nums)
    {
        // slide window
        double maxSubarrayProduct = -numeric_limits<double>::max();
        int l = 0, r = 0;
        double slidingProduct = 1;
        // [l, r)
        while (r < nums.size())
        {
            cout << "sliding window: [" << l << "," << r << ")" << endl;

             // [1, -2, 2, 3, 0, 2, 2, 1, 0, 1, 2, 3]
            // condition to move left pointer: 
            // 1. run into 0, [1, -2, 2, 3], left should move from 1 to 2, this is local max between [, 0]
            // 2. restart from two zeros: [0, 2, 2, 1, 0]
            // 3. 0 to end: [0, 1, 2, 3]
            if (nums[r] == 0 && slidingProduct < 0 && l < r - 1)
            {
                // l will be at r - 1
                slidingProduct /= nums[l++];
                maxSubarrayProduct = max(maxSubarrayProduct, slidingProduct);
            }
            else if (nums[r] == 0) // slidingProduct > 0
            {
                // [-1, 0]
                maxSubarrayProduct = max(maxSubarrayProduct, 0);
                // l and r cross the 0 and restart
                ++r;
                l = r;
                slidingProduct = 1;
            }
            else
            {
                // non-zero case
                // move r pointer
                slidingProduct *= nums[r++];
                maxSubarrayProduct = max(maxSubarrayProduct, 0);
            }
        }

        // same logic as run into 0
        for (; slidingProduct < 0 && l < nums.size() - 1; ++l)
        {
            slidingProduct /= nums[l];
            maxSubarrayProduct = max(maxSubarrayProduct, slidingProduct);
        }

        return (int)maxSubarrayProduct;
    }
};

                maxSubarrayProduct = max<double>(maxSubarrayProduct, 0.0);
                // l and r cross the 0 and restart
                ++r;
                l = r;
                slidingProduct = 1;
            }
            else
            {
                //cout << "right pointer expanding" << endl;
                // non-zero case
                // move r pointer
                slidingProduct *= nums[r++];
                maxSubarrayProduct = max<double>(maxSubarrayProduct, slidingProduct);
            }
        }

        // same logic as run into 0
        for (; slidingProduct < 0 && l < nums.size() - 1; ++l)
        {
            //cout << "final: left pointer narrowing" << endl;
            slidingProduct /= nums[l];
            maxSubarrayProduct = max<double>(maxSubarrayProduct, slidingProduct);
        }

        return (int)maxSubarrayProduct;
    }
};
