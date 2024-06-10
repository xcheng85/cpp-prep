class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // topology sorting
        vector<unordered_set<int>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].insert(e[1]);
            adj[e[1]].insert(e[0]);
        }

        vector<int> oneConnectionBfs;
        for (int i = 0; i < n; ++i) {
            if (adj[i].size() <= 1) {
                oneConnectionBfs.emplace_back(i);
            }
        }
        //
        int remainingNodes = n;
        while (remainingNodes > 2) {
            // take care current level
            vector<int> next;
            for (const auto& one : oneConnectionBfs) {
                for (const auto& n : adj[one]) {
                    adj[n].erase(one);
                    if (adj[n].size() == 1) {
                        next.emplace_back(n);
                    }
                }
            }
            remainingNodes -= oneConnectionBfs.size();
            // swap and clear idiom
            std::swap(oneConnectionBfs, next);
        }

        return oneConnectionBfs;
    }
};