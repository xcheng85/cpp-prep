#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> res;

        unordered_map<int, int> countMap;

        for(const auto& n : nums) {
            ++countMap[n];
        }
        // [count, key]
        // default is maxHeap
        priority_queue<std::pair<int, int>> pq;
        for(const auto&[k, c]:countMap){
            pq.emplace(make_pair(c, k));
        }

        int poppedCount{0};
        while(!pq.empty()){
            if(poppedCount == k){
                break;
            }
            const auto& [c, k] = pq.top();
            res.emplace_back(k);
            pq.pop();
            ++poppedCount;
        }
        return res;
    }
};