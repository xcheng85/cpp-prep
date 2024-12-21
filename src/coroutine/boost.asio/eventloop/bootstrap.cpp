#include <iostream>
#include <thread>
#include <syncstream>
#include <chrono>
#include <boost/asio.hpp>

using namespace std::chrono_literals;
using namespace boost::asio;

int main()
{
    io_context ctx;
    auto wg = make_work_guard(ctx);

    // launch two threads
    // thread1: run the event loop
    // thread2: enqueue task
    // work guard will keep event loop until reset.

    std::thread eventloop([&]()
                          { ctx.run(); });

    std::thread enqueueTask([&]()
                            {
                            std::this_thread::sleep_for(5s);
                            ctx.post([](){
                                std::cout << "enqueue Task done" << std::endl;
                            }); });

    // without wg.reset(), it will block here
    // must larger than line 25.
    std::this_thread::sleep_for(10s);
    wg.reset();
    eventloop.join();
    enqueueTask.join();
    return 0;
}