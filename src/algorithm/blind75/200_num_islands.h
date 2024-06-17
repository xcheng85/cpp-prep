#include <vector>
#include <queue>

using namespace std;

class Solution
{
public:
    // it is like multiple source graph
    // course schedules.
    // multiple sources,
    int numIslands(vector<vector<char>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == '1')
                {
                    // source of a graph
                    // a new source
                    ++res;
                    dfs(grid, i, j, m, n);
                }
            }
        }
        return res;
    }

    void dfs(vector<vector<char>> &grid, int i, int j, int m, int n)
    {
        // neighboring are left, right, up, down
        // end condition
        if (i < 0 || i >= m || j < 0 || j >= n)
        {
            return;
        }
        // visited equal
        if (grid[i][j] == '0')
        {
            return;
        }
        // visited, node not path, path is backtracking
        grid[i][j] = '0';

        dfs(grid, i + 1, j, m, n);
        dfs(grid, i, j + 1, m, n);
        dfs(grid, i - 1, j, m, n);
        dfs(grid, i, j - 1, m, n);
    }
};

class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {

                if (grid[i][j] == '1')
                {
                    // source of a graph
                    // a new source
                    ++res;
                    bfs(grid, i, j, m, n);
                }
            }
        }
        return res;
    }

    void bfs(vector<vector<char>> &grid, int srci, int srcj, int m, int n)
    {
        queue<pair<int, int>> q;
        q.push(make_pair(srci, srcj));
        while (!q.empty())
        {
            auto [i, j] = q.front();
            q.pop();
            grid[i][j] = 0;

            if (i > 0 && grid[i - 1][j] == '1')
            {
                // set here can make it faster
                grid[i - 1][j] = 0;
                q.push(make_pair(i - 1, j));
            }
            if (i < m - 1 && grid[i + 1][j] == '1')
            {
                grid[i + 1][j] = 0;
                q.push(make_pair(i + 1, j));
            }
            if (j > 0 && grid[i][j - 1] == '1')
            {
                grid[i][j - 1] = 0;
                q.push(make_pair(i, j - 1));
            }
            if (j < n - 1 && grid[i][j + 1] == '1')
            {
                grid[i][j + 1] = 0;
                q.push(make_pair(i, j + 1));
            }
        }
    }

    void bfs(vector<vector<char>> &grid, int srci, int srcj, int m, int n)
    {
        queue<pair<int, int>> q;
        q.push(make_pair(srci, srcj));
        while (!q.empty())
        {
            queue<pair<int, int>> tmp;
            int n = q.size();
            // advance at the same step
            for (int k = 0; k < n; ++k)
            {
                auto [i, j] = q.front();
                q.pop();
                grid[i][j] = 0;

                if (i > 0 && grid[i - 1][j] == '1')
                {
                    // set here can make it faster
                    // grid[i - 1][j] = 0;
                    tmp.push(make_pair(i - 1, j));
                }
                if (i < m - 1 && grid[i + 1][j] == '1')
                {
                    //grid[i + 1][j] = 0;
                    tmp.push(make_pair(i + 1, j));
                }
                if (j > 0 && grid[i][j - 1] == '1')
                {
                    //grid[i][j - 1] = 0;
                    tmp.push(make_pair(i, j - 1));
                }
                if (j < n - 1 && grid[i][j + 1] == '1')
                {
                    //grid[i][j + 1] = 0;
                    tmp.push(make_pair(i, j + 1));
                }
            }
            q.swap(tmp);
        }
    }
};