// doule pointer from center
// list all the posibility and get the best result

class Solution {
public:
    string longestPalindrome(string s) {
        string longest;
        int maxLength = 0;

        for(size_t i = 0; i < s.size(); ++i) {
            auto len1 = palindromeLength(s, i, i);
            auto len2 = palindromeLength(s, i, i + 1);

            if(len1 > len2 && len1 > maxLength) {
                // substring is needed
                //cout << "new max length: " << len1 << ", center: " << i << endl;
                longest = s.substr(i - len1/2, len1);
                maxLength = len1;
            }
            if(len2 > len1 && len2 > maxLength) {
                // substring is needed
                //cout << "new max length: " << len2 << ", center: " << i << "," << i+1 << endl;
                longest = s.substr(i - (len2 - 2)/2, len2);
                maxLength = len2;
            }
        }
        return longest;
    }

    int palindromeLength(const string& s, int cl, int cr) {
        while(cl >= 0 && cr < s.size()) {
            if(s[cl] != s[cr]) {
                break;
            }
            --cl;
            ++cr;
        }
        // if it is even, -1, 6, 6 - 0 = 6
        // if it is odd, -1, 5, 5 - 0 = 5. both valid
        return cr - (cl + 1);
    }
};