#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

int main()
{
    io_context ctx;
    steady_timer timer(ctx, chrono::seconds(1));
    timer.async_wait([&](auto const &errorCode)
                     {
        if(!errorCode) {
            std::cout << "Dametime" << std::endl;
        } }

    );

    // node.js blocking event-loop, and exi where there is no pending async operation
    ctx.run();

    return 0;
}