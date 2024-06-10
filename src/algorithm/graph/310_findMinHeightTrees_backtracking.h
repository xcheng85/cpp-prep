class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // any connected graph without simple cycles is a tree.
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1]);
            adj[e[1]].emplace_back(e[0]);
        }

        vector<int> rootNode;
        vector<int> path;
        int minTreeHeight = std::numeric_limits<int>::max();

        for (int i = 0; i < n; ++i) {
            vector<bool> visited(n, false);
            int numVisited = 0;
            int maxLength = 0;
            findHeightDfs(adj, n, i, path, maxLength, visited, numVisited);
            if (maxLength == minTreeHeight) {
                rootNode.emplace_back(i);
            } else if (maxLength < minTreeHeight) {
                minTreeHeight = maxLength;
                rootNode = vector<int>({i});
            }
        }
        return rootNode;
    }

protected:
    // term
    void findHeightDfs(const vector<vector<int>>& adj, const int& numNodes,
                       int curr, vector<int>& path, int& maxLength,
                       vector<bool>& visited, int& numVisited) {
        if (visited.at(curr)) {
            return;
        }
        visited[curr] = true;
        ++numVisited;
        if (path.size() > maxLength) {
            maxLength = path.size();
        }

        for (const auto& n : adj[curr]) {
            path.emplace_back(curr);
            findHeightDfs(adj, numNodes, n, path, maxLength, visited,
                          numVisited);
            path.pop_back();
        }
    }
};