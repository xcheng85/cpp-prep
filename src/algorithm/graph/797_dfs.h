// 1. diff vs backtracking
// 2.             path.pop_back(); don't forget

class Solution {
public:
    // vector<vector<int>>& graph: already the adj list

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> res;
        vector<int> p;
        dfs(graph, 0, p, res);
        return res;
    }

    // path:
    // here the destination is reaching the node 3
    // care about the node, not the path. Hence should use dfs.
    void dfs(vector<vector<int>>& graph, int nodeIdx, vector<int>& path,
             vector<vector<int>>& res) {
        path.emplace_back(nodeIdx);
        if (nodeIdx == graph.size() - 1) {
            res.emplace_back(path);
            // revoke 
            path.pop_back();
            return;
        }
        // make decisition outside of for-loop

        for (const auto& i : graph[nodeIdx]) {
            dfs(graph, i, path, res);
        }
        // revoke outside for loop
        path.pop_back();
    }
};