#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <utility>
#include <queue>
#include <map>

using namespace std;

// dfs + visited + path backtracking
class Solution
{
public:
    bool validTree(int n, vector<vector<int>> &edges)
    {
        // a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.”

        // step1: build the adj list
        // undirected
        vector<vector<int>> adj(n);
        for (const auto &e : edges)
        {
            adj[e[0]].emplace_back(e[1]);
            adj[e[1]].emplace_back(e[0]);
        }

        // step2: select any node, it if is a tree, all node should be visited only once
        vector<bool> visited(n, false);
        // path due to undirected graph
        unordered_set<int> path;
        bool cycle = false;
        path.insert(0);
        dfs(0, adj, visited, cycle, path);

        if (cycle)
        {
            return false;
        }

        for (int i = 0; i < n; ++i)
        {
            if (!visited[i])
            {
                return false;
            }
        }
        return true;
    }

    void dfs(int currNodeIdx, const vector<vector<int>> &adj, vector<bool> &visited,
             bool &cycle,
             unordered_set<int> &path)
    {
        // cout << "-->" << currNodeIdx << endl;
        if (visited[currNodeIdx])
        {
            // cycle
            cycle = true;
            return;
        }

        visited[currNodeIdx] = true;
        for (const auto &n : adj[currNodeIdx])
        {
            if (path.count(n) == 0)
            {
                // cout << "add: " << n << endl;
                path.insert(n);
                dfs(n, adj, visited, cycle, path);
                path.erase(n);
            }
        }
        // cout << "<--" << currNodeIdx << endl;
    }
};

class UnionSet
{
public:
    UnionSet(int n)
        : _parents(n, -1),
          _setSize(n, 1),
          _setCount(n)
    {
        for (int i = 0; i < n; ++i)
        {
            _parents[i] = i;
        }
    }

    int parents(int nodeIndex)
    {
        int curr = nodeIndex;
        while(curr != _parents[curr]) {
            curr = _parents[curr];
        }
        return curr;
    }

    bool merge(int n1, int n2) {
        int p1 = parents(n1);
        int p2 = parents(n2);

        if(p1 == p2) {
            return false;
        }

        if(_setSize[p1] < _setSize[p2]) {
            _parents[p1] = p2;
            _setSize[p2] += _setSize[p1];
        } else {
            _parents[p2] = p1;
            _setSize[p1] += _setSize[p2];   
        }
        --_setCount;
        return true;
    }

    inline auto setCount() const{
        return _setCount;
    }
private:
    vector<int> _parents;
    vector<int> _setSize;
    int _setCount;
};

class Solution
{
public:
    bool validTree(int n, vector<vector<int>> &edges)
    {
        UnionSet us(n); 
        for(const auto& e: edges) {
            if(!us.merge(e[0], e[1])){
                // duplicates
                return false;
            }
        }
        if(us.setCount() == 1) {
            return true;
        }
        return false;
    }
};