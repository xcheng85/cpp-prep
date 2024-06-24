class Solution {
public:
    int climbStairs(int n) {
        if(n == 1) {
            return 1;
        }

        int dp0 = 1, dp1 = 1;
        for(int i = 2; i <= n; ++i) {
            int newdp = dp0 + dp1;
            dp0 = dp1;
            dp1 = newdp;
        }
        return dp1;
    }
};