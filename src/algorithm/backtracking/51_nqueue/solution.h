#include <vector>
#include <string>

// return all the combination

// each decision: put q at col at a row

// end of decistion tree, row beyond board

using namespace std;

class Solution
{
public:
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> results;
        // n . each row
        // initialize n "."
        vector<string> board(n, string(n, '.'));
        backtracking(results, board, 0, n);
        return results;
    }

private:
    // row: indicate end condition and traversal with decision tree
    void backtracking(vector<vector<string>> &results, vector<string> &board, int row, int n)
    {
        if (row == n)
        {
            results.emplace_back(board);
            return;
        }

        for (int c = 0; c < n; ++c)
        {
            // choose one decision path
            if (!isValidBoard(board, row, c, n))
            {
                continue;
            }
            board[row][c] = 'Q';
            // advanced the decision tree to the next row
            backtracking(results, board, row + 1, n);
            board[row][c] = '.'; // backtrack
        }
    }

    // after assign Q at [row, col], check if still valid board
    bool isValidBoard(vector<string> &board, int row, int col, int n)
    {
        // no need to check current row, cus the decision is made cols per row
        for (int r = 0; r < n; ++r)
        {
            if (board[r][col] == 'Q')
            {
                return false;
            }
        }

        // diagnol
        // only two direction
        // **               **
        //    **         **
        //     [row, col]
        // has not been visited
        // for loop with two vars
        for (int r = row - 1, c = col - 1; r >= 0 && col >= 0; --r, --c)
        {
            if (board[r][c] == 'Q')
            {
                return false;
            }
        }

        for (int r = row - 1, c = col + 1; r >= 0 && col < n; --r, ++c)
        {
            if (board[r][c] == 'Q')
            {
                return false;
            }
        }

        return true;
    }
};