#include <vector>
#include <utility>

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
        vector<int> inorderArray;
        inorder(root, inorderArray);

        const auto& [idx1, idx2] = FindSwapIndexPair(inorderArray);

        recover(root, 2, inorderArray[idx1], inorderArray[idx2]);
    }

    // vector<int> SortAlmostSortedArray(vector<int> &array)
    // {
    //     int n = array.size();
    //     for (int i = n - 1; i > 0; i--)
    //     {
    //         if (array[i] < array[i - 1])
    //         {
    //             // array[i]: one candidate to swap

    //             // to find the other candidate must larger than

    //             // 40, 30
    //             // find [0, i-1]

    //             // find the leftmost in-order position,
    //             // 20, 60 j will stop at 20, and we need j+1
    //             int j = i - 1;
    //             while (j >= 0 && array[i] < array[j])
    //                 j--;
    //             //
    //             j++;
    //             swap(j, i);
    //             break;
    //         }
    //     }
    // }

    void inorder(TreeNode *root, vector<int> &nums)
    {
        if (root == nullptr)
            return;
        inorder(root->left, nums);
        nums.emplace_back(root->val);
        inorder(root->right, nums);
    }

    std::pair<int, int> FindSwapIndexPair(const vector<int> &almostSortedArray)
    {
        int n = almostSortedArray.size();
        for (int i = n - 1; i > 0; i--)
        {
            if (almostSortedArray[i] < almostSortedArray[i - 1])
            {
                // array[i]: one candidate to swap

                // to find the other candidate must larger than

                // 40, 30
                // find [0, i-1]

                // find the leftmost in-order position,
                // 20, 60 j will stop at 20, and we need j+1
                int j = i - 1;
                while (j >= 0 && almostSortedArray[i] < almostSortedArray[j])
                    j--;
                //
                j++;
                return make_pair(i, j);
            }
        }
    }

    // preorder
    // swap two nodes, iterator until two nodes are visited
    void recover(TreeNode *curr, int count, int x, int y)
    {
        if (curr != nullptr)
        {
            if (curr->val == x || curr->val == y)
            {
                curr->val = curr->val == x ? y : x;
                if (--count == 0)
                    return;
            }
            recover(curr->left, count, x, y);
            recover(curr->right, count, x, y);
        }
    }
};