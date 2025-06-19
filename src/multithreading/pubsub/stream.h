#pragma once

#include <memory>
#include <task.h>
#include <consumer.h>
#include <queue>
#include <vector>
#include <thread>

// ### problem8: inter-thread communication
// 1. busy check with lock
// 2. check with sleep
// 3. cv and notify_one, notify_all
// #include <conditional_variable>

// pattern1: consumer group style, notify_one
// pattern2: pub-sub style, notify_all

class Stream : public std::enable_shared_from_this<Stream>
{
public:
    Stream() = default;

    void init(int consumerGroupSize) {
        for (int i = 0; i < consumerGroupSize; i++)
        {
            // init due to this getPtr();
            _consumerGrp.emplace_back(std::make_shared<Consumer>(getptr()));
            // member function version
            _threadsForConsumerGrp.emplace_back(std::make_unique<std::thread>(
                &Consumer::start, _consumerGrp.back()));
        }
    }

    std::shared_ptr<Stream> getptr()
    {
        return shared_from_this();
    }

    void stop()
    {
        for (int i = 0; i < _consumerGrp.size(); i++)
        {
            _consumerGrp[i]->stop();
        }

        for (int i = 0; i < _threadsForConsumerGrp.size(); i++)
        {
            _threadsForConsumerGrp[i]->join();
        }
    }

    void publish(std::shared_ptr<ITask> task)
    {
        // critical section for vector
        // raii pattern for lock
        // std::lock_guard lockGuard(c.mut);
        //  same as previous, c++17
        std::scoped_lock lock(_consumerGrpMux);
        if (!_consumerQueue.empty())
        {
            auto consumer = _consumerQueue.front();
            consumer->pickupTask(task);
            // Here is the difference than redis: stream push not work polling
            // inter-thread communication: cv and notify
            // stream needs to know the cv of consumer
            // friend class
            consumer->_cv.notify_one();
            _consumerQueue.pop();
        }
        else
        {
            // all the workers are busy now
            // buffering the task
            std::scoped_lock lock(_taskMux);
            _tasks.push(task);
        }
    }

    // true: consumer is idle, blocking cv unique_lock
    // false: do nothing
    bool addConsumer(std::shared_ptr<Consumer> consumer)
    {
        // no enqueued task yet
        if (_tasks.empty())
        {
            std::scoped_lock lock(_consumerGrpMux);
            _consumerQueue.emplace(consumer);
            return true;
        }
        else
        {
            // pick up the first task
            std::scoped_lock lock(_taskMux);
            auto task = _tasks.front();
            consumer->pickupTask(task);
            _tasks.pop();
            return false;
        }
    }

private:
    // lock-free structure or another implementation of thread-safe queue
    // fifo
    std::queue<std::shared_ptr<ITask>> _tasks;
    std::queue<std::shared_ptr<Consumer>> _consumerQueue;

    std::mutex _taskMux;
    std::mutex _consumerGrpMux;

    // pool
    std::vector<std::shared_ptr<Consumer>> _consumerGrp;
    std::vector<std::unique_ptr<std::thread>> _threadsForConsumerGrp;
};