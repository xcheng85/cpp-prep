
// bfs + multisource + visited
class Solution
{
public:
    int countCompleteComponents(int n, vector<vector<int>> &edges)
    {
        // adj
        vector<vector<int>> adj(n);
        // indegree/outdegree
        vector<int> indegree(n);
        vector<int> outdegree(n);

        for (const auto &e : edges)
        {
            adj[e[0]].emplace_back(e[1]);
            adj[e[1]].emplace_back(e[0]);
            ++indegree[e[0]];
            ++indegree[e[1]];
            ++outdegree[e[0]];
            ++outdegree[e[1]];
        }
        vector<bool> visited(n, false);
        int numComponents = 0;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                vector<int> components;
                queue<int> q;
                q.push(i);
                while (!q.empty())
                {
                    const auto curr = q.front();
                    q.pop();
                    if (!visited[curr])
                    {
                        visited[curr] = true;
                        components.emplace_back(curr);

                        for (const auto &n : adj[curr])
                        {
                            if (!visited[n])
                            {
                                q.push(n);
                            }
                        }
                    }
                }
                copy(components.begin(), components.end(),
                     ostream_iterator<int>(cout, ","));
                cout << endl;

                // compare indgree and outdegree
                if (components.size() == 1)
                {
                    ++numComponents;
                }
                else
                {
                    bool goodComponent = true;
                    for (int i = 0; i < components.size(); ++i)
                    {
                        int nodeId = components[i];
                        if (indegree[nodeId] != components.size() - 1 ||
                            outdegree[nodeId] != components.size() - 1)
                        {
                            goodComponent = false;
                        }
                    }
                    if (goodComponent)
                        ++numComponents;
                }
            }
        }
        return numComponents;
    }
};