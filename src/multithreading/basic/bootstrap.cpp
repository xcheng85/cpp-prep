#include <iostream>
#include <memory>
#include <chrono> // profiling
#include <complex>
#include <exception>
#include <algorithm>
#include <future> // task
#include <iostream>
#include <mutex>
#include <assert.h>
#include <thread>

using namespace std::chrono_literals;
using namespace std::complex_literals;

// functor for thread based approach
struct CriticalSection
{
    std::mutex mut;
};

class RenderPass
{
public:
    explicit RenderPass(std::string name, size_t numPasses = 1, bool debug = false)
        : _name(name), _numPasses{numPasses}, _debug{debug}
    {
    }

    RenderPass(const RenderPass &src) : RenderPass(src._name, src._numPasses, src._debug)
    {
    }

    // move constructor
    // no memory allocation, no except risk
    RenderPass(RenderPass &&src) noexcept
        : _name(src._name), _numPasses{src._numPasses}, _debug{src._debug}
    {
    }

    // constructor delegation
    RenderPass(int numPasses = 1)
        : RenderPass("", numPasses, true)
    {
    }

    void run()
    {
        // thread local storage
        callId++;
        this->_numPasses++;
    }

    // mimic function which throws exception
    void throwSomeExeption()
    {
        throw std::runtime_error{"throwSomeExeption"};
    }

    // wrapper to notify the caller main thread
    // c++11
    void throwSomeExeptionWrapper(std::exception_ptr &err)
    {
        try
        {
            throwSomeExeption();
        }
        catch (const std::exception &e)
        {
            err = std::current_exception();
        }
    }

    void operator()(CriticalSection &c)
    {
        // std::lock_guard<std::mutex> lockGuard(c.mut);
        //  same as previous, c++17
        std::scoped_lock lock(c.mut);
        std::this_thread::sleep_for(200ms);
    }

    // assignment operator
    RenderPass &operator=(const RenderPass &s) &
    {
        if (this == &s)
        {
            return *this;
        }
        _numPasses = s._numPasses;
        _debug = s._debug;
        return *this;
    }

    // move assignment operator
    // no memory allocation, no exception
    RenderPass &operator=(RenderPass &&s) noexcept
    {
        _numPasses = s._numPasses;
        _debug = s._debug;
        return *this;
    }
    // non const version
    // & only allow lvalue
    auto &operator[](size_t i) &
    {
        assert(i >= 0 && i < 2);
        if (i == 0)
        {
            return _numPasses;
        }
        else
        {
            // return 1; // auto& must be a lvalue
            return _numPasses;
        }
    }

    // works for both const and non coCppDesignernst
    // & only allow lvalue, because it is a reference
    const auto &operator[](size_t i) const &
    {
        assert(i >= 0 && i < 2);
        if (i == 0)
        {
            return _numPasses;
        }
        else
        {
            // return 1; // auto& must be a lvalue
            return _numPasses;
        }
    }
    // for rvalue, non-reference
    const auto operator[](size_t i) &&
    {
        assert(i >= 0 && i < 2);
        if (i == 0)
        {
            return _numPasses;
        }
        else
        {
            // return 1; // auto& must be a lvalue
            return _numPasses;
        }
    }

    friend RenderPass operator+(RenderPass const &p1, RenderPass const &p2)
    {
        return RenderPass(p1._name, p1._numPasses + p2._numPasses, p1._debug);
    }
    friend auto &NumRenderPass(RenderPass &p);
    friend const auto &NumRenderPass(const RenderPass &p);

    // thread local storage
    static thread_local size_t callId;

private:
    std::string _name;
    size_t _numPasses{0};
    bool _debug{true};
};

// best member accessor pattern
inline auto &NumRenderPass(RenderPass &p)
{
    return p._numPasses;
};

inline const auto &NumRenderPass(const RenderPass &p)
{
    return p._numPasses;
};

// initialize static class member
thread_local size_t RenderPass::callId = 0;

template <typename F, typename... Args>
inline auto Async(F &&f, Args &&...args)
{
    // force seperate thread
    return std::async(std::launch::async, std::forward<F>(f), std::forward<Args>(args)...);
}

auto f()
{
    std::this_thread::sleep_for(1s);
    return 10;
}

// mutli-threading buffer

int main()
{
    constexpr auto d1{250ms};
    std::complex<double> c = 1.0 + 1i;
    auto future = Async(f);
    // synchronization using lock
    CriticalSection c1;
    // functor copy into internal storage for the thread
    std::thread t1(RenderPass("rp1", 1, true), std::ref(c1));
    std::thread t2(RenderPass("rp2", 2, false), std::ref(c1));
    std::thread t3(RenderPass("rp3", 3, true), std::ref(c1));

    // avoid functor copy
    RenderPass rp4{"rp4", 1, true};
    std::thread t4(std::ref(rp4), std::ref(c1));

    // thread + member function
    std::thread t5(&RenderPass::run, &rp4);
    std::thread t6(&RenderPass::run, &rp4);

    // retrieve result from thread
    // create new instance and ref it in the thread
    RenderPass rp5{"rp5", 2, true};
    std::jthread t7(&RenderPass::run, &rp5);

    // exception hander
    std::exception_ptr error;
    std::jthread t8(&RenderPass::throwSomeExeptionWrapper, &rp5, std::ref(error));

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();

    // retrieving result, reference is the key
    std::cout << std::format("NumRenderPass: {}", NumRenderPass(rp5)) << "\n";

    if (error)
    {
        std::cerr << "captured exception in thread\n";
        std::rethrow_exception(error);
    }
    // reader-writer lock: majority read and few writes
}