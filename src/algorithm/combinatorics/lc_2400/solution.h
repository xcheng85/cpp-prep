// 1. delta between start and end

// 2. check if the answer exists: 

// one direction move must = other direction move + k

// (totalStepAllowed - k) % 2 == 0 

// C(k, (totalStepAllowed - k)/2)

class Solution {
public:
    int numberOfWays(int startPos, int endPos, int k) {
        int delta = abs(startPos - endPos);
        int lessStep = (k - delta);
        if (lessStep % 2 > 0) {
            return 0;
        }
        lessStep /= 2;
        int nn = lessStep + 1;

        // cout << k << endl;
        // cout << lessStep << endl;

        unsigned long long res{1};
        unsigned long long mod = (pow(10, 9) + 7);
        for (int i = 1; i <= k - lessStep; ++i) {
            cout << i << endl;
            res *= nn;
            res %= mod;
            res /= i;
            ++nn;
        }
        cout << res << endl;
       
        return res ;
    }
};