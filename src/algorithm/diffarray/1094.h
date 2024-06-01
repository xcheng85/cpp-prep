// two places
// 1. -1 for the drop off
// 2. index 0 case
// 3. pre-scan to calculate the range of diff array

class Solution {
public:
    // about understand trip
    // [2, 1, 5]: add 2 from index 1 to 5
    // [3, 3, 7]: add 3 from index 3 to 7
    // recover array, if any beyond capacity false
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        // min from and max to
        int minFrom = 1001, maxTo = -1;
        for (const auto& trip : trips) {
            auto from = trip[1], to = trip[2];
            minFrom = min(from, minFrom);
            maxTo = max(to, maxTo);
        }

        // from to two: [0, 1000]
        int n = maxTo - minFrom + 1;
        vector<int> diff(n);
        for (const auto& trip : trips) {
            // convert to 0-based array
            // trick: drop off
            auto delta = trip[0], from = trip[1] - minFrom, to = trip[2] - 1 - minFrom;
            diff[from]+= delta;
            if(to + 1 < n)
                diff[to + 1] -= delta;
        }
        // trick: miss the first one
        if(diff[0] > capacity)
            return false;
        // recover
        for(size_t i = 1; i < n; ++i) {
            diff[i] += diff[i-1];
            if(diff[i] > capacity) {
                return false;
            }
        }
        return true;
    }
};