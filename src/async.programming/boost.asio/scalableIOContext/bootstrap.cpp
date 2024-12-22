#include <iostream>
#include <thread>
#include <syncstream>
#include <chrono>
#include <vector>
#include <boost/asio.hpp>

// here the dispatching i/o events is in different hardware threads
// main threads or some other threads can post event,

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
        scout << "[post task] uid: " << uid << ", threadId: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(1s); });
    }
};

// different threads process simultaneous i/o
class Demultiplexer
{
public:
    void operator()(io_context &ctx, std::string uid)
    {
        scout << "[i/o events demultiplexer] uid: " << uid << ", threadId: " << std::this_thread::get_id() << std::endl;
        ctx.run();
    }
};

int main()
{
    io_context ctx;
    auto wg = make_work_guard(ctx);

    const auto numThreads = std::thread::hardware_concurrency();
    std::vector<std::jthread> demultiplexers;
    std::vector<std::jthread> tasks;
    for (int i = 0; i < numThreads / 2; i++)
    {
        std::jthread t((Demultiplexer()), std::ref(ctx), std::to_string(i));
        demultiplexers.emplace_back(std::move(t));
    }
    std::this_thread::sleep_for(2s);
    for (int i = 0; i < numThreads / 2; i++)
    {
        std::jthread t((Task()), std::to_string(i));
        tasks.emplace_back(std::move(t));
    }
    // // make sure all the jthreads work load finishes.
    // std::this_thread::sleep_for(5s);
    wg.reset();

    return 0;
}