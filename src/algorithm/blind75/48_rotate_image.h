// 「原地」修改

// transpose + reverse perline

#include <map>
#include <algorithm>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

// transpose + reverse perline

class Solution
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        // 1. transpos in-place
        for(int i = 0; i < m; ++i) {
            for(int j = i + 1; j < n; ++j) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        // 2. reverse per row
        for(int i = 0;  i < m; ++i) {
            for(int j = 0; j < n/2; ++j) {
                swap(matrix[i][j], matrix[i][n - 1-j]);
            }
        }
    }
};