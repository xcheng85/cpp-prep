#include <string>
#include <iostream>
using namespace std;

// two edge cases
class Solution {
public:
   string addStrings(string num1, string num2) {
        if(num1.size() > num2.size()) {
            return addStrings(num2, num1);
        }
        // ensure num1.size() <= num2.size();

        int n = num1.size();
        bool carry = false;
        string result;
        for(int i = 0; i < n; i++) {
            auto n1 = num1[num1.size() - 1 - i] - '0';
            auto n2 = num2[num2.size() - 1 - i] - '0';
            auto s = n1 + n2 + (carry ? 1 : 0);
            // std::cout << "n1: " << n1 << std::endl;
            // std::cout << "n2: " << n2 << std::endl;
            // std::cout << s << std::endl;
            carry = s / 10;
            result.push_back(s % 10 + '0');
        }
        
        // the rest of num2
        for(int i = n; i < num2.size(); i++) {
            auto n2 = num2[num2.size() - 1 - i] - '0';
            auto s = n2 + (carry ? 1 : 0);
            carry = s / 10;
            result.push_back(s % 10 + '0');
        }
        if(carry) {
            result.push_back('1');
        }
        // flip
        for(int i = 0; i < result.size()/2; i++) {
            std::swap(result[i], result[result.size()-1-i]);
        }
        return result;
    }
};