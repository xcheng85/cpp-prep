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

// backtracking 

class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        int res = 0;
        backtracking(root, 0, res);
        return res;
    }

    void backtracking(TreeNode *curr, int depth, int &res)
    {
        if (!curr)
        {
            res = max(depth, res);
            return;
        }

        // enter decision branch
        backtracking(curr->left, ++depth, res);
        // exit
        --depth;

        // enter decision branch
        backtracking(curr->right, ++depth, res);
        // exit
        --depth;
    }
};

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
// subproblem, no duplication in the tree case
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) {
            return 0;
        }

        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};