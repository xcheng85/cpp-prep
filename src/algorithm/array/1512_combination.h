class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        // nums: [1, 100]
        int counter[101];
        for(const auto& n : nums) {
            ++counter[n];
        }

        // memset(_factorial, sizeof(_factorial), 0);
        int res= 0;

        for(int i = 1; i < 101; ++i) {
            if(counter[i] > 1) {
                int n = counter[i];
                // optimize of nCr
                res += (n * (n-1) / 2);
            }
        }
        return res;
    }
    // // == n * (n - 1) / 2
    // // extract 2 (pair) from n
    // long long Combination(int n, int r) {
    //     return factorial(n) / (r * factorial(n-r));
    // }

    // long long  factorial(int n) {
    //     if(_factorial[n] != 0) {
    //         return _factorial[n];
    //     } else {
    //         if(n <= 1) {
    //             return 1;
    //         }
    //         long long res = n * factorial(n - 1);
    //         _factorial[n] = res;
    //         return res;
    //     }
    // }

private: 
    //long long _factorial[101];
};