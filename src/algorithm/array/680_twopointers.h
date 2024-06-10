class Solution
{
public:
    bool validPalindrome(string s)
    {
        int l = 0, r = s.size() - 1;
        while (r - l > 1)
        {
            if (s[l] != s[r])
            {
                // try both otions, delete left or right
                return isPalindrome(s, l + 1, r) || isPalindrome(s, l, r - 1);
            }
            ++l;
            --r;
        }
        return true;
    }

    bool isPalindrome(const string &s, int i, int j)
    {
        while (i < j)
        {
            if (s[i++] != s[j--])
            {
                return false;
            }
        }
        return true;
    }
};