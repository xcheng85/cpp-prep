#pragma once

#include <exception> // custom exception
#include <stack>
#include <memory>
#include <optional>
#include <mutex>
#include <concepts>
#include <chrono>
#include <sstream>
#include <thread>

#include <logger.h>

namespace core::container
{
    using namespace core::utility;
    using namespace std::chrono;

    class EmptyStack : public std::exception
    {
    public:
        const char *what() const noexcept override;
    };

    template <typename T>
    class StackThreadSafe
    {
    public:
        StackThreadSafe(ILogger &logger) : _logger{logger}
        {
        }

        void push(T val)
        {
#ifdef PROFILING
            auto start{steady_clock::now()};
#endif
            std::scoped_lock lock{_mutex};
            std::this_thread::sleep_for(5s);
            _container.push(val);
#ifdef PROFILING
            auto end{steady_clock::now()};
            auto diff{end - start};
            std::ostringstream out;
            out << duration_cast<milliseconds>(diff);
            _logger.info(out.str());
#endif
        }

// concept + variadic parameters
#if __cplusplus > 201402L
        template <typename... R>
            requires(std::same_as<T, R> && ...)
        decltype(auto) emplace(R &&...__args)
        {
            std::scoped_lock lock{_mutex};
            return _container.emplace(std::forward<R>(__args)...);
        }
#endif

        bool empty() const
        {
            std::scoped_lock lock{_mutex};
            return _container.empty();
        }

        // single thread version:
        // top and pop creating the data race problem, it is not atomic

        // top and pop must be protected by mutex
        // single thread version, top and pop on empty stack will throw exception
        // this operation is guarded by empty()
        void pop(std::optional<T> &value)
        {
            std::scoped_lock lock{_mutex};
            if (_container.empty())
            {
            }
            else
            {
                value = _container.top();
                _container.pop();
            }
        }

    private:
        std::mutex _mutex;
        std::stack<T> _container;
        ILogger &_logger;
    };
}