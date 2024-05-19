#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <format>
#include <string>
#include <cmath>
#include <cassert>
// #include <assert>

using namespace std;

std::ostream &operator<<(std::ostream &os, const std::pair<size_t, size_t> &c)
{
    os << format("[{}, {}]", c.first, c.second);
    return os;
}
// 690 / 759 testcases passed
class Solution
{
public:
    // hash functor
    using Island = set<pair<size_t, size_t>>;

    class IslandHash
    {
    public:
        // const is a must
        size_t operator()(const Island &i) const
        {
            // accumulate delta
            // std::copy(std::begin(i), std::end(i),
            //           std::ostream_iterator<pair<size_t, size_t>>(std::cout, " "));

            // for (const auto &[x, y] : i)
            // {
            //     std::cout << format("[{}, {}]\n", x, y);
            // }

            string hashResult;

            // xor
            //  hash<int>{}(p.first) ^ hash<int>{}(p.second); // simple and effective
            for (auto itr = (++i.begin()); itr != i.end(); ++itr)
            {
                const auto b = i.begin();
                auto dx = itr->first - b->first;
                auto dy = itr->second - b->second;
                hashResult += std::to_string(dx);
                hashResult += std::to_string(dy);
                // hashResult ^= dx;
                // hashResult ^= dy;
            }
            // cout << hashResult << endl;
            //  string to hash
            return hash<string>{}(hashResult);
        }
    };

    // connected 4-directionally (horizontal or vertical.)
    int numDistinctIslands(vector<vector<int>> &grid)
    {
        // visited flag, or flip 1->0
        int numRow = grid.size();
        int numCol = grid[0].size();

        queue<pair<size_t, size_t>> q;
        unordered_set<string> islandHashes;

        // unordered_set<Island, IslandHash> islands;

        for (size_t i = 0; i < numRow; ++i)
        {
            for (size_t j = 0; j < numCol; ++j)
            {
                if (grid[i][j] == 0)
                {
                    continue;
                }

                Island island;

                q.push(make_pair(i, j));

                while (!q.empty())
                {
                    const auto &[ii, jj] = q.front();
                    q.pop();
                    // flip or visited approach
                    grid[ii][jj] = 0;
                    island.emplace(make_pair(ii, jj));

                    // 4 direction
                    if (ii > 0 && grid[ii - 1][jj] == 1)
                    {
                        q.push(make_pair(ii - 1, jj));
                    }
                    if (ii < numRow - 1 && grid[ii + 1][jj] == 1)
                    {
                        q.push(make_pair(ii + 1, jj));
                    }
                    if (jj > 0 && grid[ii][jj - 1] == 1)
                    {
                        q.push(make_pair(ii, jj - 1));
                    }
                    if (jj < numCol - 1 && grid[ii][jj + 1] == 1)
                    {
                        q.push(make_pair(ii, jj + 1));
                    }
                }
                const auto islandHash = generateIslandHash(island);
                islandHashes.insert(islandHash);
            }
        }
        return islandHashes.size();
    }

protected:
    std::string generateIslandHash(const Island &i)
    {
        // accumulate delta
        // std::copy(std::begin(i), std::end(i),
        //           std::ostream_iterator<pair<size_t, size_t>>(std::cout, " "));

        // for (const auto &[x, y] : i)
        // {
        //     std::cout << format("[{}, {}]\n", x, y);
        // }

        string hashResult;

        // xor
        //  hash<int>{}(p.first) ^ hash<int>{}(p.second); // simple and effective
        for (auto itr = (++i.begin()); itr != i.end(); ++itr)
        {
            const auto b = i.begin();
            auto dx = itr->first - b->first;
            auto dy = itr->second - b->second;
            hashResult += std::to_string(dx);
            hashResult += std::to_string(dy);
            // hashResult ^= dx;
            // hashResult ^= dy;
        }
        // cout << hashResult << endl;
        //  string to hash
        return hashResult;
    }
};
