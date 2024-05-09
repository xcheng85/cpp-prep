#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <iostream>
#include <event.h>
#include <publisher.h>
#include <dispatcher.h>

namespace core::eda
{
    // subscriber own the queue
    // subscriber will pull the queue and call upstream threads. such as: atm controller ---> bank
    class Publisher;
    class Subscriber
    {
    public:
        // publisher to this subscriber.
        Publisher publisher()
        {
            return Publisher(_q);
        }

        Dispatcher dispatcher()
        {
            return Dispatcher(_q);
        }

    private:
        EventQueue _q;
    };
}