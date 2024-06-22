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
    TreeNode* constructFromPrePost(vector<int>& preorder,
                                   vector<int>& postorder) {
        for (int i = 0; i < postorder.size(); ++i) {
            _postOrderValToIndex[postorder[i]] = i;
        }
        return build(preorder, 0, preorder.size() - 1, postorder, 0, postorder.size() - 1);
    }

    TreeNode* build(vector<int>& preorder, int preStart, int preEnd,
                    vector<int>& postorder, int postStart, int postEnd) {
        // cout << "prestart: " << preStart << "," << preEnd << endl;
        
        if (preStart > preEnd) {
            return nullptr;
        }
        // looking for the 2nd node, this check is extra
        if (preStart == preEnd) {
            return new TreeNode(preorder[preStart]);
        }

        int leftRootNode = preorder[preStart + 1];
        int postOrderIndex = _postOrderValToIndex[leftRootNode];
        // - postStart is key
        int leftSize = postOrderIndex - postStart + 1;

        TreeNode* curr = new TreeNode(preorder[preStart]);
        curr->left = build(preorder, preStart + 1, preStart + leftSize,
                           postorder, postStart, postStart + leftSize - 1);

        curr->right = build(preorder, preStart + leftSize + 1, preEnd,
                            postorder, postStart + leftSize, postEnd - 1);

        return curr;
    }

private:
    unordered_map<int, int> _postOrderValToIndex;
};