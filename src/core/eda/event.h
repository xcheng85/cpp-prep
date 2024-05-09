#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <iostream>

#include <queuethreadsafe.h>

namespace core::eda
{
    using namespace core::container;
    // allow heterogenous object stored in once stl container
    class IEvent
    {
    public:
        virtual ~IEvent()
        {
        }

        virtual void print(std::ostream &os) const = 0;
    };

    std::ostream &operator<<(std::ostream &os, const IEvent &e)
    {
        e.print(os);
        return os;
    }

    // allow any type with template metaprogramming
    // Payload must support copy constructable
    template <typename Payload>
    class GenericEvent : public IEvent
    {
    public:
        explicit GenericEvent(const Payload &payload) : _payload{payload}
        {
        }

        inline const Payload& payload() const{
            return _payload;
        }

    private:
        virtual void print(std::ostream &os) const
        {
           // os << _payload << "\n";
        }
        Payload _payload;
    };

    using EventQueue = QueuePtrThreadSafe<IEvent>;
}