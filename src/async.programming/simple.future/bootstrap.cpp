#include <iostream>
#include <assert.h>
#include <memory>  // smart pointer
#include <chrono>  // profiling
#include <complex> // math complex
#include <exception>
#include <algorithm>
#include <future> // task
#include <mutex>
#include <thread>     //jthread
#include <functional> // std::ref

using namespace std::chrono_literals;
using namespace std::complex_literals;

// packing ...
// perferct forwarding
template <typename F, typename... Args>
inline auto Async(F &&f, Args &&...args)
{
    // force seperate thread
    // unpacking
    return std::async(std::launch::async, std::forward<F>(f), std::forward<Args>(args)...);
}

class LoggingMiddleware
{
public:
    std::string operator()(const std::string &payload){
        return std::format("{} {}", std::chrono::system_clock::now(), payload);
    }
};

int main()
{
    auto future = Async(LoggingMiddleware(), "test");
    // future block call
    std::cout << future.get() << "\n";
}
