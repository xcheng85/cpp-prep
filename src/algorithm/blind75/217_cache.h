class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
       unordered_set<int> cache;
       for(const auto& n:nums) {
        if(cache.count(n)){
            return true;
        }
        cache.insert(n);
       }
       return false;
    }
};