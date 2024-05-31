// palindrome

// alphabatic include number;

class Solution {
public:
    bool isPalindrome(string s) {
        int l = 0, r = s.size() - 1;
        while (l < r) {
            if (!isAlphabatic(s[l])) {
                ++l;
                continue;
            }
            if (!isAlphabatic(s[r])) {
                --r;
                continue;
            }
            if(toLowerCase(s[l]) != toLowerCase(s[r])) {
                return false;
            }
            ++l;
            --r;
        }
        return true;
    }

    bool isAlphabatic(const char& c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    }

    char toLowerCase(const char& c) { 
        if (c >= 'A' && c <= 'Z'){
            return c - 'A' + 'a';
        } else {
            return c;
        }
    }
};