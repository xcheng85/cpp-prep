/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

        // // tricky part is this to simply
        // if (p->val > q->val) {
        //     // 保证 p->val <= q->val，便于后续情况讨论
        //     return lowestCommonAncestor(root, q, p);
        // }

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL)
            return NULL;
        // tricky part is this to simply
        if (p->val > q->val) {
            // 保证 p->val <= q->val，便于后续情况讨论
            return lowestCommonAncestor(root, q, p);
        }
        if (root->val >= p->val && root->val <= q->val) {
            // p <= root <= q
            // 即 p 和 q 分别在 root 的左右子树，那么 root 就是 LCA
            return root;
        }
        if (root->val > q->val) {
            // p 和 q 都在 root 的左子树，那么 LCA 在左子树
            return lowestCommonAncestor(root->left, p, q);
        } else {
            // p 和 q 都在 root 的右子树，那么 LCA 在右子树
            return lowestCommonAncestor(root->right, p, q);
        }
    }
};