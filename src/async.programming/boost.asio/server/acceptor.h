#pragma once

#include <memory>
#include <assert.h>
#include <boost/asio.hpp>
#include <session.h>

using namespace boost::asio::ip;
using namespace boost::asio;

class Acceptor
{
public:
    Acceptor(io_context &ctx, uint32_t port)
        : _acceptor(ctx, tcp::endpoint(tcp::v4(), port))
    {
        _acceptor.listen();
        _tearup();
    }

    void teardown()
    {
        _teardowned.store(true);
    }

private:
    void _tearup()
    {
        // when a client connection completed, the callback will be triggerred.

        // the recursive shows the pattern for constant listening.

        // when you open an acceptor, you're asking the OS for a socket and saving the descriptor to a member variable.
        // here you see why there is a socket in the callback signature

        // 2. init the async accept operation
        _acceptor.async_accept([this](boost::system::error_code errorCode, tcp::socket socket)
                               {
                                   if (!errorCode)
                                   {
                                       // socket ownership transfer
                                       // 4.
                                       std::make_shared<Session>(std::move(socket))->initRead();
                                   }
                                   // 3. when the async accept operation completes, init new one for the next request
                                   if (!_teardowned.load())
                                   {
                                       _tearup();
                                   } else {
                                        _acceptor.close();
                                   } });
    }

    tcp::acceptor _acceptor;
    std::atomic<bool> _teardowned;
};