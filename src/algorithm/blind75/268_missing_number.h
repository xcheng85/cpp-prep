// bit xor

// Index	0	1	2	3
// Value	0	1	3	4
// missing=4∧(0∧0)∧(1∧1)∧(2∧3)∧(3∧4)=(4∧4)∧(0∧0)∧(1∧1)∧(3∧3)∧2=0∧0∧0∧0∧2=2\begin{aligned} missing &= 4 \wedge (0 \wedge 0) \wedge (1 \wedge 1) \wedge (2 \wedge 3) \wedge (3 \wedge 4) \\ &= (4 \wedge 4) \wedge (0 \wedge 0) \wedge (1 \wedge 1) \wedge (3 \wedge 3) \wedge 2 \\ &= 0 \wedge 0 \wedge 0 \wedge 0 \wedge 2 \\ &= 2 \end{aligned}
// missing
// ​
  
// =4∧(0∧0)∧(1∧1)∧(2∧3)∧(3∧4)
// =(4∧4)∧(0∧0)∧(1∧1)∧(3∧3)∧2
// =0∧0∧0∧0∧2
// =2
// ​
 
// [0, n] is the input
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int res = n; 
        for(int i = 0; i < n; ++i) {
            res ^= i;
            res ^= nums[i];
        }
        return res;
    }
};