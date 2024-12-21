#include <coroutine>
#include <string>
#include <iostream>
#include <chrono>
#include <optional>
#include <utility>
#include <assert.h>
#include <thread>
#include <exception>

using namespace std::string_literals; // for ""s
using namespace std::chrono_literals;

// network i/o, node.js style
template <typename CoroToCallerType, typename CallerToCoroType>
struct AsyncStreamer
{
    struct promise_type
    {
        // minimum requirement
        void return_void() noexcept {}

        std::suspend_always initial_suspend() noexcept
        {
            return {};
        }

        std::suspend_always final_suspend() noexcept
        {
            return {};
        }

        void unhandled_exception() noexcept
        {
            // exception to the frame state
            _exception = std::current_exception();
        }

        AsyncStreamer get_return_object() noexcept
        {
            // another ctor
            return AsyncStreamer{*this};
        }

        // extra saurce: string as contract
        // responding to co_yield string_type
        std::suspend_always yield_value(CoroToCallerType payload) noexcept
        {
            // when yield the frame state is updated.
            // std::cout << "yield_value: " << payload << std::endl;
            _coroutineToCaller = payload;
            return {};
        }

        const auto &coroutineToCaller() const noexcept
        {
            // std::cout << "coroutineToCaller: " << _coroutineToCaller << std::endl;
            return _coroutineToCaller;
        }

        const auto &callerToCoroutine() const noexcept
        {
            return _callerToCoroutine;
        }

        auto &callerToCoroutine() noexcept
        {
            return _callerToCoroutine;
        }

        // transform payload (string type) to awaiter object
        // awaiter object: must implement: await_ready, await_resume, await_suspend

        // await_transfrom is the specs behind: co_await
        auto await_transform(CallerToCoroType)
        {
            struct awaiter
            {
                awaiter(promise_type &promise)
                    : _promise(promise)
                {
                }
                // check whether coroutine is suspended
                bool await_ready() const noexcept
                {
                    // only ready if _coroutineToCaller has value
                    return _promise.callerToCoroutine().has_value();
                }

                CallerToCoroType await_resume() const noexcept
                {
                    if (_promise._exception)
                    {
                        std::rethrow_exception(_promise._exception);
                    }

                    // must already passed the await_ready check
                    assert(_promise.callerToCoroutine().has_value());
                    // exchange return the old value and set the new value
                    // nullopt is for std::optional
                    // return *_promise.callerToCoroutine();
                    return *std::exchange(_promise.callerToCoroutine(), std::nullopt);
                }

                void await_suspend(std::coroutine_handle<promise_type>) const noexcept
                {
                }

            private:
                promise_type &_promise;
            };

            return awaiter(*this);
        }

        std::exception_ptr _exception;

    private:
        // coutrine frame state is here
        // for yield coroutine:
        std::optional<CallerToCoroType> _callerToCoroutine;
        // for wait coroutine:
        CoroToCallerType _coroutineToCaller;
    };

    // static method of template class and copy ctor
    explicit AsyncStreamer(promise_type &promise)
        : _handle{
              std::coroutine_handle<promise_type>::from_promise(promise)}
    {
    }

    ~AsyncStreamer() noexcept
    {
        if (!_handle)
        {
            _handle.destroy();
        }
    }

    // for coroutine handle: here contract type is string
    // get: one way communication from coroutine to the caller
    CoroToCallerType get()
    {
        if (_handle.promise()._exception)
        {
            std::rethrow_exception(_handle.promise()._exception);
        }
        if (!_handle.done())
        {
            _handle.resume();
        }
        // coroutine handle is created through from_promise;
        // so it is logical to access the payload
        // promise can access
        return _handle.promise().coroutineToCaller();
    }

    // put: one way communication from caller to the coroutine
    void request(CallerToCoroType payload)
    {
        // everything is going through coroutine handler
        _handle.promise().callerToCoroutine() = payload;
        if (!_handle.done())
        {
            _handle.resume();
        }
    }

private:
    // coroutine handle: specialization of template std::coroutine_handle
    // it has resume, done, destroy
    std::coroutine_handle<promise_type> _handle;
};

