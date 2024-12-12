#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>
using namespace std;

// 先用 for 循环遍历棋盘的四边，用 DFS 算法把那些与边界相连的 O 换成一个特殊字符，
// 比如 #；然后再遍历整个棋盘，把剩下的 O 换成 X，把 # 恢复成 O。这样就能完成题目的要求，时间复杂度 O(MN)。


// the bottom region is not captured because it is on the edge of the board and cannot be surrounded.

class Solution
{
public:
    void solve(vector<vector<char>> &board)
    {
        // for edges
        int m = board.size();
        int n = board[0].size();
        for (int c = 0; c < n; ++c)
        {
            dfs(board, 0, c, 'O', '#');
            dfs(board, m - 1, c, 'O', '#');
        }
        for (int r = 0; r < m; ++r)
        {
            dfs(board, r, 0, 'O', '#');
            dfs(board, r, n - 1, 'O', '#');
        }

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (board[i][j] = 'O')
                {
                    dfs(board, i, j, 'O', 'X');
                }
            }
        }

        // revert #
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (board[i][j] == '#')
                {
                    board[i][j] == 'O';
                }
            }
        }
    }

    void dfs(vector<vector<char>> &board, int i, int j, char replaced, char replace)
    {
        // boundary
        int m = board.size(), n = board[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n)
        {
            return;
        }

        // not visited
        if (board[i][j] == replaced)
        {
            // A cell is connected to adjacent cells horizontally or vertically.
            board[i][j] = replace;

            dfs(board, i - 1, j, replaced, replace);
            dfs(board, i + 1, j, replaced, replace);
            dfs(board, i, j - 1, replaced, replace);
            dfs(board, i, j + 1, replaced, replace);
        }
    }
};

// one dummy node to filter out all the "O" in the boundary
// 2d coordinates to 1d mapping + 1 dummy node

class UnionSet
{
public:
    UnionSet(int n) : _parents(n, -1), _size(n, 1)
    {
        for (int i = 0; i < n; ++i)
        {
            // each one is in spearate set
            _parents[i] = i;
        }
        // initially, every node is in its own set
        _setCount = n;
    }

    void unionSets(int nodeIdx1, int nodeIdx2)
    {
        int p1 = parent(nodeIdx1);
        int p2 = parent(nodeIdx2);

        // unbalance
        // if(p1 != p2)
        //      _parents[p1] = p2;
        // already in one set, early return
        if (p1 == p2)
            return;

        if (_size[p1] > _size[p2])
        {
            //// 小树接到大树下面，较平衡
            _parents[p2] = p1;
            _size[p1] += _size[p2];
        }
        else
        {
            _parents[p1] = p2;
            _size[p2] += _size[p1];
        }
        --_setCount; // 两个分量合二为一
    }

    int parent(int nodeIdx)
    {
        int currentNodeIdx = nodeIdx;
        while (_parents[currentNodeIdx] != currentNodeIdx)
        {
            currentNodeIdx = _parents[currentNodeIdx];
        }
        return currentNodeIdx;
    }

    inline auto setCount() const
    {
        return _setCount;
    }

    bool isConnected(int nodeIdx1, int nodeIdx2)
    {
        int p1 = parent(nodeIdx1);
        int p2 = parent(nodeIdx2);

        return p1 == p2;
    }

private:
    vector<int> _parents;

    vector<int> _size; // for balance of tree

    int _setCount;
};

class SolutionUnionSet
{
public:
    void solve(vector<vector<char>> &board)
    {
        int m = board.size(), n = board[0].size();

        UnionSet us(m * n + 1);
        const int dummyNodeIndex = m * n; // last one

        // for (int i = 0; i < m; i++) {
        //     if (board[i][0] == 'O')
        //         uf.union(i * n, dummy);
        //     if (board[i][n - 1] == 'O')
        //         uf.union(i * n + n - 1, dummy);
        // }
        // // 将首行和末行的 O 与 dummy 连通
        // for (int j = 0; j < n; j++) {
        //     if (board[0][j] == 'O')
        //         uf.union(j, dummy);
        //     if (board[m - 1][j] == 'O')
        //         uf.union(n * (m - 1) + j, dummy);

        // first and last line
        for (int c = 0; c < n; ++c)
        {
            if (board[0][c] == 'O')
            {
                int nodeIdx = 0 * n + c;
                us.unionSets(nodeIdx, dummyNodeIndex);
            }

            if (board[m - 1][c] == 'O')
            {
                int nodeIdx = (m - 1) * n + c;
                us.unionSets(nodeIdx, dummyNodeIndex);
            }

            // dfs(board, 0, c, 'O', '#');
            // dfs(board, m - 1, c, 'O', '#');
        }
        // first and last column
        for (int r = 0; r < m; ++r)
        {
            if (board[r][0] == 'O')
            {
                int nodeIdx = r * n;
                us.unionSets(nodeIdx, dummyNodeIndex);
            }

            if (board[r][n - 1] == 'O')
            {
                int nodeIdx = r * n + n - 1;
                us.unionSets(nodeIdx, dummyNodeIndex);
            }
        }

        vector<pair<int, int>> d{{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
        // boudary is already calculated and has no contribution
        for (int i = 1; i < m - 1; i++)
            for (int j = 1; j < n - 1; j++)
                // merge 00
                if (board[i][j] == 'O')
                    for (int k = 0; k < 4; k++)
                    {
                        int x = i + d[k].first;
                        int y = j + d[k].second;
                        if (board[x][y] == 'O')
                        {
                            us.unionSets(x * n + y, i * n + j);
                        }
                    }
        // '0' to 'X'
        // 'x' is not participated to the unionset
        for (int i = 1; i < m - 1; i++)
            for (int j = 1; j < n - 1; j++)
                if (!us.isConnected(i * n + j ,dummyNodeIndex))
                    board[i][j] = 'X';
    }
};