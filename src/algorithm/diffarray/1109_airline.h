class Solution {
public:
    // airline == array
    // booking: update subrange frequently
    // pattern for diff array
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> diff(n);

        for(const auto& book : bookings) {
            // index-1
            auto left = book[0] - 1, right = book[1] - 1, delta = book[2];
            diff[left] += delta;
            if(right + 1 < n)
                diff[right + 1] -= delta;
        }

        for(size_t i = 1; i < diff.size(); ++i) {
            diff[i] += diff[i-1];
        }
        return diff;
    }
};