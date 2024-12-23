#pragma once

#include <memory>
#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio::ip;
using namespace boost::asio;

// each connection is a session, session become the owner of socket

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket) : _socket(std::move(socket))
    {
    }

    void initRead()
    {
        _read();
    }

private:
    // read: asio input operation
    // boost::asio::buffer: prepare the _buffer to be used within boost.asio's methods
    // reason behind is the *BufferSequence c++ template concept which force composite objects.
    // design of composite buffers: to overcome large message payload which could not allocate block memory due to
    // memory fragmentation
    void _read()
    {
        _extendableBuffer.consume(_bufferSizeReceived);
            // enable_shared_from_this to avoid the self-destruct std::make_shared<Session>(std::move(socket))->initRead();
            auto self(shared_from_this());
        // read into buffer
        // callback when completed
        // the shared_ptr counter increase by lamda copy capture on self
        // here boost::asio::buffer(_buffer, sMaxBufferSizeInBytes) is mutable buffers (which is for written), fixed-length
        // buffer

        // _socket.async_read_some vs asio::async_read vs asio::async_read_until
        // asio::async_read_until: operate on extensible, stream-oriented i/o buffers
        // Extensible buffers: dynamically increase their size when new data is written to them. incoming size unknown
        // specific delimiter. asio::streambuf
        // streambuf contains at least one delimiter but it may contain data after it.
        async_read_until(_socket, _extendableBuffer, '<end>',
                         [this, self](boost::system::error_code errorCode, std::size_t bufferSizeReceived)
                         {
                             std::cout << self.use_count() << std::endl;
                             if (!errorCode)
                             {
                                 // 6. when the asyn reading completes, process the request and prepare the response
                                 _write(bufferSizeReceived);
                             }
                         });

        // // callback on any success buffer transfer
        // _socket.async_read_some(boost::asio::buffer(_buffer, sMaxBufferSizeInBytes),
        //                         [this, self](boost::system::error_code errorCode, std::size_t bufferSizeReceived)
        //                         {
        //                             std::cout << self.use_count() << std::endl;
        //                             if (!errorCode)
        //                             {
        //                                 // 6. when the asyn reading completes, process the request and prepare the response
        //                                 _write(bufferSizeReceived);
        //                             }
        //                         });

        // // callback on any success buffer transfer
        // _socket.async_read_some(boost::asio::buffer(_buffer, sMaxBufferSizeInBytes),
        //                         [this, self](boost::system::error_code errorCode, std::size_t bufferSizeReceived)
        //                         {
        //                             std::cout << self.use_count() << std::endl;
        //                             if (!errorCode)
        //                             {
        //                                 // 6. when the asyn reading completes, process the request and prepare the response
        //                                 _write(bufferSizeReceived);
        //                             }
        //                         });

        // callback will be triggered only when the buffer is filled 100%
        // async_read(_socket, boost::asio::buffer(_buffer, sMaxBufferSizeInBytes),
        //                         [this, self](boost::system::error_code errorCode, std::size_t bufferSizeReceived)
        //                         {
        //                             std::cout << self.use_count() << std::endl;
        //                             if (!errorCode)
        //                             {
        //                                 _write(bufferSizeReceived);
        //                             }
        //                         });
    }

    void _write(std::size_t bufferSize)
    {
        boost::asio::streambuf::const_buffers_type bufs = _extendableBuffer.data();
        std::string str(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + bufferSize);

        auto self(shared_from_this());
        // stl string to asio writable buffer
        async_write(_socket, boost::asio::buffer(str),
                    [this, self](boost::system::error_code ec, std::size_t bufferSize)
                    {
                        std::cout << self.use_count() << std::endl;
                        if (!ec)
                        {
                            _bufferSizeReceived = bufferSize;
                            // 8. when the async reading completes, process the request and prepare the response
                            _read();
                        }
                    });
    }

    // // writing to a tcp socket: output operation
    // // send data to the remote peer connected to the socket
    // void _write(std::size_t bufferSize)
    // {
    //     // socket.async_write_some vs asio::async_write
    //     // async_write_some: may NOT transfer all of the data to the peer. need to track the progress
    //     // async_write: ensure that all data is written before the asynchronous operation completes
    //     auto self(shared_from_this());
    //     async_write(_socket, boost::asio::buffer(_buffer, sMaxBufferSizeInBytes),
    //                 [this, self](boost::system::error_code ec, std::size_t bufferSize)
    //                 {
    //                     std::cout << self.use_count() << std::endl;
    //                     if (!ec)
    //                     {
    //                         // 8. when the async reading completes, process the request and prepare the response
    //                         _read();
    //                     }
    //                 });
    // }

    static constexpr size_t sMaxBufferSizeInBytes = 1024;
    tcp::socket _socket;
    // for mutable buffer which size is predictable or max capped
    std::array<char, sMaxBufferSizeInBytes> _buffer;

    // separate read and write
    streambuf _extendableBuffer;
    // size is needed for streambuf.consume, which == flush the buffer content
    size_t _bufferSizeReceived{0};
};