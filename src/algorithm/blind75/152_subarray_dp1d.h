#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// product overflow: use double
// double negative min value is: double res = -numeric_limits<double>::max();

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        vector<double> dpMin(n);
        vector<double> dpMax(n);

        // base case
        dpMin[0] = nums[0];
        dpMax[0] = nums[0];

        for (int i = 1; i < n; i++) {
            // nums[i], consider 0 case
            const auto p = minmax<double>({dpMax[i - 1] * nums[i], dpMin[i - 1] * nums[i], (double)nums[i]});
            dpMin[i] = p.first;
            dpMax[i] = p.second;
        }

        double res = -numeric_limits<double>::max();
        for (int i = 0; i < n; i++) {
            res = max(res, dpMax[i]);
        }
        return (int)res;
    }
};
