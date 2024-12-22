#pragma once

#include <memory>
#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio::ip;
using namespace boost::asio;

// each connection is a session
class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket) : _socket(std::move(socket))
    {
    }

    void init()
    {
        _read();
    }

private:
    void _read()
    {
        auto self(shared_from_this());
        // read into buffer
        // callback when completed
        // the shared_ptr counter increase by lamda copy capture on self
        _socket.async_read_some(boost::asio::buffer(_buffer, sMaxBufferSizeInBytes),
                                [this, self](boost::system::error_code errorCode, std::size_t bufferSize)
                                {
                                    std::cout << self.use_count() << std::endl;
                                    if (!errorCode)
                                    {
                                        _write(bufferSize);
                                    }
                                });
    }

    void _write(std::size_t bufferSize)
    {
        // async_write_some vs async_write
        // async_write_some: may NOT transfer all of the data to the peer.
        // async_write: ensure that all data is written before the asynchronous operation completes
        auto self(shared_from_this());
        async_write(_socket, boost::asio::buffer(_buffer, sMaxBufferSizeInBytes),
                    [this, self](boost::system::error_code ec, std::size_t bufferSize)
                    {
                        std::cout << self.use_count() << std::endl;
                        if (!ec)
                        {
                            _read();
                        }
                    });
    }

    static constexpr size_t sMaxBufferSizeInBytes = 1024;
    tcp::socket _socket;
    std::array<char, sMaxBufferSizeInBytes> _buffer;
};