#include <bitset>
#include <iostream>

using namespace std;

class Solution {
public:
    int getSum(int a, int b) {
        std::bitset<11> t1(a); // convent number into bit array
        std::bitset<11> t2(b); // convent number into bit array
        std::bitset<12> res;
        // 1’s Complement Method :
        // -1000: 10000011000
        // 1000:  01111101000

        // 111111111010
        // 1 flip the rest
        // 000000101
        std::cout << "t1 binary is " << t1 << std::endl;
        std::cout << "t2 binary is " << t2 << std::endl;
        bool offset = false;
        for (int i = 0; i < 12; ++i) {
            if (t1[i] == 0 && t2[i] == 0 && offset) {
                res.set(i);
                offset = false;
            } else if (t1[i] == 1 && t2[i] == 1) {
                if (offset) {
                    res.set(i);
                } else {
                    offset = true;
                }
            } else if (t1[i] == 1 || t2[i] == 1) {
                if (offset) {

                } else {
                    res.set(i);
                }
            }
        }
        std::cout << "binary is " << res << std::endl;
        // -0 and +0 case
        auto isNegative = res.test(11);
        cout << "isNegative: " << isNegative << endl;
        res.set(11, 1);
        // Checks if all bits are set to true.
        if(isNegative && res.all()) {
            // -0 case
            return 0;
        }
        res.set(11, 0);
        if(isNegative == 1 && res.none()) {
            // -0 case
            return 0;
        }

        //other case
        if(isNegative ) {
            cout << "flip" << endl;
            res.flip();
            res.set(11, 0);
        } 
        std::cout << "binary is " << res << std::endl;
        return res.to_ulong();
    }
};