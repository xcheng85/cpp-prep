#include <vector>

// row 1: 1

// row 2: 11

// row 3: 1 2 1           1:    0 + 1      extra memory: 1

// row 4: 1 3 3 1         1:  0 + 1   2: 1 + 2   2

// row 5: 1 0+1, 1 + 2, 2 + 3, 1             3

// extra memory 5 - 2
using namespace std;

class Solution
{
public:
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> res(numRows);

        for (int r = 1; r <= numRows; ++r)
        {
            for (int i = 0; i < r; ++i)
            {
                if (i == 0 || i == r - 1)
                {
                    res[r - 1].emplace_back(1);
                }
                else
                {
                    if (r < 3)
                    {
                        continue;
                    }
                    else
                    {
                        res[r - 1].emplace_back(res[r - 2][i - 1] + res[r - 2][i]);
                    }
                }
            }
        }
        return res;
    }
};