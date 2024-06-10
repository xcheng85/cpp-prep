class Solution {
public:
    // next greater element
    // MONOTONIC STACK
    // [4,2,3,1]
    // [-1, 3, -1, -1]
    // scan right to left
    // next greater element

    vector<int> findBuildings(vector<int>& heights) {
        // vector<T> res(elements.size());
        vector<int> res;
        stack<int> s;
        for (int i = heights.size() - 1; i >= 0; --i) {
            // == obstruct
            while (!s.empty() && s.top() < heights[i]) {
                s.pop();
            }
            if(s.empty()) {
                // no one obstruct
                res.push_back(i);
            }
            s.push(heights[i]);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};