 & (and), | (or), ~ (not) and ^ (exclusive-or, xor) and shift operators a << b and a >> b.

Set union A | B

Set intersection A & B

Set subtraction A & ~B

Set negation ALL_BITS ^ A or ~A

Set bit A |= 1 << bit

Clear bit A &= ~(1 << bit)

Test bit (A & 1 << bit) != 0

Extract last bit A&-A or A&~(A-1) or x^(x&(x-1))

Remove last bit A&(A-1)

Get all 1-bits ~0

Count the number of ones in the binary representation of the given number

class Solution {
public:
    int hammingWeight(int n) {
        int count = 0;
        while (n) {
            cout << n << endl;
            // every remove rightmost 1
            n = n & (n - 1);
            count++;
        }
        return count;
    }
};

xor + communicative 

268, missing number

[0, n]
[0, 1, 3]

not missing case

0 ^ 0 ^ 1 ^ 1 ^ 2 ^ 2 ^ 3 ^ 3

0 ^ 0 ^ 1 ^ 1 ^ 2 ^ 3 ^ 3

missing is 2


3,0,1]