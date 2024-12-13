#include <coroutine>

// 1. traits: std::coroutine_traits

// 2. return type of coroutine must define a type name promise_type

// 3. rules to implement: return_void

struct ReturnObjectType
{
    struct promise_type
    {
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

        ReturnObjectType get_return_object() noexcept {
            // another ctor
            return ReturnObjectType{*this};
        }
    };

    explicit ReturnObjectType(promise_type&) {

    }
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

ReturnObjectType corotineFunc()
{
    co_return;
}

int main()
{
    corotineFunc();
}