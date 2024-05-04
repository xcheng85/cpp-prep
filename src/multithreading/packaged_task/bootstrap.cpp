#include <string>
#include <sstream>
#include <format>
#include <chrono>
#include <thread_factory.h>
#include <logger.h>
#include <queuethreadsafe.h>
#include <future> //packaged_task<>
#include <functional>
#include <vector>
#include <utility> // for std::pair
#include <tuple>   // for std::tuple

using namespace std::chrono;
using namespace core::utility;
using namespace core::system;
using namespace core::container;
// two threads
// main thread: create tasks using packaged_task<>

// Alternatively, you can bind the arguments directly before you construct the task,
//  in which case the task itself now has a signature that takes no arguments:
using StreamingDataFn = std::tuple<int, int, int>(void);

// volume dimension is [256, 256, 256]
// 3d tile size: [64, 64, 64]
// tile id: [0, 0, 0] - [3, 3, 3]
inline std::tuple<int, int, int> load3DVoxelTiles(const std::tuple<int, int, int> &tileId)
{
    const int x = get<0>(tileId), y = get<1>(tileId), z = get<2>(tileId);
    DefaultLogger::Instance().debug(std::format("Start Loading 3D Tile at: [{},{},{}]", x, y, z));
    std::this_thread::sleep_for(10s);
    DefaultLogger::Instance().debug(std::format("End Loading 3D Tile at: [{},{},{}]", x, y, z));
    return tileId;
}

// mimic gpu-based ray caster to detect missing textures from current view angle.
inline std::vector<std::packaged_task<StreamingDataFn>> rayCastingPrepass()
{
    std::vector<std::packaged_task<StreamingDataFn>> res;
    const auto x = rand() % 4;
    const auto y = rand() % 4;
    const auto z = rand() % 4;
    // a lot implicit type deduction here
    res.emplace_back(std::bind(&load3DVoxelTiles, std::make_tuple(x, y, z)));
    return res;
    // std::packaged_task<StreamingDataFn> asyncLoadingTextureTask(std::bind(&loadTextures, "texturePath1"));
}

inline void rendering()
{
    // DefaultLogger::Instance().debug("Start rendering");
    // DefaultLogger::Instance().debug("End rendering");
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

    // container for the future "return type is void"
    // future is not CopyConstructable
    // future is MoveConstructible
    std::vector<std::future<std::tuple<int, int, int>>> asyncReadTilesTaskFutures;

    // main thread create tasks
    // and get the future handle for retrieve result later
    while (true)
    {
        // simulate on-demand missing tile streaming
        // cannot be const due to get_future() is not const
        auto readTilesTasks = rayCastingPrepass();

        for (auto &t : readTilesTasks)
        {
            // auto deductable
            std::future res = t.get_future();
            // cache the future for retrieve in the future action.
            asyncReadTilesTaskFutures.emplace_back(std::move(res));
            taskQueue.push(std::move(t));
        }

        const auto update = [&]()
        {
            // 50fps = each frame 1/50 = 0.02s;
            // 0.02s = 20ms,
            // iterate to check if the future is ready
            // cached the ready future's iterator for erase in a seprate pass.
            using vecFut = std::vector<std::future<std::tuple<int, int, int>>>;
            using vecFutItr = vecFut::iterator;

            std::vector<vecFutItr> eraseVec;

            for (auto itr = asyncReadTilesTaskFutures.begin(); itr != asyncReadTilesTaskFutures.end(); ++itr)
            {
                auto& f = *itr;
                // considering fps
                std::future_status status = f.wait_for(1ms);
                if (status != std::future_status::ready)
                {
                    continue;
                }
                else
                {
                    const auto completedStreamTileId = f.get();
                    const int x = get<0>(completedStreamTileId), y = get<1>(completedStreamTileId), z = get<2>(completedStreamTileId);
                    DefaultLogger::Instance().debug(std::format("Updating 3D Tile from RAM to GPU at: [{},{},{}]", x, y, z));
                    // future is done
                    eraseVec.emplace_back(itr);
                }
            }

            for( auto itr = eraseVec.rbegin(); itr != eraseVec.rend(); ++itr) {
                asyncReadTilesTaskFutures.erase(*itr);
            }
        };

        update();

        rendering();
    }

    return 0;
}