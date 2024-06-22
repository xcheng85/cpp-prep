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
    // 主函数
    int maxDepth(TreeNode* root) {
        // 记录最大深度
        int maxDepth = 0;
        // 记录遍历到的节点的深度
        int depthInPath = 0;

        traverse(root, depthInPath, maxDepth);
        return maxDepth;
    }

    // 二叉树遍历框架
    void traverse(TreeNode* curr, int& depthInPath, int& maxDepth) {
        if (curr == nullptr) {
            return;
        }
        // 前序位置
        depthInPath++;
        if (curr->left == NULL && curr->right == NULL) {
            // 到达叶子节点，更新最大深度
            maxDepth = max(maxDepth, depthInPath);
        }
        traverse(curr->left, depthInPath, maxDepth);
        traverse(curr->right, depthInPath, maxDepth);
        // 后序位置
        depthInPath--;
    }
};