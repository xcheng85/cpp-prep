#include <iostream>
#include <assert.h>
#include <solution.h>

int main()
{
    Solution s;
    vector<vector<int>> grid{
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1}};

    std::cout << s.numDistinctIslands(grid) << std::endl;

    vector<vector<int>> grid2{
        {1, 1, 0, 1, 1},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1},
        {1, 1, 0, 1, 1}};
    std::cout << s.numDistinctIslands(grid2) << std::endl;
    return 0;
}