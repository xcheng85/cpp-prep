// 2169. Count Operations to Obtain Zero

class Solution {
public:
    int countOperations(int num1, int num2) {
        // recursive
        if(num1 < num2) {
            return countOperations(num2, num1);
        }

        // num1 always >= num2
        // base condition 
        if(num2 == 0) {
            return 0;
        }
        if(num2 == 1) {
            return num1;
        }

        auto newNum = num1 - num2;
        return countOperations(std::max(newNum, num2), std::min(newNum, num2)) + 1;
    }
};