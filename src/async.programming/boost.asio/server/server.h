#pragma once

#include <memory>
#include <boost/asio.hpp>
#include <session.h>

using namespace boost::asio::ip;
using namespace boost::asio;

// summary of all steps in order for tcp server async (back-end forth between client-server)

// 1.
// 2.
// 3.
// 4.when the async accept operation completes, init new one for the next request
// 5. init the asyn reading to read request from the connected client
// 6. when the asyn reading completes, process the request and prepare the response
// 7. when the async writing completes, switch to 5.

// server develop elements and steps summary.
// 1. socket: open a socket with socket(); opening a file, and you get an integer descriptor you can use with read(), write(), close() etc.
// 2. bind the socket to a network address with bind()
// 3. tell the OS you want to listen for connections on this socket, with listen()
// 4. start accepting incoming connection requests by calling accept()

//     // acceptor is used to listen for connection requests on a specific endpoint and open a socket in response to a request.

// unlike a file, the socket descriptor is not associated with anything outside your process until you do this

// until this point, it could still be used as an outgoing connection, although it's unusual to bind the source address explicitly

// start accepting incoming connection requests by calling accept()

// So when you open an acceptor, you're asking the OS for a socket and saving the descriptor to a member variable.

// When you bind an acceptor, you're just asking the OS to link that socket to an address (but there may be a member variable tracking its state as well, so the acceptor remembers this has been done).

// Note that the "middle ground" passes a protocol type, which is needed to open a socket (it corresponds exactly to the arguments to socket()), but it doesn't have an address (or endpoint), so it can't bind that socket yet.

class Server
{
public:
    // 1. allocate an accepat socket and bind it to the tcp port
    Server(io_context &ctx, uint32_t port)
        : _acceptor(ctx, tcp::endpoint(tcp::v4(), port))
    {
        _accept();
    }

private:
    void _accept()
    {
        // when a client connection completed, the callback will be triggerred.

        // the recursive shows the pattern for constant listening.

        // when you open an acceptor, you're asking the OS for a socket and saving the descriptor to a member variable.
        // here you see why there is a socket in the callback signature

        // 2. init the async accept operation
        _acceptor.listen();
        _acceptor.async_accept([this](boost::system::error_code errorCode, tcp::socket socket)
                               {
            if (!errorCode) {
                // socket ownership transfer
                // 4. 
                std::make_shared<Session>(std::move(socket))->initRead();
            }
            // 3. when the async accept operation completes, init new one for the next request
            _accept(); });
    }

    tcp::acceptor _acceptor;
};