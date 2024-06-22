/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for(int i = 0; i < inorder.size(); ++i) {
            _valToIndexInInOrder[inorder[i]] = i;
        }

        return build(preorder, 0, preorder.size()- 1, inorder, 0, inorder.size() - 1);
    }

    // like st and bit
    // preorder and inorder consist of unique values.
    // This enables value to index look up
    TreeNode* build(vector<int>& preorder, int preStart, int preEnd,
                    vector<int>& inorder, int inStart, int inEnd) {
        // dfs end condition
        if (preStart > preEnd) {
            return nullptr;
        }

        int rootVal = preorder[preStart];
        int index = _valToIndexInInOrder[rootVal];
        // inorder separate left and right based on root value
        int leftSize = index - inStart;

        TreeNode* root = new TreeNode(rootVal);
        root->left =
            build(preorder, preStart + 1, preStart + 1 + (leftSize - 1),
                  inorder, inStart, index - 1);
        root->right =
            build(preorder, preStart + leftSize + 1, preEnd,
                  inorder, index + 1, inEnd);
        return root;
    }

private:
    unordered_map<int, int> _valToIndexInInOrder;
};