#pragma once

#include <thread>

namespace core::system
{
    class jthread
    {
    public:
        explicit jthread(std::thread &&t);
        virtual ~jthread();
        jthread() = delete;
        // resource handle _t, cannot copy but can move
        jthread(const jthread &t) = delete;
        jthread &operator=(const jthread &t) = delete;

        // must be enabled for stl container with noexcept
        jthread(jthread &&t) noexcept {
            _t = std::move(t._t);
        }
        jthread &operator=(jthread &&t) noexcept {
            _t = std::move(t._t);
            return *this;
        }

        inline void join() {
            return _t.join();
        }

    private:
        std::thread _t;
    };
}
