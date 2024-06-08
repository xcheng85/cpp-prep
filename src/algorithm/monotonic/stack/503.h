class Solution {
public:
    // concat two arrays, and minus 
    vector<int> nextGreaterElements(vector<int>& nums) {
        int s = nums.size();
        nums.resize(2 * nums.size());
        for(int i = s; i < nums.size(); ++i) {
            nums[i] = nums[ i - s];
        }
        // copy(nums.begin(), nums.end(), ostream_iterator<int>(cout, " "));
        // cout << endl; 
        
        // 
        vector<int> nextGreater(nums.size());
        stack<int> increasingS;
        for(int i = nums.size() - 1; i >= 0; --i) {
            int curr = nums[i];
            while(!increasingS.empty() && increasingS.top() <= curr) {
                increasingS.pop();
            }
            if(increasingS.empty()) {
                nextGreater[i] = -1;
            } else {
                nextGreater[i] = increasingS.top();
            }
            increasingS.emplace(curr);
        }
        // copy(nextGreater.begin(), nextGreater.end(), ostream_iterator<int>(cout, " "));
        // cout << endl; 
        // vector<int> res(s);
        // res[s-1] = nextGreater[s-1];
        // for(int i = 0; i < s - 1; ++i) {
        //     res[i] = nextGreater[i + s];
        // }
        // ctor with pair of iter
        return vector<int>(nextGreater.begin(), nextGreater.begin() + s);
    }

};