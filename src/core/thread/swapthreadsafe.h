#pragma once

#include <thread>
#include <algorithm>
#include <concepts>

namespace core::system
{
    class IThreadSafeSwappable
    {
    public:
        virtual ~IThreadSafeSwappable() = default;
        // look at concept HasMutex
        virtual std::mutex& mutex() = 0;
        // to swap, Type T shall be move-constructible and move-assignable (or have swap defined for it, for version (2)).
    };

    template <typename T>
    concept HasMutex = requires(T x) {
        x.mutex();
    };

    // force mutex() api
    // move_constructible requirements of std::swap
    template <typename T>
    requires HasMutex<T> && move_constructible<T>
    inline void SwapThreadSafe(T &v1, T &v2)
    {
        if (&v1 == &v2)
        {
            return;
        }
        std::scoped_lock lock{v1.mutex(), v2.mutex()};
        std::swap(v1, v2);
    };
}