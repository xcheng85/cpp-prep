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
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int maxPathSum = numeric_limits<int>::min();
        traverse(root, maxPathSum);
        return maxPathSum;
    }
    // post-order
    int traverse(TreeNode* curr, int& maxPathSum) {
        if(!curr) {
            return 0;
        }

       // cout << "visit: " << curr->val << endl;

        int leftMax = traverse(curr->left, maxPathSum);
        int rightMax = traverse(curr->right, maxPathSum);

        // cout << "leftMax: " << leftMax << endl;
        // cout << "rightMax: " << rightMax << endl; 

        maxPathSum = max({maxPathSum, leftMax + rightMax + curr->val, 
        leftMax + curr->val, rightMax + curr->val, curr->val});

        return max({leftMax + curr->val, rightMax + curr->val, curr->val});
    }
};