#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <string>

using namespace std;

struct TrieNode
{
    unordered_map<char, TrieNode *> nodes;
    string word{""};
};

class Solution
{
private:
    vector<vector<char>> _board;
    vector<string> _result;
    TrieNode _root;

public:
    vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
    {
        for (string &word : words)
        {
            TrieNode *curr = &_root;
            for (const auto &c : word)
            {
                if (!curr->nodes.count(c))
                {
                    TrieNode *tmp = new TrieNode();
                    curr->nodes[c] = tmp;
                }
                curr = curr->nodes[c];
            }
            // leaf
            curr->word = word;
        }

        this->_board = board;

        // Step 2). Backtracking starting for each cell in the board
        // every grid cell as start
        int m = board.size();
        int n = board[0].size();

        for (int row = 0; row < m; ++row)
        {
            for (int col = 0; col < n; ++col)
            {
                preOrderTraverse(board, &_root, row, col);
            }
        }

        return this->_result;
    }

private:
    void preOrderTraverse(vector<vector<char>> &board, TrieNode *curr, int row, int col)
    {
        // exit condition 1
        if (row < 0 || row >= this->_board.size() || col < 0 || col >= this->_board[0].size())
        {
            return;
        }

        char c = this->_board[row][col];

        // exit condition 2
        if (!curr->nodes.count(c))
        {
            return;
        }

        TrieNode *currNode = curr->nodes[c];

        // is leaf
        // preorder style
        if (currNode->word != "")
        {
            this->_result.push_back(currNode->word);
            // visited.
            currNode->word = ""; // prevent duplicate entries
        }

        // visited in a path. avoid regress
        this->_board[row][col] = '#';
        // child nodes in the tree view
        int rowOffset[] = {-1, 0, 1, 0};
        int colOffset[] = {0, 1, 0, -1};
        for (int i = 0; i < 4; ++i)
        {
            // no early branch , due to multiple answers
            preOrderTraverse(board, currNode, row + rowOffset[i], col + colOffset[i]);
        }
        // back track in a path
        this->_board[row][col] = c;
    }
};