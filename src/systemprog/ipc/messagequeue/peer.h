#pragma once
// c string
#include <string.h>
#include <iostream>
#include <format>
#include <mqueue.h>

using namespace std;

// p2p connection
// exchange mutual meta: two message queue description

template <size_t MAX_MESSAGES, size_t MAX_MSG_SIZE>
class Peer
{
public:
    // mqd_t: int, a handle
    Peer(const std::string &uid, mqd_t local, mqd_t remote)
        : _uid{uid}
    {
    }

    void run()
    {
        while (true)
        {
            cout << _uid << endl;
            cin >> _send;
            // send from local
            // strlen not include null terminator, here we need bytesize
            // that is why c++ string is way better
            // priority 0
            if (mq_send(_local, _send, strlen(_send) + 1, 0) == -1)
            {
                // message describing the meaning of the value of errno.
                perror("Failed to send message out");
            }
            // receive remote from 
            // removes the oldest message with the highest priority
            // here: priority field is NULL, ignore priority
            if (mq_receive(_remote, _recv, MAX_MSG_SIZE, NULL) == -1)
            {
                // message describing the meaning of the value of errno.
                perror("Failed to receive message from remote peer");
            } else {
                cout << _recv << endl;
            }
        }
    }

private:
    std::string _uid;
    char _send[MAX_MSG_SIZE];
    char _recv[MAX_MSG_SIZE];
    mqd_t _local;
    mqd_t _remote;
};