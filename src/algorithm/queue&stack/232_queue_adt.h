class MyQueue {
public:
    MyQueue() {
        
    }
    
    void push(int x) {
        // always to s1
        _s1.push(std::move(x));
    }
    // All the calls to pop and peek are valid.
    int pop() {
        auto t = peek();
        _s2.pop();
        return t;
    }
    
    int peek() {
        if(_s2.empty()) {
            // move _s1 to _s2
            while(!_s1.empty()) {
                _s2.emplace(_s1.top());
                _s1.pop();
            }
        }
        return _s2.top();
    }
    
    bool empty() {
        return _s1.empty() && _s2.empty();
    }
private: 
    stack<int> _s1, _s2;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */