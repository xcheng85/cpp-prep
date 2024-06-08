

class MyStack {
public:
    MyStack() {
        
    }
    
    void push(int x) {
        _topCache = x;
        _q.emplace(x);
    }
    
    int pop() {
        // update 
        int res = _topCache;
        // needs to know the last element
        while(!_q.empty() ) {
            if(_q.front() != res){
                _q2.emplace(_q.front());
                _topCache = _q.front(); // 2nd last become the cache
            }
            _q.pop();
        }

        while(!_q2.empty()){
            _q.emplace(_q2.front());
            _q2.pop();
        }

        return res;
    }
    
    // needs updated after push and pop
    int top() {
        return _topCache;
    }
    
    bool empty() {
        return _q.empty();
    }

private:
    queue<int> _q;
    queue<int> _q2;
    int _topCache;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */