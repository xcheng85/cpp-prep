
// start: root

// end: node->left == nullptr && right == nullptr

// neighbor, left and right

// advance at the same step to increase depth

#include <queue>

using namespace std;

class Solution
{
public:
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    int minDepth(TreeNode *root)
    {
        if (!root)
        {
            return 0;
        }

        queue<TreeNode *> bfs;
        bfs.emplace(root);
        int depth{1};

        while (!bfs.empty())
        {
            auto s = bfs.size();
            for (size_t i = 0; i < s; ++i)
            {
                auto node = bfs.front();
                bfs.pop();
                if (!node->left && !node->right)
                {
                    return depth;
                }
                // tree has no cyclic, no visited cache needed
                if (node->left)
                {
                    bfs.emplace(node->left);
                }
                if (node->right)
                {
                    bfs.emplace(node->right);
                }
            }
            ++depth;
        }
        // flat case, like complte binary tree
        return depth;
    }
};