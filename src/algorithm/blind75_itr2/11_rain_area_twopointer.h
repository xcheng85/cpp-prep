class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxArea = 0;
        int l = 0, r = height.size() - 1;
        while(l < r) {
            int area = (r - l) * min(height[r], height[l]);
            maxArea = max(maxArea, area);

            // w is decreasing, the only way to increase area is to increase the minHeight of two
            if(height[r] < height[l]) {
                --r;
            } else {
                l++;
            }
        }
        return maxArea;
    }
};