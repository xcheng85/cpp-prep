#include <string>
#include <sstream>
#include <format>
#include <chrono>
#include <thread_factory.h>
#include <logger.h>
#include <queuethreadsafe.h>

using namespace std::chrono;
using namespace core::utility;
using namespace core::system;
using namespace core::container;

int main(int argc, char **argv)
{
    auto &logger = DefaultLogger::Instance();
    logger.setLogLevel(LogLevel::DEBUG);
    // mimic redis/kafka stream
    QueueThreadSafe<std::string> stream;

    constexpr size_t NUM_CONSUMERS = 3;
    constexpr size_t NUM_PRODUCERS = 2;
    constexpr size_t NUM_STREAMTASK = 1;

    // use lamda to wrap around stream to add audit/observability
    const auto XGROUPCREATECONSUMER = [&]()
    {
        // generate consumerId based on the system clock
        std::ostringstream os;
        os << system_clock::now();
        const auto consumerId = os.str();
        logger.debug(consumerId);

        std::string streamTaskId;
        stream.bpop(streamTaskId);
        logger.debug(std::format("{} assigned stream task: {}", consumerId, streamTaskId));
    };

    const auto XADD = [&]()
    {
        auto numStreamTasksToAdd = NUM_STREAMTASK;
        while (numStreamTasksToAdd-- > 0)
        {
            std::this_thread::sleep_for(seconds(rand() % 10));
            stream.push(format("streamTask_{}", rand() % 10));
        }
    };

    auto threadGroup = CreateThreadGroup(NUM_CONSUMERS, XGROUPCREATECONSUMER);
    auto xaddThreadGroup = CreateThreadGroup(NUM_PRODUCERS, XADD);
    for (auto &thread : xaddThreadGroup)
    {
        thread->join();
    }
    for (auto &thread : threadGroup)
    {
        thread->join();
    }
    return 0;
}