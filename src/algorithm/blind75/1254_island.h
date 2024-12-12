#include <vector>
#include <queue>

using namespace std;

class Solution
{
public:
    int closedIsland(vector<vector<int>> &grid)
    {
        // boundary 0 flip to 1
        int m = grid.size();
        int n = grid[0].size();

        // rule out the island on the edge
        // flip with out counting
        // r: 0
        for (int c = 0; c < n; ++c)
        {
            // all the sources in the boundary
            floodfillDfs(grid, 0, c, m, n);
            floodfillDfs(grid, m - 1, c, m, n);
        }
        // two boundary cols
        for (int r = 0; r < m; ++r)
        {
            floodfillDfs(grid, r, 0, m, n);
            floodfillDfs(grid, r, n - 1, m, n);
        }

        // normal multi-source based dfs
        int res = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 0)
                {
                    // one island src
                    ++res;
                    floodfillDfs(grid, i, j, m, n);
                }
            }
        }

        return res;
    }

    // like preorder traversal, there is a root action and then iterate all the children
    void floodfillDfs(vector<vector<int>> &grid, int srci, int srcj, int m, int n)
    {
        // two early branch trim
        if (srci < 0 || srci >= m || srcj < 0 || srcj >= n)
        {
            return;
        }
        // 1: means visited in this problem or it is a 1 in the original input, 
        // it does not matter, because this tree branch is done. 
        if (grid[srci][srcj] == 1)
        {
            return;
        }
        // avoid re-visited
        grid[srci][srcj] = 1;

        // flood neighbor
        floodfillDfs(grid, srci - 1, srcj, m, n);
        floodfillDfs(grid, srci + 1, srcj, m, n);
        floodfillDfs(grid, srci, srcj - 1, m, n);
        floodfillDfs(grid, srci, srcj + 1, m, n);
    }
};