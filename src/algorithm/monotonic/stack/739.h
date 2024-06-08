class Solution {
public:
// next greater element
// pair to carry the index
// <=
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> nextGreaterDistance(temperatures.size());
        // first temperature, 2nd 0-based index
        stack<pair<int, int>> increasingS;
        // reverse
        for(int i = temperatures.size() - 1; i >= 0; --i) {
            auto temp = temperatures[i];
            // <= , filter out same temp
            while(!increasingS.empty() && increasingS.top().first <= temp){
                increasingS.pop();
            }
            if(increasingS.empty()) {
                nextGreaterDistance[i] = 0;
            } else {
                nextGreaterDistance[i] = increasingS.top().second - i;
            }
            increasingS.emplace(pair{temp, i});
        }
        return nextGreaterDistance;
    }

};

