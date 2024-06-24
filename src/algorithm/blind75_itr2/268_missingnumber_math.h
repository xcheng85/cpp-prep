

class Solution
{
public:
    int missingNumber(vector<int> &nums)
    {
        int n = nums.size();
        // 等差数列 0, 1, 2,..., n
        long expect = (0 + n) * (n + 1) / 2;
        long sum = 0;
        for (int x : nums)
        {
            sum += x;
        }
        return (int)(expect - sum);
    }
};

// 异或运算满足交换律和结合律
