#include <stackthreadsafe.h>
#include <thread_factory.h>
#include <swapthreadsafe.h>
#include <random>
#include <logger.h>
#include <dlistthreadsafe.h>
#include <mapthreadsafe.h>
#include <finegrainedhashmapthreadsafe.h>
#include <hetrogenousmap.h>

using namespace core::container;
using namespace core::system;
using namespace core::utility;

template <typename T>
class SwapObject : private IThreadSafeSwappable
{
public:
    SwapObject(const T &data) : _data{data}
    {
    }
    std::mutex &mutex() override
    {
        return _mutex;
    }
    // concept move_constructible
    SwapObject(SwapObject &&other) noexcept
    {
        if (this == &other)
        {
            return;
        }
        if (other.mutex().try_lock())
        {
            _data = std::move(other._data);
            other.mutex().unlock();
            return;
        }
        else
        {
            // deadlock due to lock twice
            // std::scoped_lock lock{other.mutex()};
            //  for data entry
            _data = std::move(other._data);
        }
    }
    SwapObject &operator=(SwapObject &&other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        if (other.mutex().try_lock())
        {
            _data = std::move(other._data);
            other.mutex().unlock();
        }
        else
        {
            // deadlock due to lock twice
            // std::scoped_lock lock{other.mutex()};
            //  for data entry
            _data = std::move(other._data);
        }
        return *this;
    }

    inline const auto &data() const
    {
        return _data;
    }

private:
    std::mutex _mutex;
    T _data;
};
struct A;
struct B;
struct Weight;

int main()
{
    srand(time(0));
    auto &logger = DefaultLogger::Instance();

    using FParams = HetrogenousMap<A, B, Weight>;
    auto data = FParams::Create().SetKV<A>(true).SetKV<B>(std::string("abc")).SetKV<Weight>(15);
    cout << data.Get<A>() << std::endl;
    cout << data.Get<B>() << std::endl;

    SwapObject o1{1}, o2{2};
    // single thread test
    constexpr size_t NUM_ITERATION = 100;
    for (size_t i = 0; i < NUM_ITERATION; ++i)
    {
        SwapThreadSafe(o1, o2);
    }
    constexpr size_t NUM_THREADS = 10;
    {
        auto threadGroup = CreateThreadGroup(NUM_THREADS, SwapThreadSafe<SwapObject<int>>, std::ref(o1), std::ref(o2));
        for (auto &thread : threadGroup)
        {
            thread->join();
        }
    }

    logger.info(std::to_string(o1.data()));
    logger.info(std::to_string(o2.data()));

    {
        DListThreadSafe<int> dlist;
        auto push_back = [&]()
        {
            dlist.push_back(rand());
        };
        auto threadGroup = CreateThreadGroup(NUM_THREADS, push_back);
        for (auto &thread : threadGroup)
        {
            thread->join();
        }
        for (const auto &v : dlist)
        {
            if (v.val.has_value())
            {
                logger.info(std::to_string(v.val.value()));
            }
        }
    }

    // multiple read and rare write case
    {
        MapThreadSafe<int, int> m;
        auto mapAction = [&]()
        {
            if (rand() % 2 == 0)
            {
                logger.info("getvalue");
                if (m.get(1).has_value())
                {
                    logger.info(std::to_string(m.get(1).value()));
                }
                else
                {
                    logger.info("cache miss");
                }
            }
            else
            {
                logger.info("setvalue");
                m.set(1, rand());
            }
        };
        auto threadGroup = CreateThreadGroup(NUM_THREADS, mapAction);
        for (auto &thread : threadGroup)
        {
            thread->join();
        }
    }

    StackThreadSafe<int> stack(logger);
    // same_as concept
    // stack.emplace(1.0f);

    auto pushElement = [&]()
    {
        stack.push(rand());
    };

    auto threadGroup = CreateThreadGroup(10, pushElement);
    for (auto &thread : threadGroup)
    {
        thread->join();
    }

    // test

    return 0;
}