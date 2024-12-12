// compare with 261_valid tree.

// dfs will only extend to all the components connected.

#include <vector>
#include <unordered_set>
using namespace std;

// dfs based solution

class Solution
{
public:
    int countComponents(int n, vector<vector<int>> &edges)
    {
         // step1: build adj list (undirected)
        vector<vector<int>> adjList(n, vector<int>());
        for(const auto& edge : edges) {
            adjList[edge[0]].emplace_back(edge[1]);
            adjList[edge[1]].emplace_back(edge[0]);
        }

        unordered_set<int> path;
        unordered_set<int> allVisitedNodes;
        // try each one
        int numComponents = 0;
        for(int nodeIndex = 0; nodeIndex < n; nodeIndex++) {
            if(allVisitedNodes.count(nodeIndex)) 
                continue;
            //cout << nodeIndex << endl;
            ++numComponents;
            backtracking(adjList, nodeIndex, -1, path, allVisitedNodes);
        }
        return numComponents;
    }

    void backtracking(const vector<vector<int>> &adjList, int nodeIndex, int fromNodeIndex,
                      unordered_set<int> &path,
                      unordered_set<int> &allVisitedNodes)
    {
        //cout << "backtracking: " << nodeIndex << endl;
        if(allVisitedNodes.count(nodeIndex))
            return;
        allVisitedNodes.insert(nodeIndex);
        for (const auto &neighborNodeIndex : adjList[nodeIndex])
        {
            if (neighborNodeIndex == fromNodeIndex)
                continue;
            // loop, but here I don't care, just ignore it
            if (path.count(neighborNodeIndex) > 0)
            {
                //valid = false;
                //return;
                continue;
            }
            path.insert(neighborNodeIndex);
            backtracking(adjList, neighborNodeIndex, nodeIndex, path , allVisitedNodes);
            path.erase(neighborNodeIndex);
        }
    }
};