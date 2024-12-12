/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

// connected undirected graph.
// must a way to know which node has been visited,

class Solution {
public:
    Node* cloneGraph(Node* node) {
        queue<Node*> bfs;
        if(node)
            bfs.emplace(node);
        unordered_set<Node*> visited;
        unordered_map<Node*, Node*> lookup;
        while (!bfs.empty()) {
            auto currNode = bfs.front();
            bfs.pop();
            visited.insert(currNode);

            auto newNode = new Node(currNode->val);
            lookup.insert(make_pair(currNode, newNode));

            for (const auto& n : currNode->neighbors) {
                if (visited.find(n) != visited.end())
                    continue;
                bfs.emplace(n);
            }
        }
        // now add the relationship
        for (const auto& oldNode : visited) {
            auto newNode = lookup[oldNode];
            for (const auto& oldNeighborNode : oldNode->neighbors) {
                auto newNeighborNode = lookup[oldNeighborNode];
                newNode->neighbors.emplace_back(newNeighborNode);
            }
        }
        return lookup[node];
    }
};