struct NetworkClient
{
    struct promise_type
    {
        // minimum requirement
        void return_void() noexcept {}

        std::suspend_always initial_suspend() noexcept
        {
            return {};
        }

        std::suspend_always final_suspend() noexcept
        {
            return {};
        }

        void unhandled_exception() noexcept {}

        NetworkClient get_return_object() noexcept
        {
            // another ctor
            return NetworkClient{*this};
        }

        // extra saurce: string as contract
        // responding to co_yield string_type
        std::suspend_always yield_value(std::string payload) noexcept
        {
            // when yield the frame state is updated.
            // std::cout << "yield_value: " << payload << std::endl;
            _coroutineToCaller = payload;
            return {};
        }

        const auto &coroutineToCaller() const noexcept
        {
            // std::cout << "coroutineToCaller: " << _coroutineToCaller << std::endl;
            return _coroutineToCaller;
        }

        const auto &callerToCoroutine() const noexcept
        {
            return _callerToCoroutine;
        }

        auto &callerToCoroutine() noexcept
        {
            return _callerToCoroutine;
        }

        // transform payload (string type) to awaiter object
        // awaiter object: must implement: await_ready, await_resume, await_suspend

        // await_transfrom is the specs behind: co_await
        auto await_transform(char)
        {
            struct awaiter
            {
                awaiter(promise_type &promise)
                    : _promise(promise)
                {
                }
                // check whether coroutine is suspended
                bool await_ready() const noexcept
                {
                    // only ready if _coroutineToCaller has value
                    return _promise.callerToCoroutine().has_value();
                }

                char await_resume() const noexcept
                {
                    // must already passed the await_ready check
                    assert(_promise.callerToCoroutine().has_value());
                    // exchange return the old value and set the new value
                    // nullopt is for std::optional
                    // return *_promise.callerToCoroutine();
                    return *std::exchange(_promise.callerToCoroutine(), std::nullopt);
                }

                void await_suspend(std::coroutine_handle<promise_type>) const noexcept
                {
                }

            private:
                promise_type &_promise;
            };

            return awaiter(*this);
        }

    private:
        // coutrine frame state is here
        // for yield coroutine:
        std::optional<char> _callerToCoroutine;
        // for wait coroutine:
        std::string _coroutineToCaller;

        std::exception_ptr _exception;
    };

    // static method of template class and copy ctor
    explicit NetworkClient(promise_type &promise)
        : _handle{
              std::coroutine_handle<promise_type>::from_promise(promise)}
    {
    }

    ~NetworkClient() noexcept
    {
        if (!_handle)
        {
            _handle.destroy();
        }
    }

    // for coroutine handle: here contract type is string
    // get: one way communication from coroutine to the caller
    std::string get()
    {
        if (!_handle.done())
        {
            _handle.resume();
        }
        // coroutine handle is created through from_promise;
        // so it is logical to access the payload
        // promise can access
        return _handle.promise().coroutineToCaller();
    }

    // put: one way communication from caller to the coroutine
    void request(char payload)
    {
        // everything is going through coroutine handler
        _handle.promise().callerToCoroutine() = payload;
        if (!_handle.done())
        {
            _handle.resume();
        }
    }

private:
    // coroutine handle: specialization of template std::coroutine_handle
    // it has resume, done, destroy
    std::coroutine_handle<promise_type> _handle;
};

// INPUT: CHAR
// OUTPUT: INT
AsyncStreamer<std::string, char> createStreamingClient()
{
    while (true)
    {
        std::string buffer;
        // caller to coroutine
        while (true)
        {
            char c = co_await char{};
            // std::cout << c << std::endl;
            if (c == '#')
            {
                break;
            }
            buffer += c;
        }
        co_yield buffer;
        // co_yield 1;
    }
}
// ./coroutine-streamer  -1234#2345
int main(int argc, char **argv)
{
    assert(argc == 2);
    std::string payload(argv[1]);
    auto client = createStreamingClient();

    for (char c : payload)
    {
        // mimic network i/o
        client.request(c);
        std::this_thread::sleep_for(1s);
        if (c == '#')
        {
            std::cout << client.get() << std::endl;
        }
    }

    return 0;
}