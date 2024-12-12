#include <vector>
#include <deque>

using namespace std;

// like simulation
vector<int> spiralOrder(vector<vector<int>> &matrix)
{
    int m = matrix.size(), n = matrix[0].size();

    // 4 state in the state machine transfer
    
    // current state
    int upper_bound = 0, lower_bound = m - 1;
    int left_bound = 0, right_bound = n - 1;

    vector<int> res;
    // res.size() == m * n 则遍历完整个数组
    while (res.size() < m * n)
    {
        if (upper_bound <= lower_bound)
        {
            // 在顶部从左向右遍历
            for (int j = left_bound; j <= right_bound; j++)
            {
                res.push_back(matrix[upper_bound][j]);
            }
            // 上边界下移
            upper_bound++;
        }

        if (left_bound <= right_bound)
        {
            // 在右侧从上向下遍历
            for (int i = upper_bound; i <= lower_bound; i++)
            {
                res.push_back(matrix[i][right_bound]);
            }
            // 右边界左移
            right_bound--;
        }

        if (upper_bound <= lower_bound)
        {
            // 在底部从右向左遍历
            for (int j = right_bound; j >= left_bound; j--)
            {
                res.push_back(matrix[lower_bound][j]);
            }
            // 下边界上移
            lower_bound--;
        }

        if (left_bound <= right_bound)
        {
            // 在左侧从下向上遍历
            for (int i = lower_bound; i >= upper_bound; i--)
            {
                res.push_back(matrix[i][left_bound]);
            }
            // 左边界右移
            left_bound++;
        }
    }
    return res;
}


vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    int upper_bound = 0, lower_bound = n - 1;
    int left_bound = 0, right_bound = n - 1;
    // 需要填入矩阵的数字
    int num = 1;
    
    while (num <= n * n) {
        if (upper_bound <= lower_bound) {
            // 在顶部从左向右遍历
            for (int j = left_bound; j <= right_bound; j++) {
                //  res.push_back(matrix[upper_bound][j]);
                matrix[upper_bound][j] = num++;
            }
            // 上边界下移
            upper_bound++;
        }
        
        if (left_bound <= right_bound) {
            // 在右侧从上向下遍历
            for (int i = upper_bound; i <= lower_bound; i++) {
                matrix[i][right_bound] = num++;
            }
            // 右边界左移
            right_bound--;
        }
        
        if (upper_bound <= lower_bound) {
            // 在底部从右向左遍历
            for (int j = right_bound; j >= left_bound; j--) {
                matrix[lower_bound][j] = num++;
            }
            // 下边界上移
            lower_bound--;
        }
        
        if (left_bound <= right_bound) {
            // 在左侧从下向上遍历
            for (int i = lower_bound; i >= upper_bound; i--) {
                matrix[i][left_bound] = num++;
            }
            // 左边界右移
            left_bound++;
        }
    }
    return matrix;
}