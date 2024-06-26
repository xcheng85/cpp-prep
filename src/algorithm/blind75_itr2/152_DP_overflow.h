// 1. 动态规划问题的一般形式就是求最值
// 2. 求解动态规划的核心问题是穷举
// 3. 正确的「状态转移方程」，
//4.问题是否具备「最优子结构」, 是否能够通过子问题的最值得到原问题的最值

// 最优子结构：可以从子问题的最优结果推出更大规模问题的最优结果。
// 全校的最大分数差可能出现在两个班之间，显然子问题不独立，所以这个问题本身不符合最优子结构
// 最优子结构失效情况，怎么办？策略是：改造问题


// 5. 所以需要你使用「备忘录」或者「DP table」来优化穷举过程，避免不必要的计算

// 明确「状态」-> 明确「选择」 -> 定义 dp 数组/函数的含义。

// O(2^n) recursive --> 子问题就是 f(1), f(2), f(3) ... f(20)，数量和输入规模 n = 20 成正比，所以子问题个数为 O(n)。

// 带备忘录的递归解法的效率已经和迭代的动态规划解法

// 当前状态 n 只和之前的 n-1, n-2 两个状态有关

// 要符合「最优子结构」，子问题间必须互相独立

// 确定「状态」，也就是原问题和子问题中会变化的变量

// 递归树 
//O(k^n)
// 复杂度是 O(kn)。

// memorization: dp 函数体现在函数参数，
// bottom-up 而 dp 数组体现在数组索引：

// 只要通过状态转移方程写出暴力递归解，剩下的也就是优化递归树，消除重叠子问题而已。
// 讲一讲设计动态规划的通用技巧：数学归纳思想。

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