#include <coroutine>
#include <string>
#include <iostream>

using namespace std::string_literals; // for ""s

// 1. traits: std::coroutine_traits

// 2. return type of coroutine must define a type name promise_type

// 3. rules to implement: return_void

// 4. coroutine handle: for coroutine caller to use

// 5. yielding coroutine: has its specs

// 6. waiting coroutine has its specs

// wrapper type around promise_type
struct ReturnObjectWrapper
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

        ReturnObjectWrapper get_return_object() noexcept
        {
            // another ctor
            return ReturnObjectWrapper{*this};
        }

        // extra saurce: string as contract
        // responding to co_yield string_type
        std::suspend_always yield_value(std::string payload) noexcept
        {
            // when yield the frame state is updated.
            _coroutineToCaller = std::move(payload);
            return {};
        }

        const auto &coroutineToCaller() const noexcept
        {
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
        auto await_transform(std::string)
        {
            struct awaiter
            {
                awaiter(promise_type &promise)
                    : _promise(promise)
                {
                }

                bool await_ready() const noexcept
                {
                    return true;
                }

                std::string await_resume() const noexcept
                {
                    return std::move(_promise.callerToCoroutine());
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
        std::string _coroutineToCaller;
        // for wait coroutine:
        std::string _callerToCoroutine;
    };

    // static method of template class and copy ctor
    explicit ReturnObjectWrapper(promise_type &promise)
        : _handle{
              std::coroutine_handle<promise_type>::from_promise(promise)}
    {
    }

    ~ReturnObjectWrapper() noexcept
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
        return std::move(_handle.promise().coroutineToCaller());
    }

    // put: one way communication from caller to the coroutine
    void put(std::string payload)
    {
        // everything is going through coroutine handler
        _handle.promise().callerToCoroutine() = std::move(payload);
    }

private:
    // coroutine handle: specialization of template std::coroutine_handle
    // it has resume, done, destroy
    std::coroutine_handle<promise_type> _handle;
};

// /home/xcheng85/github.com/xcheng85/cpp-prep/src/coroutine/basic/bootstrap.cpp: In function ‘ReturnTypeDef corotineFunc()’:
// /home/xcheng85/github.com/xcheng85/cpp-prep/src/coroutine/basic/bootstrap.cpp:15:5: error: no member named ‘return_void’ in ‘std::__n4861::__coroutine_traits_impl<ReturnTypeDef, void>::promise_type’ {aka ‘ReturnTypeDef::promise_type’}
//    15 |     co_return;
//       |     ^~~~~~~~~
// /home/xcheng85/github.com/xcheng85/cpp-prep/src/coroutine/basic/bootstrap.cpp:14:15: error: no member named ‘initial_suspend’ in ‘std::__n4861::__coroutine_traits_impl<ReturnTypeDef, void>::promise_type’ {aka ‘ReturnTypeDef::promise_type’}
//    14 | ReturnTypeDef corotineFunc() {
//       |               ^~~~~~~~~~~~
// /home/xcheng85/github.com/xcheng85/cpp-prep/src/coroutine/basic/bootstrap.cpp:14:15: error: no member named ‘unhandled_exception’ in ‘std::__n4861::__coroutine_traits_impl<ReturnTypeDef, void>::promise_type’ {aka ‘ReturnTypeDef::promise_type’}
// /home/xcheng85/github.com/xcheng85/cpp-prep/src/coroutine/basic/bootstrap.cpp:14:15: error: no member named ‘final_suspend’ in ‘std::__n4861::__coroutine_traits_impl<ReturnTypeDef, void>::promise_type’ {aka ‘ReturnTypeDef::promise_type’}
// /home/xcheng85/github.com/xcheng85/cpp-prep/src/coroutine/basic/bootstrap.cpp:14:15: error: no member named ‘get_return_object’ in ‘std::__n4861::__coroutine_traits_impl<ReturnTypeDef, void>::promise_type’ {aka ‘ReturnTypeDef::promise_type’}
// gmake[2]: *** [bin/coroutine/basic/CMakeFiles/coroutine-basic.dir/build.make:76: bin/coroutine/basic/CMakeFiles/coroutine-basic.dir/bootstrap.cpp.o] Error 1
// gmake[1]: *** [CMakeFiles/Makefile2:4609: bin/coroutine/basic/CMakeFiles/coroutine-basic.dir/all] Error 2

ReturnObjectWrapper corotineFunc()
{
    // co_await
    const auto payload = co_await std::string{};

    // s requires string_literals
    co_yield payload;

    co_return;
}

int main()
{
    auto returnType = corotineFunc();
    // wait coroutine
    returnType.put("from Giannis to Dametime");
    // yield coroutine
    std::cout << returnType.get() << std::endl;

    return 0;
}