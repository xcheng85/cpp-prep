// Assumption: You may assume all four edges of the grid are all surrounded by water.
//  '1's (land) and '0's (water)

// An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically

// assumpation is key,
// undirected graph, all the sources are 1.
// merge sources

// update grid from 1-->0 to record visited.

#include <vector>
#include <array>
using namespace std;

class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int res = 0;
        int m = grid.size(), n = grid[0].size();
        for (int r = 0; r < m; r++)
        {
            for (int c = 0; c < n; c++)
            {
                // source of graph
                if (grid[r][c] == '1')
                {
                    ++res;
                    dfs(grid, r, c);
                }
            }
        }
        return res;
    }

    // from a source
    void dfs(vector<vector<char>> &grid, int r, int c)
    {
        // cout << "r: " << r << ", c: " << c << endl;
        if (r >= grid.size() || c >= grid[0].size() || r < 0 || c < 0)
        {
            return;
        }
        if (grid[r][c] == '0')
        {
            return;
        }
        grid[r][c] = '0';
        for (const auto &[rOffset, cOffset] : _dirs)
        {
            dfs(grid, r + rOffset, c + cOffset);
        }
    }

private:
    const std::array<std::pair<int, int>, 4> _dirs{
        make_pair(-1, 0),
        make_pair(1, 0),
        make_pair(0, -1),
        make_pair(0, 1),
    };
};