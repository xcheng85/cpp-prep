class Solution {
public:
    // decreasing 
    // front: is the max: 
    class DecreasingQueue {
        public: 
            int max() const {
                return _q.front();
            }

            void push(int e) {
                while(!_q.empty() && _q.back() < e) {
                    _q.pop_back();
                }
                // decreasing queue
                _q.push_back(e);
            }

            void pop(int e) {
                // max could change
                if(_q.front() == e) {
                    _q.pop_front();
                }
            }

        private:
            deque<int> _q;
    };

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        DecreasingQueue q;
        for(int i = 0; i < nums.size(); ++i) {
            if(i < k - 1) {
                q.push(nums[i]);
                continue;
            }
            q.push(nums[i]);
            // update result
            res.emplace_back(q.max());
            // meet the k size, kick out old one
            q.pop(nums[i - k + 1]);
        }
        return res;
    }
};