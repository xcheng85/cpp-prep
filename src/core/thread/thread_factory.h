#pragma once
#include <vector>
#include <memory>
#include <thread>
#include <future>

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

    // thread-based
    template <typename F, typename... Args>
    inline auto CreateThreadGroup(size_t numThreads, F &&f, Args &&...args)
    {
        std::vector<unique_ptr<thread>> res;
        for (size_t i = 0; i < numThreads; ++i)
        {
            res.emplace_back(std::make_unique<std::thread>(std::forward<F>(f), std::forward<Args>(args)...));
        }
        return res;
    }

    // future task-based
    template <typename F, typename... Args>
    inline auto SpawnTask(F &&f, Args &&...args)
    {
        // typename is a must due to a template
        using ReturnType = typename std::result_of<F(Args...)>::type;
        // std::packaged_task<ReturnType(Args...)> task(f, args...);
        // package_task only took function,
        // parameters is provided when it is executed in line 42.
        std::packaged_task<ReturnType(Args...)> task(f);
        auto res{task.get_future()};
        //task, lvalue must move
        std::thread t{std::move(task), std::forward<Args>(args)...};
        t.detach();
        // compiler optim
        return res;
    }
}