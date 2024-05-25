#pragma once

#include <string.h>
#include <string>
#include <iostream>

using namespace std;

template <size_t MAX_MSG_SIZE>
class Peer
{
public:
    Peer() = delete;
    Peer(const Peer &) = delete;
    Peer(Peer &&) = delete;
    Peer(const string &uid, void *wShmAddress, void *rShmAddress)
        : _uid{uid},
          _wShmAddress{wShmAddress},
          _rShmAddress{rShmAddress}
    {
    }

    void run()
    {
        while (true)
        {
            cout << _uid << endl;
            // cin >> will stop at space
            getline(std::cin, _send);
            cout << _send << endl;
            // int byteLen = strlen(_send) + 1;
            // dst, src,
            memcpy(_wShmAddress, _send.c_str(), _send.length());
            cout << "BEFORE" << endl;
            // block by getchar and wait for other peer to proceed
            getchar();
             cout << "AFTER" << endl;
            // memcpy up to
            memcpy(_recv, _rShmAddress, MAX_MSG_SIZE);
                     cout << "AFTER: memcpy" << endl;
        }
    }

private:
    const string _uid;
    void *_wShmAddress;
    void *_rShmAddress;
    std::string _send;
    char _recv[MAX_MSG_SIZE];
};