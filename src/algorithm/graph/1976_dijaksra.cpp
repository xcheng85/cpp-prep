#include <vector>
#include <utility>
#include <numeric>
#include <set>
#include <iostream>

using namespace std;


class Solution
{
public:
    using DistanceType = long long;
    static constexpr int M=1e9+7;
    int countPaths(int n, vector<vector<int>> &roads)
    {
        // weighted list
        // <node,w>
        vector<vector<pair<int, int>>> adjW(n);
        for (const auto &r : roads)
        {
            // undirected graph
            adjW[r[0]].emplace_back(make_pair(r[1], r[2]));
            adjW[r[1]].emplace_back(make_pair(r[0], r[2]));
        }
        // two outputs
        vector<DistanceType> shortestDistArray(
            n, std::numeric_limits<DistanceType>::max());
        vector<int> pathCount(n);

        dijkstra(adjW, n, 0, shortestDistArray, pathCount);
        return pathCount[n - 1];
    }
    // dist array from src to all the nodes
    // path count array, number of minimum path combination
    void dijkstra(const vector<vector<pair<int, int>>> &adjW, int n, int src,
                  vector<DistanceType> &shortestDistArray,
                  vector<int> &pathCount)
    {
        // 1. distarray (sum of int)
        // shortest
        shortestDistArray[src] = 0; // src to itself is 0

        // 2. every node count the path (extra to the standard Dijkstra
        // algorithm)
        pathCount[src] = 1;

        // using set default std::less<int>
        // shortest distance to the node i
        set<pair<DistanceType, int>> candidates;
        candidates.insert(make_pair(0, src));

        while (!candidates.empty())
        {
            // cannot reference here
            const auto [dist, node] = *(candidates.begin());
            // cout << "dist:" << dist << ", node:" << node << endl;
            candidates.erase(candidates.begin());

            // [nodeIndex, weight]
            for (const auto &p : adjW[node])
            {
                const auto n = p.first;
                const auto w = p.second;
                const auto newDistance = dist + w;
                //cout << "visiting node: " << n << " with weight: " << w << " with new distance: " << newDistance << endl; 
                // iterative optimize
                if (newDistance < shortestDistArray[n])
                {
                    // cannot update set, reinsert
                    auto itr = candidates.find(make_pair(shortestDistArray[n], n));
                    // if record found then erase it
                    if (itr != candidates.end())
                    {
                        candidates.erase(itr);
                    }
                    // optimized distance for this node
                    shortestDistArray[n] = newDistance;
                    // pathcount propagated from src to dst of the directed
                    // edge.
                    pathCount[n] = pathCount[node];
                    // cout << "new candidate: " << n << ", distance: " 
                    //   << newDistance << ", pathCount: " << pathCount[n]  << endl;
                    candidates.insert(make_pair(newDistance, n));
                }
                else if (newDistance == shortestDistArray[n])
                {
                    pathCount[n] = (pathCount[n] + pathCount[node]) % M;
                    // cout << "update candidate:  " << n << ", distance: " 
                    //   << newDistance << ", pathCount: " << pathCount[n]  << endl;
                }
            }
        }
        return;
    }
};

int main()
{
    Solution s;

    vector<vector<int>> inputs = {
        {0, 6, 7},
        {0, 1, 2},
        {1, 2, 3},
        {1, 3, 3},
        {6, 3, 3},
        {3, 5, 1},
        {6, 5, 1},
        {2, 5, 1},
        {0, 4, 5},
        {4, 6, 2}};

    cout << s.countPaths(7, inputs) << endl;
}