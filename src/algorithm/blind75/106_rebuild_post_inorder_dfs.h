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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for (int i = 0; i < inorder.size(); ++i) {
            _inorderValToIndex[inorder[i]] = i;
        }

        return buildDFS(inorder, 0, inorder.size() - 1, postorder, 0, 
        postorder.size() - 1);
    }

    TreeNode* buildDFS(vector<int>& inorder, int inStart, int inEnd,
                       vector<int>& postorder, int postStart, int postEnd) {            
        // recursive end condition
        if (inStart > inEnd) {
            return nullptr;
        }

        // last of postOrder is root
        int rootValue = postorder[postEnd];
        int inOrderRootIndex = _inorderValToIndex[rootValue];
        int rightSize = inEnd - inOrderRootIndex;

        TreeNode* curr = new TreeNode(rootValue);
        curr->left = buildDFS(inorder, inStart, inOrderRootIndex - 1, postorder, postStart, postEnd - 1 - rightSize);

        // postEnd-1 rule out the root
        curr->right = buildDFS(inorder, inOrderRootIndex + 1, inEnd, postorder, postEnd - 1 - rightSize + 1, postEnd-1);

        return curr;
    }

private:
    unordered_map<int, int> _inorderValToIndex;
};