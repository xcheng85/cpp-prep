#pragma once

#include <memory>
#include <thread>

namespace core::system
{
    // packing
    template <typename F, typename... Args>
    inline auto CreateThread(F &&f, Args &&...args)
    {
        // unpacking
        return std::make_unique<thread>(std::forward<F>(f), std::forward<Args>(args)...);
    }
}