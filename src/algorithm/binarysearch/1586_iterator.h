#include <vector>
#include <iostream>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BSTIterator
{
public:
    // You may assume that next() and prev() calls will always be valid.
    BSTIterator(TreeNode *root)
    {
        inorder(root);
    }

    bool hasNext()
    {
        return _currIdx < ((int)_arr.size() - 1);
    }

    int next()
    {
        return _arr[++_currIdx];
    }

    bool hasPrev()
    {
        return _currIdx > 0;
    }

    int prev()
    {
        // guard against overflow
        return _arr[max(--_currIdx, 0)];
    }

private:
    // can only be called once
    void inorder(TreeNode *curr)
    {
        if (curr == nullptr)
            return;
        inorder(curr->left);
        _arr.emplace_back(curr->val);
        inorder(curr->right);
    }
    vector<int> _arr;
    int _currIdx{-1};
};
