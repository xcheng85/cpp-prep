#pragma once

#include <iostream>
#include <functional>
#include <format>

#define LOG_I(T) std::cout << T << std::endl;
#define LOG_E(T) std::cerr << T << std::endl;

#define LOG_TRACE_I(TRACEID, T) std::cout << std::format("[{}]: {}\n", TRACEID, T);
#define LOG_TRACE_E(TRACEID, T) std::cerr << std::format("[{}]: {}\n", TRACEID, T);


template <typename T>
void logItrable(T iterables)
{
    for (const auto &itr : iterables)
    {
        LOG_I(itr);
    }
}

#define LOG_I_ITRABLE(T) logItrable(T)

// packing
// &&F for anonymous f, univeral reference for both l and rvalue
template <typename F, typename... Args>
inline auto SyncExec(std::string name, F &&f, Args &&...args)
{
    LOG_I(std::format("--->{}", name));
    f(args...);
    LOG_I(std::format("<---{}", name));
    // // force seperate thread
    // // unpacking
    // return std::async(std::launch::async, std::forward<F>(f), std::forward<Args>(args)...);
}