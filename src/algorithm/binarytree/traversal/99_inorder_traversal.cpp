#include <stack>
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

class Solution
{
public:
    void recoverTree(TreeNode *root)
    {
        stack<TreeNode *> stack;

        TreeNode *x = nullptr, *y = nullptr, *pred = nullptr;

        // every node will go through two traversal path
        // enter and exit
        // push: enter
        // top: exit and then you can pop
        auto curr = root;
        while (!stack.empty() || curr != nullptr)
        {
            // enter, left node
            while (curr != nullptr)
            {
                // push
                stack.push(curr);
                curr = curr->left;
            }
            // curr enter and exit
            curr = stack.top();
            stack.pop();
            cout << curr << endl;

            if (pred != nullptr && curr->val < pred->val)
            {
                cout << curr->val << " < " << pred->val << endl;
                y = root;
                if (x == nullptr)
                {
                    cout << pred->val << " become pred " << endl;
                    x = pred;
                }
                else
                    break;
            }
            pred = curr;
            curr = curr->right;
        }
        // swap(x->val, y->val);
    }
};

class Solution2
{
public:
    TreeNode *x = nullptr;    // first node
    TreeNode *y = nullptr;    // second node
    TreeNode *pred = nullptr; // predecessor node
    void findTwoSwapped(TreeNode *root)
    {
        if (root == nullptr)
            return;
        findTwoSwapped(root->left);
        if (pred != nullptr && root->val < pred->val)
        {
            y = root;
            if (x == nullptr)
                x = pred;
            else
                return;
        }
        pred = root;
        findTwoSwapped(root->right);
    }
    void recoverTree(TreeNode *root)
    {
        findTwoSwapped(root);
        swap(x->val, y->val); // C++ standard swap function
    }
};