#include <string>
#include <sstream>
#include <format>
#include <chrono>
#include <thread_factory.h>
#include <logger.h>
#include <queuethreadsafe.h>
#include <future> //packaged_task<>
#include <functional>

using namespace std::chrono;
using namespace core::utility;
using namespace core::system;
using namespace core::container;
// two threads
// main thread: create tasks using packaged_task<>
//

// Alternatively, you can bind the arguments directly before you construct the task,
//  in which case the task itself now has a signature that takes no arguments:
using StreamingDataFn = void(void);

inline void loadTextures(const std::string &path)
{
    DefaultLogger::Instance().debug(std::format("Start Loading Textures: {}", path));
    std::this_thread::sleep_for(10s);
    DefaultLogger::Instance().debug(std::format("End Loading Textures: {}", path));
    return;
}

int main()
{
    auto &logger = DefaultLogger::Instance();
    logger.setLogLevel(LogLevel::DEBUG);

    QueueThreadSafe<std::packaged_task<StreamingDataFn>> taskQueue;
    const auto handlingStreamingData = [&]()
    {
        while (true)
        {
            std::packaged_task<StreamingDataFn> task;
            taskQueue.bpop(task);

            // when I create the task, I need to bind the argument. such as: texture path, model path, etc.
            task();

            std::this_thread::sleep_for(2s);
        }
    };

    // launch worker thread in a detached mode or using asyn task itself
    auto f = std::async(std::launch::async, handlingStreamingData);

    // main thread create tasks
    // and get the future handle for retrieve result later
    while (true)
    {
        std::packaged_task<StreamingDataFn> asyncLoadingTextureTask(std::bind(&loadTextures, "texturePath1"));
        // auto deductable
        std::future res = asyncLoadingTextureTask.get_future();
        taskQueue.push(std::move(asyncLoadingTextureTask));
        std::this_thread::sleep_for(15s);
    }

    return 0;
}