class Solution {
public:
    class MonoQueue {
    public:
        int max() const { return _q.front(); }
        int min() const { return _increasingQ.front(); }

        void push(int e) {
            while (!_q.empty() && _q.back() < e) {
                _q.pop_back();
            }
            // decreasing queue
            _q.push_back(e);

            // increasing queue for min
            while (!_increasingQ.empty() && _increasingQ.back() > e) {
                _increasingQ.pop_back();
            }
            _increasingQ.push_back(e);
        }

        void pop(int e) {
            // max could change
            if (_q.front() == e) {
                _q.pop_front();
            }

            // min could change
            if (_increasingQ.front() == e) {
                _increasingQ.pop_front();
            }
        }

    private:
        deque<int> _q;
        deque<int> _increasingQ;
    };

    int longestSubarray(vector<int>& nums, int limit) {
        // try k = 1, 2, ... sliding window
        int res = 0;
        // binary search
        int leftWindowSize = 1, rightWindowSize = nums.size();
        while(leftWindowSize <= rightWindowSize) {
            int windowSize = leftWindowSize + (rightWindowSize - leftWindowSize) / 2;
            MonoQueue q; // reset for each windowSize
            bool resultUpdated = false;

            for (int i = 0; i < nums.size(); ++i) {
                if (i + 1 < windowSize) {
                    q.push(nums[i]);
                    continue;
                }
                q.push(nums[i]);
                int currMax = q.max(), currMin = q.min();
                if(currMax - currMin <= limit) {
                    // cout << "WindowSize: " << windowSize << endl;
                    // cout << "[" << currMin << "," << currMax << "]" << endl;
                    res = max(res, windowSize);
                    // this windowSize is valid, try larger one
                    resultUpdated = true;
                }
                q.pop(nums[i - windowSize + 1]);
                // done with this windowSize
                if(resultUpdated) {
                    break;
                }
            }

            if(resultUpdated) {
                // increase windowSize
                leftWindowSize = windowSize + 1;
            } else {
                rightWindowSize = windowSize - 1;
            }
        }
        return res;
    }
};