class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // 1. adj list
        // 2. traversal and record post order
        // 3. reverse

        // 0 <= ai, bi < numCourses
        vector<vector<int>> adjLists(numCourses);
        for (const auto& p : prerequisites) {
            assert(p.size() == 2);
            const auto src = p[1], dst = p[0];
            adjLists[src].emplace_back(dst);
        }
        // multiple sources
        unordered_map<int, bool> visited;
        // vector<bool> visited; // not suited if the node id is random, string,
        // etc.
        unordered_map<int, bool> onPath;
        vector<int> postOrderTraversal;
        bool cycle = false;
        for (size_t i = 0; i < numCourses; ++i) {
            traverse(adjLists, i, visited, onPath, postOrderTraversal, cycle);
        }
        if(cycle) {
            return {};
        }
        reverse(postOrderTraversal.begin(), postOrderTraversal.end());
        return postOrderTraversal;
    }
    // 1. visited for cycle
    // 2. path for topology sorting
    void traverse(const vector<vector<int>>& adj, int curr,
                  unordered_map<int, bool>& visited, unordered_map<int, bool>& onPath,
                  vector<int>& postOrderTraversal, bool& cycle) {
        // other pre-traverse path alrealdy visited cut, branch
        // cyle detection first, then visited
        if (onPath.count(curr) > 0 && onPath[curr]) {
            cycle = true;
            return;
        }

        if (visited.count(curr) > 0) {
            return;
        }

        onPath[curr] = true;
        visited[curr] = true;
        // children first
        for(const auto& n : adj.at(curr)) {
            traverse(adj, n, visited, onPath, postOrderTraversal, cycle);
        }
        onPath[curr] = false;
        postOrderTraversal.emplace_back(curr);
    }
};