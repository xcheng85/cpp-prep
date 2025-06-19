#pragma once

// consumers in consumer groups
#include <memory>
#include <task.h>
#include <condition_variable>
#include <mutex>


class Stream;
class Consumer : public std::enable_shared_from_this<Consumer>
{
public:
    Consumer(std::shared_ptr<Stream> stream) : _ulock{_mux}, _stream{stream}
    {
    }

    std::shared_ptr<Consumer> getptr()
    {
        return shared_from_this();
    }
    void pickupTask(std::shared_ptr<ITask> task)
    {
        _task = task;
        _ready = true;
    }

    void start();

    void stop()
    {
        _running = false;
    }

    friend class Stream;

private:
    bool _running{true};
    bool _ready{false};
    std::condition_variable _cv;
    std::unique_lock<std::mutex> _ulock;
    std::mutex _mux;
    std::shared_ptr<ITask> _task;
    std::shared_ptr<Stream> _stream;
};