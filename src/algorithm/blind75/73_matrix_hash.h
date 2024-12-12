class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        unordered_set<int> zeroRow, zeroCol;

        for(int i = 0; i < matrix.size(); ++i) {
            for(int j = 0; j < matrix[0].size(); ++j) {
                if(matrix[i][j] == 0) {
                    zeroRow.insert(i);
                    zeroCol.insert(j);
                }
            }
        }
        
        for(int i = 0; i < matrix.size(); ++i) {
            for(int j = 0; j < matrix[0].size(); ++j) {
                if(zeroRow.count(i) || zeroCol.count(j)) {
                    matrix[i][j] = 0;
                }
            }   
        }
    }
};