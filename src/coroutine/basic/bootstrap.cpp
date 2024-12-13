#include <coroutine>
#include <string>
#include <iostream>

using namespace std::string_literals; // for ""s

// 1. traits: std::coroutine_traits

// 2. return type of coroutine must define a type name promise_type

// 3. rules to implement: return_void

// 4. coroutine handle: for coroutine caller to use

//

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
        std::suspend_always yield_value(std::string msg) noexcept
        {
            // when yield the frame state is updated.
            _msg = std::move(msg);
            return {};
        }

        auto payload() noexcept{
            return _msg;
        }

    private:
        // coutrine frame state is here
        std::string _msg;
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
    std::string get()
    {

        if (!_handle.done())
        {
            _handle.resume();
        }
        // coroutine handle is created through from_promise;
        // so it is logical to access the payload
        // promise can access 
        return std::move(_handle.promise().payload());
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
    // s requires string_literals
    co_yield "Dametime"s;

    co_return;
}

int main()
{
    auto returnType = corotineFunc();

    std::cout << returnType.get() << std::endl;

    return 0;
}