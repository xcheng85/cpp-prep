#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <iostream>
#include <event.h>

namespace core::eda
{
    class ShutDownQueue
    {
    };

    std::ostream &operator<<(std::ostream &os, const ShutDownQueue &)
    {
        os << "ShutDownQueue\n";
        return os;
    }

    // template meta programming to handle all types of events
    template <typename PreviousDispatcher, typename Event, typename Handler>
    class TemplateDispatcher
    {
    public:
        explicit TemplateDispatcher(
            EventQueue &q,
            PreviousDispatcher &prev,
            Handler &&handler)
            : _q{q},
              _prev{prev},
              _handler{std::forward<Handler>(handler)}
        {
            // like a single branched tree, only leaf node _chained = false
            _prev._chained = true;
        }

        // chain of responsibility
        // fp1 * fp2 * ...
        template <typename OtherEvent, typename OtherHandler>
        TemplateDispatcher<TemplateDispatcher, OtherEvent, OtherHandler>
        handle(OtherHandler &&handler)
        {
            return TemplateDispatcher<TemplateDispatcher, OtherEvent, OtherHandler>(
                _q, *this, std::forward<OtherHandler>(handler));
        }

        // noexcept(false) due to exception throw in dtor
        ~TemplateDispatcher() noexcept(false)
        {
            // only the leaf node handling events
            if (!_chained)
            {
                wait_and_dispatch();
            }
        }

    private:
        TemplateDispatcher(TemplateDispatcher const &) = delete;
        TemplateDispatcher &operator=(TemplateDispatcher const &) = delete;
        TemplateDispatcher(TemplateDispatcher &&other) = delete;

        // include all
        template <typename Dispatcher, typename OtherEvent, typename OtherHandler>
        friend class TemplateDispatcher;

        void wait_and_dispatch()
        {
            while (true)
            {
                auto event = _q.wait_and_pop();
                if (dispatch(event))
                {
                    break;
                }
            }
        }

        // select the TemplateDispatcher in the chain to handle the event
        // current node can only handle Event
        bool dispatch(const std::shared_ptr<IEvent> &event)
        {
            // if the dynamic_cast == nullptr, means this node cannot handle this event
            GenericEvent<Event> *typedEvent = dynamic_cast<GenericEvent<Event> *>(event.get());
            if (typedEvent)
            {
                _handler(typedEvent->payload());
                return true;
            }
            else
            {
                return _prev.dispatch(event);
            }
        }

        EventQueue &_q;
        PreviousDispatcher &_prev;
        Handler _handler;
        bool _chained{false};
    };

    // dispatch own the event-handler relationship (stateless)
    // does not own the q
    class Dispatcher
    {
    public:
        explicit Dispatcher(EventQueue &q) : _q{q}
        {
        }

        // create the root node of handler chain
        template <typename Event, typename Handler>
        TemplateDispatcher<Dispatcher, Event, Handler>
        handle(Handler &&handler)
        {
            return TemplateDispatcher<Dispatcher, Event, Handler>(_q, *this, std::forward<Handler>(handler));
        }

        // noexcept(false) due to throw in the dtor
        ~Dispatcher() noexcept(false)
        {
            if (!_chained)
            {
                wait_and_dispatch();
            }
        }

    private:
        EventQueue &_q;
        bool _chained{false};

        Dispatcher(Dispatcher const &) = delete;
        Dispatcher &operator=(Dispatcher const &) = delete;
        Dispatcher(Dispatcher &&other) = delete;

        template <
            typename Dispatcher,
            typename Msg,
            typename Func>
        friend class TemplateDispatcher;

        void wait_and_dispatch()
        {
            while (true)
            {
                auto event = _q.wait_and_pop();
                // only need to know the close_events
                dispatch(event);
            }
        }

        bool dispatch(const std::shared_ptr<IEvent> &event)
        {
            // if the event's payload is ShutDownQueue
            if (dynamic_cast<GenericEvent<ShutDownQueue> *>(event.get()))
            {
                throw ShutDownQueue();
            }
            return false;
        }
    };
}