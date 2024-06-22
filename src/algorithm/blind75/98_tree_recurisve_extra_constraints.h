/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
    bool isValidBST(TreeNode *root)
    {
        // 限定以root为根的子树节点必须满足max.val > root.val > min.val
        return checkValidBST(root, nullptr, nullptr);
    }

    // 限定root节点符合min和max的限制
    bool checkValidBST(TreeNode *root, TreeNode *minNode, TreeNode *maxNode)
    {
        // base case
        if (root == nullptr)
            return true;
        // 若root.val不符合max和min的限制，说明不是合法BST
        if (minNode != nullptr && root->val <= minNode->val)
            return false;
        if (maxNode != nullptr && root->val >= maxNode->val)
            return false;
        // 限定左子树的最大值是root.val，右子树的最小值是root.val
        return checkValidBST(root->left, minNode, root) && checkValidBST(root->right, root, maxNode);
    }
};