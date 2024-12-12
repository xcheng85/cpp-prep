
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        bool wordMatched = false;
        unordered_set<int> path;
        int m = board.size();
        int n = board[0].size();
        // every grid could be the source
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j){
                dfs(board, i,j, word, 0, wordMatched, path);
                if(wordMatched) {
                    return true;
                }
            }
        }
        return false;
    }

    void dfs(vector<vector<char>>& board, int i, int j, string word,
             int wordIdx, bool& matched, unordered_set<int>& path ) {
        int m = board.size();
        int n = board[0].size();
        if (wordIdx == word.size()) { 
            // 整个word已经被匹配完，找到了一个答案
            matched = true;
            return;
        }
        if (matched) {  // 已经找到了一个答案，不用再搜索了
            return;
        }

        if (i < 0 || i >= m || j < 0 || j >= n) {
            return;
        }

        // // visited in the path, going backwards
        // int id = i * n + j;
        // if(path.count(id) > 0){
        //     return;
        // }

        if(board[i][j] != word[wordIdx]) {
            // already mismatched
            return;
        }
        // check next char
        // need to record the current path for the dfs. 
        // could use 1d offset from 2d grid
        // set insert and erase is very efficient 
        //path.insert(id);
        board[i][j] = (char)(-board[i][j]);
        dfs(board, i + 1, j, word, wordIdx + 1, matched, path);
        dfs(board, i - 1, j, word, wordIdx + 1, matched, path);
        dfs(board, i, j + 1, word, wordIdx + 1, matched, path);
        dfs(board, i, j - 1, word, wordIdx + 1, matched, path);
        board[i][j] = (char)(-board[i][j]);

        //path.erase(id);
    }
};