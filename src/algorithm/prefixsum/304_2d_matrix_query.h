class NumMatrix {
public:
    // hint: o(1) for sumRegion
    // combination theory
    //
    NumMatrix(vector<vector<int>>& matrix) {

        int numR = matrix.size(), numC = matrix[0].size();
        _prefixSum.resize(numR, vector<int>(numC, 0));
        for (int i = 0; i < numR; ++i) {
            for (int j = 0; j < numC; ++j) {
                int sum = matrix[i][j];
                if (i >= 1) {
                    sum += _prefixSum[i - 1][j];
                }
                if (j >= 1) {
                    sum += _prefixSum[i][j - 1];
                }
                if (i >= 1 && j >= 1) {
                    sum -= _prefixSum[i - 1][j - 1];
                }
                _prefixSum[i][j] = sum;

                //cout << i << "," << j << ": " << _prefixSum[i][j] << endl;
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int sum = _prefixSum[row2][col2];
        if(row1 >= 1) {
            sum -= _prefixSum[row1 - 1][col2];
        }
        if(col1 >= 1) {
            // easy to mistake
            sum -= _prefixSum[row2][col1 - 1];
        }
        if(row1 >= 1 && col1 >= 1) {
            sum += _prefixSum[row1 - 1][col1 - 1];
        }
        return sum;
    }

private:
    vector<vector<int>> _prefixSum;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */