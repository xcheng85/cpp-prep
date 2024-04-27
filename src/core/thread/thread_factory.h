#pragma once
#include <vector>
#include <memory>
#include <thread>

namespace core::system
{
    using namespace std;
    // packing
    template <typename F, typename... Args>
    inline auto CreateThread(F &&f, Args &&...args)
    {
        // unpacking
        return std::make_unique<std::thread>(std::forward<F>(f), std::forward<Args>(args)...);
    }

    template <typename F, typename... Args>
    inline auto CreateThreadGroup(size_t numThreads, F &&f, Args &&...args)
    {
        std::vector<unique_ptr<thread>> res;
        for(size_t i = 0; i < numThreads; ++i){
            res.emplace_back(std::make_unique<std::thread>(std::forward<F>(f), std::forward<Args>(args)...));
        }
        return res;
    }
}