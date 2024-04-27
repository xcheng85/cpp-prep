#include <stackthreadsafe.h>
#include <thread_factory.h>
#include <random>
#include <logger.h>

using namespace core::container;
using namespace core::system;
using namespace core::utility;

int main()
{
    auto &logger = DefaultLogger::Instance();
    StackThreadSafe<int> stack(logger);
    // same_as concept
    // stack.emplace(1.0f);
    srand(time(0));
    auto pushElement = [&]()
    {
        stack.push(rand());
    };

    auto threadGroup = CreateThreadGroup(10, pushElement);
    for (auto &thread : threadGroup)
    {
        thread->join();
    }

    return 0;
}