#include <vector>
#include <algorithm>
#include <numeric>
// Given an array of positive integers nums and a positive integer target, return the minimal length of a
// subarray
//  whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.

using namespace std;

// 1. subarray -> sliding window
// 2. try each case from (every 1, every 2, every 3, every 4, ...)

// minSubArrayLen(7) = std::min({minSubArrayLen(7-2), })

// greater than or equal to target

// subarray is continous

// target = 7, nums = [2,3,1,2,4,3]

// state of the window
// global best result

// l = 0, r = 1, 2
// l = 0, r = 2, [2,3] = 5
// l = 0, r = 3, [2, 3, 1] = 6
// l = 0, r = 4, [2, 3, 1, 2] = 8, shift left (store temporarily result)  4
// l = 1, r = 4, 6, stop shift left
// l= 1, r = 5, 10,  (result 4)
// l =2, r = 5, 7 (result 3)
// l = 3, r= 5, 6,
// l = 3, r = 6, 9 (result3)
// l = 4, r = 6, 7 (result 2)
// l = 5, r = 6, 3
// r = 7 , terminate

// two early return
// 1. if the res already hit 1
// 2. if the sum < target

class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        auto sum = std::reduce(nums.begin(), nums.end());
        if(sum < target) 
            return 0;
        
        //accumulate(A.begin(), A.end(), 0);
        // compare with target must >= , then update res
        int sumWindow = 0;
        // worst possible
        int res = nums.size();
        // [l, r)
        int l = 0, r = 0; 
        while(r < nums.size()){
            // expand window rightwise
            sumWindow += nums[r];
            ++r;
            while(sumWindow >= target) {
                // try to update res, if hit 
                res = std::min(res, r - l);
                if(res == 1) {
                    return res; // cannot be better
                }
                // shrink window leftwise
                sumWindow -= nums[l++];
            }
        }
        return res;
    }
};