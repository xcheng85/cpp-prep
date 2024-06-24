//// 异或运算满足交换律和结合律
int missingNumber(vector<int>& nums) {
    int n = nums.size();
    int res = 0;
    // 先和新补的索引异或一下
    res ^= n;
    // 和其他的元素、索引做异或
    for (int i = 0; i < n; i++)
        res ^= i ^ nums[i];
    return res;
}