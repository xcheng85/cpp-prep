#include <vector>
#include <unordered_set>
using namespace std;

// definition of valid tree
// 1. single source (this is incorrect understanding, we don't know which one is root node)
// Input: n = 5, edges = [[0,1],[0,2],[0,3],[1,4]] from a bottom-up view, you will see three source node (4,2,3)

// 2. non cycle

// a tree is an undirected graph in which any two vertices are connected by exactly one path.
// In other words, any connected graph without simple cycles is a tree.”

// how to detect the cycle
// backtracking carry the path in the dfs ?

// Input: n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]

// 0 - 1- 2-3  - 2 1, 1 is already in the path


// tree is connected. 
// disconnected case: // [[0,1],[2,3]]

using namespace std;

class Solution
{
public:
    bool validTree(int n, vector<vector<int>> &edges)
    {
        // step1: build adj list (undirected)
        vector<vector<int>> adjList(n, vector<int>());
        for(const auto& edge : edges) {
            adjList[edge[0]].emplace_back(edge[1]);
            adjList[edge[1]].emplace_back(edge[0]);
        }

        bool valid = true;
        unordered_set<int> path;
        unordered_set<int> allVisitedNodes;
        backtracking(adjList, 0, -1, path, valid, allVisitedNodes);
        if(allVisitedNodes.size() != n) {
            return false;
        }
        return valid;
    }
    // [[0,1],[2,3]]


    void backtracking(const vector<vector<int>> &adjList, int nodeIndex, int fromNodeIndex,
                      unordered_set<int> &path,
                      bool &valid,
                      unordered_set<int> &allVisitedNodes)
    {
        allVisitedNodes.insert(nodeIndex);
        for (const auto &neighborNodeIndex : adjList[nodeIndex])
        {
            if (neighborNodeIndex == fromNodeIndex)
                continue;
            if (path.count(neighborNodeIndex) > 0)
            {
                valid = false;
                return;
            }
            if (!valid)
            {
                return;
            }
            path.insert(neighborNodeIndex);
            backtracking(adjList, neighborNodeIndex, nodeIndex, path, valid, allVisitedNodes);
            path.erase(neighborNodeIndex);
        }
    }
};