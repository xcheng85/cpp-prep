class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        // distinct is the pre-requisite
        stack<int> s;
        // key is the value (distinct), value is the next greater element.
        unordered_map<int, int> hm;

        // next greater, back scan
        for(int i = nums2.size() - 1; i >= 0; --i) {
            auto currHeight = nums2[i];
            while(!s.empty() && s.top() < currHeight) {
                s.pop();
            }
            if(s.empty()) {
                hm[currHeight] = -1;
            } else {
                hm[currHeight] = s.top();
            }
            s.push(currHeight);
        }

        vector<int> res;
        for(const auto& n:nums1) {
            if(hm.count(n) == 1) {
                res.emplace_back(hm[n]);
            } else {
                res.emplace_back(-1);
            }
        }
        return res;
    }
};