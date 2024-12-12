#include <vector>
using namespace std;

// basically is the w * min(h1, h2)
// max(w)
// max(min(h1, h2)) 
// w is determined by r - l (two pointers)
// when to move left or right pointer ? we need to strive for larger value for h. so 
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1; // starting from max w
        int maxArea = std::numeric_limits<int>::min();
        while(l < r) {
            int w = r - l; 
            int hLeft = height[l], hRight = height[r];
            maxArea = std::max(maxArea, w * std::min(hLeft, hRight));
            if(hLeft < hRight) {
                ++l;
            } else {
                --r;
            }
        }
        return maxArea;
    }
};