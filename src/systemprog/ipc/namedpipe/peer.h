#pragma once

#include <string>
#include <unistd.h>
#include <fcntl.h> // posix file
#include <iostream>
#include <format>

using namespace std;

class Peer
{
public:
    Peer() = delete;
    explicit Peer(const std::string &uid, const std::string &filePath)
        : _uid{uid},
          _filePath{filePath}
    {
    }

    void run()
    {

#ifdef WRITER
        while (true)
        {
            {
                // OPEN:  System Calls
                auto fd = open(_filePath.c_str(), O_WRONLY);
                cout << _uid << "\n";

                string message;
                // will resize the message
                cin >> message;

                cout << "writing:" << message << "\n";
                // write to the named pipe backed by the fd
                write(fd, message.c_str(), message.length());
                close(fd);
            }

            // read from the named pipe
            {
                auto fd = open(_filePath.c_str(), O_RDONLY);
                // write to the named pipe backed by the fd
                // read up to maxMessageSize;
                read(fd, _recv, maxMessageSize);
                cout << "reading:" << _recv << "\n";
                close(fd);
            }
        }
#elif defined(READER)
        while (true)
        {
            // read from the named pipe
            {
                auto fd = open(_filePath.c_str(), O_RDONLY);
                // write to the named pipe backed by the fd
                // read up to maxMessageSize;
                read(fd, _recv, maxMessageSize);
                cout << "reading: " << _recv << "\n";
                close(fd);
            }

            {
                // OPEN:  System Calls
                auto fd = open(_filePath.c_str(), O_WRONLY);
                cout << _uid << "\n";

                string message;
                // will resize the message
                cin >> message;
                cout << "writing:" << message << "\n";
                // write to the named pipe backed by the fd
                write(fd, message.c_str(), message.length());
                close(fd);
            }
        }
#endif
    }

private:
    std::string _uid;
    std::string _filePath;
    constexpr static size_t maxMessageSize{128};

    char _recv[maxMessageSize];
};