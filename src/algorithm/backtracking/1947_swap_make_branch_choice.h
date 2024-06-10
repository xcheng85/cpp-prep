// use swap to make branch choice

class Solution {
public:
    int ans = 0;
    int score(const vector<int>& v1, const vector<int>& v2, int m) {
        int cnt = 0;
        for (int i = 0; i < m; i++) {
            cnt += (v1[i] == v2[i]);
        }
        return cnt;
    }
    void backtracking(int curr, vector<int>& arr,
                      const vector<vector<int>>& students,
                      const vector<vector<int>>& mentors, int n, int m) {
        // termination condition for one combination
        if (curr == arr.size()) {
            int sum = 0;
            for (int i = 0; i < n; i++) {
                // mentor switched
                sum += score(students.at(i), mentors.at(arr[i]), m);
            }
            ans = max(ans, sum);
            return;
        }
        // choose inside the for-loop
        for (int i = curr; i < arr.size(); i++) {
            swap(arr[curr], arr[i]);
            backtracking(curr + 1, arr, students, mentors, n, m);
            swap(arr[curr], arr[i]);
        }
    }

    int maxCompatibilitySum(vector<vector<int>>& students,
                            vector<vector<int>>& mentors) {
        int n = students.size();
        int m = students[0].size();
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            arr[i] = i;
        backtracking(0, arr, students, mentors, n, m);
        return ans;
    }
};