#include <vector>
using namespace std;

// recursion with duplication sub-problems
class Solution {
public:
    int climbStairs(int n) {
        if(n == 1) 
            return 1;
        if(n == 2) 
            return 2;
        return climbStairs(n-1) + climbStairs(n-2);
    }
};

// memorization
class Solution {
public:
    int climbStairs(int n) {
        if(n == 1) 
            return 1;
        if(n == 2) 
            return 2;
        int dp0 = 1, dp1 = 2;
        int dp;
        for(int i = 3; i <= n; ++i) {
            dp = dp0 + dp1; 
            dp0 = dp1;
            dp1 = dp;
        }
        return dp;
    }
};

