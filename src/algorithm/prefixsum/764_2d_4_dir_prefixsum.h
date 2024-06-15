#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution
{
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>> &mines)
    {
        vector<vector<int>> up(n, vector<int>(n, 0)),
            down(n, vector<int>(n, 0)), left(n, vector<int>(n, 0)),
            right(n, vector<int>(n, 0));

        // I need to easily tell if grid at [i,j] is 0
        // mapping i,j to linear offset

        unordered_set<size_t> zeroCacheSet;
        for (auto &p : mines)
        {
            size_t offset = p[0] * n + p[1];
            zeroCacheSet.insert(offset);
        }

        // below code that includes 4 double loops are used for storing prefix
        // sum of 1's in left, right,up and down direction.
        for (int j = 0; j < n; j++)
        {
            for (int i = 0; i < n; i++)
            {
                if (zeroCacheSet.find(i * n + j) != zeroCacheSet.end())
                    up[i][j] = 0;
                else if (i == 0)
                    up[i][j] = 1;
                else
                    up[i][j] = 1 + up[i - 1][j];
            }
        }

        for (int j = 0; j < n; j++)
        {
            for (int i = n - 1; i >= 0; i--)
            {
                if (zeroCacheSet.find(i * n + j) != zeroCacheSet.end())
                    down[i][j] = 0;
                else if (i == n - 1)
                    down[i][j] = 1;
                else
                    down[i][j] = 1 + down[i + 1][j];
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (zeroCacheSet.find(i * n + j) != zeroCacheSet.end())
                    left[i][j] = 0;
                else if (j == 0)
                    left[i][j] = 1;
                else
                    left[i][j] = 1 + left[i][j - 1];
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = n - 1; j >= 0; j--)
            {
                if (zeroCacheSet.find(i * n + j) != zeroCacheSet.end())
                    right[i][j] = 0;
                else if (j == n - 1)
                    right[i][j] = 1;
                else
                    right[i][j] = 1 + right[i][j + 1];
            }
        }

        int res = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                res = max(res, min(left[i][j], min(right[i][j], min(up[i][j], down[i][j]))));
            }
        }
        return res;
    }
};