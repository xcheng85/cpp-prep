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
   // bfs advance at the same step
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;

        // only store all the nodes at the same level
        queue<TreeNode*> bfs;
        if(root)
            bfs.emplace(root);

        while(!bfs.empty()) {
            auto levelSize = bfs.size();

            // deal with all the nodes at the same level
            vector<int> nodes;
            nodes.reserve(levelSize); // avoid dynamic memory allocation

            for(size_t i = 0; i < levelSize; ++i) {
                auto curr = bfs.front();
                nodes.push_back(bfs.front()->val);
                bfs.pop();

                if(curr->left) {
                    bfs.emplace(curr->left);
                }
                if(curr->right) {
                    bfs.emplace(curr->right);
                }
            }
            // avoid copy, rvalue
            res.push_back(std::move(nodes));
        }
        return res;
    }
};