class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // build adj list from the pre-req
        vector<vector<int>> adjList(numCourses);
        for (auto& edge : prerequisites) {
            int from = edge[1], to = edge[0];
            adjList[from].emplace_back(to);
        }
        // visited 记录蛇经过过的格子，而 onPath 仅仅记录蛇身。在图的遍历过程中，onPath 用于判断是否成环
        vector<bool> visited(numCourses, false);
        vector<bool> path(numCourses, false);
        bool hasCycle = false;

        // all the nodes could be the source
        for(int i = 0; i < numCourses; ++i){
            dfs(adjList, i, visited, path, hasCycle);
            if(hasCycle) {
                return false;
            }
        }

        return !hasCycle;
    }

    void dfs(vector<vector<int>>& adjList, int v, vector<bool>& visited, 
    vector<bool>& path, bool& hasCycle) {
         if (path[v]) {
            // 出现环
            hasCycle = true;
            return;
        }

        if (visited[v]) {
            return;
        }
        
        visited[v] = true;
        path[v] = true;
        for (const auto& n : adjList[v]) {
            dfs(adjList, n, visited, path, hasCycle);
        }
        // dfs out of for loop
        path[v] = false;
    }
};