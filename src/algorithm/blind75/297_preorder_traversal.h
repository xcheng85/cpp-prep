/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec
{
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        if (!root)
            return string(NULL_STR) + _delimiter;

        /* 前序遍历位置 */
        string res = to_string(root->val) + _delimiter;
        res += serialize(root->left);
        res += serialize(root->right);
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        string tmp;
        stringstream ss(data);
        vector<string> nodes;

        while (getline(ss, tmp, _delimiter))
        {
            nodes.emplace_back(tmp);
        }
        return preOrderTraversal(nodes);
    }

private:
    TreeNode *preOrderTraversal(const vector<string> &nodes)
    {
        if (_nextPos >= nodes.size())
        {
            return nullptr;
        }

        auto nodeVal = nodes[_nextPos++];
        if (nodeVal == NULL_STR)
        {
            return nullptr;
        }
        TreeNode *root = new TreeNode(stoi(nodeVal));
        root->left = preOrderTraversal(nodes);
        root->right = preOrderTraversal(nodes);

        return root;
    }

    const char _delimiter{','};
    const string NULL_STR{"#"};
    int _nextPos{0};
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));