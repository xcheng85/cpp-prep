#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <utility>
#include <queue>
#include <map>

using namespace std;

class Solution
{
public:
    string alienOrder(vector<string> &words)
    {
        // 1. create vertex and edges
        unordered_set<int> nodes;
        for (const auto &w : words)
        {
            for (const auto &c : w)
            {
                nodes.insert(c - 'a');
            }
        }

        // directed
        vector<pair<int, int>> edges;
        for (int j = 1; j < words.size(); ++j)
        {
            string w1 = words[j - 1];
            string w2 = words[j];

            int l1 = w1.length();
            int l2 = w2.length();
            // abc-->ab
            // ["wrt","wrtkj"]
            bool findEdge = false;
            for (int k = 0; k < min(l1, l2); ++k)
            {
                if (w1[k] == w2[k])
                {
                    continue;
                }
                else
                {
                    //cout << w1[k] << " ---> " << w2[k] << endl;
                    edges.push_back(make_pair(w1[k] - 'a', w2[k] - 'a'));
                    findEdge = true;
                    break;
                }
            }
            if(!findEdge && l1 != l2) {
                return "".
            }
        }

        // build the adj list
        map<int, vector<int>> adj;
        // nodeIdx, indegree
        map<int, int> indegree;
        // initialize to be indegree for all the nodes
        for (const auto &n : nodes)
        {
            indegree[n] = 0;
        }

        for (const auto &[v1, v2] : edges)
        {
            adj[v1].push_back(v2);
            ++indegree[v2];
        }

        // bfs topology sort
        queue<int> zeroInDegrees;
        for (const auto &[nodeIdx, d] : indegree)
        {
            if (d == 0)
            {
                zeroInDegrees.emplace(nodeIdx);
            }
        }

        string toposorted;
        while (!zeroInDegrees.empty())
        {
            const auto curr = zeroInDegrees.front();
            zeroInDegrees.pop();
            toposorted.push_back(curr + 'a');
            for (const auto &n : adj[curr])
            {
                --indegree[n];
                if (indegree[n] == 0)
                {
                    zeroInDegrees.emplace(n);
                }
            }
        }
        if (toposorted.size() != nodes.size())
        {
            return "";
        }
        else
        {
            return toposorted;
        }
    }
};