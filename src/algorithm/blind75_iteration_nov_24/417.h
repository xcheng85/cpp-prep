// 2d grid problem: undirected graph
// two type of sources:
// source 1: upper row and left column pacific
// source 2: bottom row and rightmost column : atlantic

// 4 dirs:

// all the sources can spread out, like dfs, how to record visited or not ?
//

#include <vector>
#include <array>
using namespace std;

class Solution
{
public:
    using dir = std::pair<int, int>;
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        int m = heights.size();
        int n = heights[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<vector<int>> score(m, vector<int>(n, 0));

        for (int c = 0; c < n; c++)
        {
            dfs(0, c, 1, heights, visited, score);
        }
        for (int r = 0; r < m; r++)
        {
            dfs(r, 0, 1, heights, visited, score);
        }
        // buggy: visited.resize(m, vector<bool>(n, false));
        vector<vector<bool>> visited2(m, vector<bool>(n, false));
        swap(visited, visited2);

        visited.resize(m, vector<bool>(n, false));
        for (int c = 0; c < n; c++)
        {
            dfs(m - 1, c, 2, heights, visited, score);
        }
        for (int r = 0; r < m; r++)
        {
            dfs(r, n - 1, 2, heights, visited, score);
        }

        vector<vector<int>> res;
        for (int r = 0; r < m; r++)
        {
            for (int c = 0; c < n; c++)
            {
                // two source propagated
                if(score[r][c] == 3) {
                    res.emplace_back(vector<int>{r, c});
                }
            }
        }
        return res;
    }
    // source1 = 1, source2 = 2,
    void dfs(int r, int c,
             const int sourceId,
             const vector<vector<int>> &heights,
             vector<vector<bool>> &visited,
             vector<vector<int>> &score)
    {
        
        // visited
        if (visited[r][c])
            return;

        // 4 directions, _dir
        visited[r][c] = true;
        const auto currHeight = heights[r][c];
        score[r][c] += sourceId;
        //cout << "r: " << r << ", c: " << c << ", score: " << sourceId << endl;
        for (const auto &[dx, dy] : _dirs)
        {
            int newr = r + dx, newc = c + dy;
            // early branch trim
            // out of boundary
            if (newr >= heights.size() || newc >= heights[0].size())
            {
                continue;
            }
            // can flow to children
            if (currHeight <= heights[newr][newc])
            {
                dfs(newr, newc, sourceId, heights, visited, score);
            }
        }
    }

private:
    const array<dir, 4> _dirs{
        make_pair(0, 1),
        make_pair(0, -1),
        make_pair(1, 0),
        make_pair(-1, 0)};
};