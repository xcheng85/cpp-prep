#include <iostream>
#include <thread>
#include <syncstream>
#include <chrono>
#include <vector>
#include <boost/asio.hpp>

// shared io context will have contention with simultaneous i/o operations

using namespace std::chrono_literals;
using namespace boost::asio;

#define scout std::osyncstream(std::cout)

// // thread + functor who implements "void operator()(...)"
class Task
{
public:
    void operator()(std::string uid)
    {
        boost::asio::post([uid]()
                          {
                            // completion handler is exexute on different threads, which is told by threadid PRINTED. 
        scout << "uid: " << uid << ", threadId: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(1s); });
    }
};

int main()
{
    io_context ctx;
    auto wg = make_work_guard(ctx);

    // 1. threads to run the context (event loop, blocking)
    std::jthread eventThreads([&ctx]()
                              { ctx.run(); });

    const auto numThreads = std::thread::hardware_concurrency();
    std::vector<std::jthread> threads;

    for (int i = 0; i < numThreads; i++)
    {
        std::jthread t((Task()), std::to_string(i));
        threads.emplace_back(std::move(t));
    }
    // make sure all the jthreads work load finishes.
    std::this_thread::sleep_for(5s);
    wg.reset();

    return 0;
}