#include <vector>
#include <iostream>
#include <iterator>

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

vector<int> preorder(TreeNode *root)
{
    vector<int> res;
    backtracking(root, res);
    return res;
}

void backtracking(TreeNode* curr, vector<int>& res) {
    if(!curr) {
        return;
    }
    res.emplace_back(curr->val);
    backtracking(curr->left, res);
    backtracking(curr->right, res);
}

int main()
{

}