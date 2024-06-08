class NumArray {
public:
    NumArray(vector<int>& nums) : _prefixsum(nums.size()+1){
        int sum = 0;
        for(size_t i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            _prefixsum[i +1] = sum;
        }
    }
    
    int sumRange(int left, int right) {
        return _prefixsum[right + 1] - _prefixsum[left];
    }

private:
    vector<int> _prefixsum;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */