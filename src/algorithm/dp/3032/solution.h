// a = 1, b = 20

// 1

// base case:

// 1, 11, 111

// 11 is the subproblme of 111

#include <unordered_set>
#include <string>

class Solution
{
public:
    int numberCount(int a, int b)
    {
        int res = 0;
        for(int i{a}; i <= b; ++i) {
            if(!duplicateNumber(std::to_string(i))) {
                ++res;
            }
        }
        return res;
    }
    // dp with memorization
    bool duplicateNumber(std::string n)
    {
        if (_dupSet.find(n) != _dupSet.end())
        {
            return true;
        }
        // base case
        if (n.size() == 1)
        {
            return false;
        }
        else if (n.size() == 2)
        {
            if (n[0] == n[1])
            {
                _dupSet.insert(n);
                return true;
            }
            return false;
        }
        else
        {
            // 211
            // 2 and 11
            // sub problem
            auto sub = n.substr(1);
            if (duplicateNumber(sub))
            {
                _dupSet.insert(n);
                return true;
            }
            for (const auto &c : sub)
            {
                if (c == n[0])
                {
                    _dupSet.insert(n);
                    return true;
                }
            }
            return false;
        }
    }

private:
    std::unordered_set<std::string> _dupSet;
};