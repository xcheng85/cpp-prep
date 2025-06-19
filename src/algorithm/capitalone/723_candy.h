#include <string>
#include <iostream>
using namespace std;

class Solution
{
public:
    vector<vector<int>> candyCrush(vector<vector<int>> &board)
    {
        // every cell stats

        int row = board.size();
        int col = board[0].size();

        vector<vector<int>> h(row, vector<int>(col, 0));
        vector<vector<int>> v(row, vector<int>(col, 0));
        vector<vector<int>> v(row, vector<int>(col, 0));
        
        bool stable = false;
        while (!stable)
        {
            // horizontal, look left
            for (int c = 1; c < col; c++)
            {
                for (int r = 0; r < row; r++)
                {
                    if (board[r][c] == board[r][c - 1])
                    {
                        h[r][c] = 1 + h[r][c - 1];
                    }
                }
            }
            // v, look up
            for (int r = 1; r < row; r++)
            {
                for (int c = 0; c < col; c++)
                {
                    if (board[r][c] == board[r - 1][c])
                    {
                        v[r][c] = 1 + v[r - 1][c];
                    }
                }
            }

            // colume-wise crash, from the last row
            bool hasAnyCrash = false;
            for(int r = row - 1; r >= 0; r--) {
                for(int c = 0; c < col; c++) {
                    //  three or more
                     if (v[r][c] >= 2 || h[r][c] >= 2 ){
                        // update the field
                     }
                }
            }
        }
    }
};