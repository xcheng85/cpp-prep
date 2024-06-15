#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        // 1 <= s.length <= 25
        unordered_set<string> visit;

        queue<string> q;

        q.push(s);
        visit.insert(s);

        vector<string> ans;

        while (!q.empty()) {
            queue<string> nextLevel;
            // clean the current level
            while (!q.empty()) {
                auto curr = q.front();
                q.pop();
                if (isValidString(curr)) {
                    cout << curr << endl;

                    // If answer is found, make level true
                    // so that valid string of only that level
                    // are processed.
                    ans.emplace_back(curr);
                }
                if(ans.empty()){
                    for (int i = 0; i < curr.length(); i++) {
                        if (!isParenthesis(curr[i]))
                            continue;
                        auto temp = curr.substr(0, i) + curr.substr(i + 1);
                        if (visit.find(temp) == visit.end()) {
                            nextLevel.push(temp);
                            visit.insert(temp);
                        }
                    }
                }

            }
            if(!ans.empty()){
                break;
            }
            swap(q, nextLevel);
        }
        return ans;
    }

    bool isParenthesis(char c) { return ((c == '(') || (c == ')')); }

    //  method returns true if string contains valid
    // parenthesis
    bool isValidString(string str) {
        int cnt = 0;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == '(')
                cnt++;
            else if (str[i] == ')')
                cnt--;
            if (cnt < 0)
                return false;
        }
        return (cnt == 0);
    }
};