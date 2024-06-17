#include <vector>
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
    }
};

class Solution
{
public
    Node cloneGraph(Node node)
    {
        // DFS 遍历图，顺便构建克隆图
        traverse(node);
        // 从 map 里找到克隆图的对应节点
        return originToClone.get(node);
    }

    // 记录 DFS 遍历过的节点，防止走回头路
    HashSet<Node> visited = new HashSet<>();
    // 记录原节点到克隆节点的映射
    HashMap<Node, Node> originToClone = new HashMap<>();

    // DFS 图遍历框架
    void traverse(Node node)
    {
        if (node == null)
        {
            return;
        }
        if (visited.contains(node))
        {
            return;
        }
        // 前序位置，标记为已访问
        visited.add(node);
        // 前序位置，克隆节点
        if (!originToClone.containsKey(node))
        {
            originToClone.put(node, new Node(node.val));
        }
        Node cloneNode = originToClone.get(node);

        // 递归遍历邻居节点，并构建克隆图
        for (Node neighbor : node.neighbors)
        {
            traverse(neighbor);
            // 递归之后，邻居节点一定存在 originToClone 中
            Node cloneNeighbor = originToClone.get(neighbor);
            cloneNode.neighbors.add(cloneNeighbor);
        }
    }
}