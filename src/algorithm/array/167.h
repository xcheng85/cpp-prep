class Solution {
public:
    // binary search
    vector<int> twoSum(vector<int>& numbers, int target) {
        for (int i = 0; i < numbers.size(); ++i) {
            int other = target - numbers[i];
            if (other >= numbers[i]) {
                int otherIdx = binarySearch(numbers, i + 1, numbers.size() - 1, other);
                if(otherIdx >= 0) {
                    return {i + 1, otherIdx + 1};
                }
            } else {
                int otherIdx = binarySearch(numbers, 0, i - 1,other);
                if(otherIdx >= 0) {
                    return {otherIdx + 1, i + 1 };
                }
            }
        }
        return {-1, -1};
    }

    int binarySearch(vector<int>& numbers, size_t l, size_t r, int target) {
        while (l <= r) {
            auto mid = l + (r - l) / 2;
            if (numbers[mid] == target) {
                return mid;
            } else if (numbers[mid] > target) {
                r = mid - 1;
            } else if (numbers[mid] < target) {
                l = mid + 1;
            }
        }
        return -1;
    }
};