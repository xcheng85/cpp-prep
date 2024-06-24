class Solution {
public:
    int hammingWeight(int n) {
        int count = 0;
        while (n) {
            // every remove rightmost 1
            n = n & (n - 1);
            count++;
        }
        return count;
    }
};