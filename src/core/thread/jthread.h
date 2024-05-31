#pragma once

#include <thread>

namespace core::system
{
    class jthread
    {
    public:
        explicit jthread(std::thread &&t);

        // perfect forwarding
        template <typename F, typename... Args>
        explicit jthread(F &&f, Args &&...args)
            : _t(std::forward<F>(f), std::forward<Args>(args)...)
        {
        }

        virtual ~jthread();
        jthread() = delete;
        // resource handle _t, cannot copy but can move
        jthread(const jthread &t) = delete;
        jthread &operator=(const jthread &t) = delete;

        // must be enabled for stl container with noexcept
        jthread(jthread &&t) noexcept
        {
            // pay attention to the bug:
            // need to clean the existed _t handle
            if (_t.joinable())
            {
                _t.join();
            }

            _t = std::move(t._t);
        }
        jthread &operator=(jthread &&t) noexcept
        {
            // pay attention to the bug:
            // need to clean the existed _t handle
            if (_t.joinable())
            {
                _t.join();
            }
            _t = std::move(t._t);
            return *this;
        }

        inline void join()
        {
            return _t.join();
        }

        inline void detach()
        {
            return _t.detach();
        }

    private:
        std::thread _t;
    };
}
