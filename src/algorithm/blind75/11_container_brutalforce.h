#include <map>
#include <algorithm>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int res = 0;
        for(int i = 0; i < height.size(); ++i) {
            for(int j = i + 1;  j < height.size(); ++j) {
                int w = j-i;
                int h = min(height[i], height[j]);
                res = max(res, w * h );
            }
        }
        return res;
    }
};