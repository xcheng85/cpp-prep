#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> constructDistancedSequence(int n)
    {
        // The integer 1 occurs once in the sequence.
        // Each integer between 2 and n occurs twice in the sequence.

        // total length: 2 * (n - 1) + 1 = 2 * n - 1;
        vector<int> res(2 * n - 1);

        // 1 to n
        vector<int> used(n + 1, 0);

        dfs(0, res);

        return res;
    }

private:
    bool backtracking(int currIdx, vector<int> &ans)
    {
        // stop condition
        if (currIdx == ans.size()) {
            return true;
        }

        if (ans[i]) {
            return dfs(ans, i + 1); 
            // this index is already filled, continue to fill the next index.
        }
        // descanding due to lexi sorting
        for (int j = used.size() - 1; j > 0; --j)
        { // try each number in decending order from n to 1.
            if (used[j])
                continue; // j is already used, skip
            if (j != 1 && (i + j >= ans.size() || ans[i + j]))
                continue; // we can't fill `ans[i + j]` either because `i + j` is out of bound or `ans[i + j]` is already filled. Skip.
            used[j] = 1;  // mark number `j` as used.
            ans[i] = j;   // fill `ans[j]` and `ans[i + j]` (if needed) with `j`.
            if (j != 1)
                ans[i + j] = j;
            if (dfs(ans, i + 1))
                return true;
            ans[i] = 0; // this filling is invalid, backtrack and try the next number.
            if (j != 1)
                ans[i + j] = 0;
            used[j] = 0;
        }
        return false;
    }
};