#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <iostream>
#include <event.h>

namespace core::eda
{
    // publisher does not own the queue (state less)

    // receiver own the queue (state )

    // dispatch own the event-handler relationship (stateless)
    
    class Publisher
    {
    public:
        Publisher() = delete;
        explicit Publisher(EventQueue &q) : _q{q}
        {
        }

        template <typename Payload>
        void publish(const Payload &payload)
        {
            _q.push<GenericEvent<std::remove_reference_t<Payload>>>(payload);
        }

    private:
        EventQueue &_q;
    };
}