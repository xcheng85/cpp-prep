// maintain the balance of two pq: 1. min-queue 2. max-queue
// 1. 两个堆中的元素之差不能超过 1
// 2. large 堆 (minHeap)的堆顶元素要大于等于 small 堆(maxHeap)的堆顶元素。

// cut of reverse primyad, bottom-half is maxHeap, top-half reverse and is minHeap

#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <utility>
#include <queue>
#include <map>

using namespace std;

class MedianFinder
{
public:
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        // add to top half
        if (_maxPQ_small.size() >= _minPQ_large.size())
        {
            // to add element to _minPQ_large

            // must ensure the new max in _maxPQ_small is in _minPQ_large
            _maxPQ_small.push(num);
            _minPQ_large.push(_maxPQ_small.top());
            _maxPQ_small.pop();
        }
        else
        {
            // add to bottom half
            // to add element to _maxPQ_small
            // must ensure the new min in _minPQ_large is in _maxPQ_small
            _minPQ_large.push(num);
            _maxPQ_small.push(_minPQ_large.top());
            _minPQ_large.pop();
        }
    }

    double findMedian()
    {
         // 如果元素不一样多，多的那个堆的堆顶元素就是中位数
        if (_minPQ_large.size() < _maxPQ_small.size()) {
            return _maxPQ_small.top();
        } else if (_minPQ_large.size() > _maxPQ_small.size()) {
            return _minPQ_large.top();
        }
        // 如果元素一样多，两个堆堆顶元素的平均数是中位数
        return (double)(_minPQ_large.top() + _maxPQ_small.top()) / 2.0;
    }

private:
    // top half
    priority_queue<int, std::vector<int>, std::greater<>> _minPQ_large;
    // bottom half
    priority_queue<int, std::vector<int>, std::less<>> _maxPQ_small;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */