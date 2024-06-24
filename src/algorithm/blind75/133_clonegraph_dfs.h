#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <assert.h>

using namespace std;

// Definition for a Node.
class Node
{
public:
    int val;
    vector<Node *> neighbors;
    Node()
    {
        val = 0;
        neighbors = vector<Node *>();
    }
    Node(int _val)
    {
        val = _val;
        neighbors = vector<Node *>();
    }
    Node(int _val, vector<Node *> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};

// adj list of the graph is given in the ds of node.

class Solution
{
public:
    Node *cloneGraph(Node *node)
    {
        // DFS 遍历图，顺便构建克隆图
        preOrderTraverse(node);
        // 从 map 里找到克隆图的对应节点
        return _originToClone[node];
    }

private:
    // connected undirected graph.

    // 记录 DFS 遍历过的节点，防止走回头路
    unordered_set<Node *> _visited;

    // 记录原节点到克隆节点的映射
    unordered_map<Node *, Node *> _originToClone;

    // preOrderTraverse 图遍历框架
    void preOrderTraverse(Node *curr)
    {
        if (curr == nullptr)
        {
            return;
        }
        if (_visited.contains(curr))
        {
            return;
        }
        // 前序位置，标记为已访问
        _visited.insert(curr);

        assert(!_originToClone.contains(curr));
        auto tmp = new Node(curr->val);
        // 前序位置，克隆节点
        _originToClone[curr] = tmp;

        // 递归遍历邻居节点，并构建克隆图
        for (const auto &n : curr->neighbors)
        {
            preOrderTraverse(n);
            // 递归之后，邻居节点一定存在 originToClone 中
            auto clone_n = _originToClone[n];
            tmp->neighbors.push_back(clone_n);
        }
    }
};