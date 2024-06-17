#include <vector>
#include <queue>

using namespace std;

class Solution
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        // 1. adj
        // 2. indegree
        // 3. queue

        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses);

        for (const auto &p : prerequisites)
        {
            auto src = p[1], dst = p[0];
            adj[src].emplace_back(dst);
            ++indegree[dst];
        }
        queue<int> zeroInDegrees;
        for (int i = 0; i < numCourses; ++i)
        {
            if (indegree[i] == 0)
            {
                zeroInDegrees.emplace(i);
            }
        }
        vector<int> topoSorted;
        while (!zeroInDegrees.empty())
        {
            const auto curr = zeroInDegrees.front();
            zeroInDegrees.pop();
            topoSorted.emplace_back(curr);

            for (const auto &n : adj[curr])
            {
                --indegree[n];
                if (indegree[n] == 0)
                {
                    zeroInDegrees.emplace(n);
                }
            }
        }

        return topoSorted.size() == numCourses ? topoSorted : vector<int>{};
    }
};