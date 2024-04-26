#include "jthread.h"

namespace core::system
{
    jthread::jthread(std::thread &&t)
        : _t{std::move(t)}
    {
    }

    jthread::~jthread()
    {
        if (_t.joinable())
        {
            _t.join();
        }
    }
}