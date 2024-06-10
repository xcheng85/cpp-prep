class Solution {
public:
    int treeDiameter(vector<vector<int>>& edges) {
        // each node save two maxim value
        int n = edges.size() + 1;
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1]);
            adj[e[1]].emplace_back(e[0]);
        }

        vector<bool> visited(edges.size() + 1, false);
        int maxDiameter = 0;
        maxDistanceToLeafDfs(adj, 0, visited, maxDiameter);
        return maxDiameter;
    }

    // only care about node, not traversed path, not backtracking
    // dfs, post-order-traversal
    // n is runtime, can not use bitset
    int maxDistanceToLeafDfs(const vector<vector<int>>& adj, int curr,
             vector<bool>& visited, int& maxDiameter) {
        // record two max distance for this current node
        int maxDist = 0, secondMaxDist = 0;
        // dfs out of the for-loop
        visited[curr] = true;
        // max and 2nd max distance
        for (const auto& n : adj[curr]) {
            if (!visited[n]) {
                const auto distance = maxDistanceToLeafDfs(adj, n, visited, maxDiameter) + 1;
                if (distance > secondMaxDist) {
                    secondMaxDist = distance;
                }
                if (distance > maxDist) {
                    secondMaxDist = maxDist;
                    maxDist = distance;
                }
            }
        }
        // update maxDisameter if possible
        maxDiameter = max({maxDiameter, maxDist + secondMaxDist});
        return maxDist;
    }
};