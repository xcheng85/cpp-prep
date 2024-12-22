#include <memory>
#include <iostream>

#include <server.h>
// std::enable_shared_from_this:

// create shared_ptr objects for instances that are already managed by another shared_ptr object

// help to create more shared_ptr objects from an existing one in a sfafe manner

namespace core
{
    struct Foo
    {
        ~Foo()
        {
            std::cout << "Foo\n";
        }
    };

    struct Foo2 : std::enable_shared_from_this<Foo2>
    {
        ~Foo2()
        {
            std::cout << "Foo\n";
        }
    };
};

// Foo
// Foo
// free(): double free detected in tcache 2
// Aborted (core dumped)

int main()
{
    // auto f = new core::Foo();
    // std::shared_ptr<core::Foo> p1{f}; // manage raw pointer
    // std::shared_ptr<core::Foo> p2{f}; // manage raw pointer

    auto f = new core::Foo2();
    std::shared_ptr<core::Foo2> p1{f};                      // manage raw pointer
    std::shared_ptr<core::Foo2> p2{p1->shared_from_this()}; // manage raw pointer

    // testing: telnet localhost 3000
    // quit telnet: ctrl + ], then quit

    constexpr int port = 3000;
    try
    {
        boost::asio::io_context ctx;
        Server server(ctx, port);
        ctx.run();
    }
    catch (std::exception &ex)
    {
        std::cerr << "Exception: " << ex.what() << "\n";
    }
    return 0;
}