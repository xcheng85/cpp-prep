/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
        // two linked list
        // cache the visted nodes
        set<int> pathP;
        while(p != nullptr) {
            pathP.insert(p->val);
            p = p->parent;
        }

        while(q != nullptr) {
            auto ret = pathP.find(q->val);
            if(ret != pathP.end())
                return q;
            q = q->parent;
        }

        return nullptr;
    }
};