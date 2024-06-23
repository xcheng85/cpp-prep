class Solution {
public:
    int maxProduct(vector<int>& nums) {
        double maxProduct = -numeric_limits<double>::max();
        vector<double> dpMin(nums.size());
        vector<double> dpMax(nums.size());

        dpMin[0] = nums[0];
        dpMax[0] = nums[0];

        maxProduct = max<double>(maxProduct, dpMax[0]);

        for (int i = 1; i < nums.size(); ++i) {
            dpMin[i] = min<double>({ (double)nums[i], nums[i] * dpMin[i-1], nums[i] * dpMax[i-1] });
            dpMax[i] = max<double>({ (double)nums[i], nums[i] * dpMin[i-1], nums[i] * dpMax[i-1] });
            maxProduct = max<double>(maxProduct, dpMax[i]);

            cout << dpMax[i] << endl;
            cout << maxProduct << endl;
        }

        return (int)maxProduct;
    }
};