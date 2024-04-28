#pragma once

#include <optional>
#include <memory>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <logger.h>

namespace core::container
{
    using namespace core::utility;

    // front and pop race condition
    // try_pop to replace single-threaded version of
    // .size(), front, pop()

    // wait_pop
    template <typename T>
    class QueueThreadSafe
    {
    public:
        QueueThreadSafe() = default;
        QueueThreadSafe(const QueueThreadSafe &other)
        {
            if (this == &other)
            {
                return;
            }

            std::scoped_lock lock{other._mux};
            _container = other._container;
        }

        QueueThreadSafe &operator=(const QueueThreadSafe &other) = delete;

        void push(const T &v)
        {
            std::scoped_lock lock{_mux};
            _container.push(v);
            // any waiting thread of multiple threads
            _cv.notify_one();
        }

        bool empty() const
        {
            std::scoped_lock lock{_mux};
            return _container.empty();
        }

        // caller pass in
        void pop(std::optional<T> &v)
        {
            std::scoped_lock lock{_mux};
            if (!_container.empty())
            {
                v = _container.front();
                _container.pop();
            }
        }

        // blocking pop, no need optional
        // one off. caller needs to do while(true)
        void bpop(T &v)
        {
            // unique_ptr to work with cv
            // cv's blocking wait with predict
            std::unique_lock lock{_mux};
            // predict = false; unique_lock will be unlocked.
            // receive notify_one, re-evaluate the predict
            _cv.wait(lock, [this]()
                     { return !_container.empty(); });
            v = _container.front();
            _container.pop();
        }

    private:
        std::queue<T> _container;
        mutable std::mutex _mux;
        std::condition_variable _cv;
    };
}