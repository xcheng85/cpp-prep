#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<int> numMovesStones(int a, int b, int c)
    {
        // a, b, and c have different values
        //  a = 1, b = 2, c = 5
        vector<int> s{a, b, c};
        sort(begin(s), end(s));
        if (s[2] - s[0] == 2)
            return {0, 0};
            // dt == 1, always one move
        return {min(s[1] - s[0], s[2] - s[1]) <= 2 ? 1 : 2, s[2] - s[0] - 2};
    }
};