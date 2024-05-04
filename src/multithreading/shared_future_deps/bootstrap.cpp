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

#include <random>

// requires boost/filesystem
#include <boost/filesystem.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp> // to_string

using namespace std::chrono;
using namespace core::utility;
using namespace core::system;
using namespace core::container;

// Pipeline with mult-threading
// Saga

// A: assemble vertex buffer and index buffer
// B and C: vertex shader

// A --> B
//   --> C

struct VertexAttribute
{
    float pos[3];
};

struct InputAssembly
{
    std::vector<VertexAttribute> vb;
    std::vector<size_t> ib;

    ~InputAssembly()
    {
        std::cout << "~InputAssembly\n";
    }
};

template <typename T>
T generateFloatInRange(T min, T max)
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution dis(min, max);
    return dis(gen);
}

std::shared_ptr<InputAssembly> generateInputAssembly()
{
    auto res = std::make_shared<InputAssembly>();
    constexpr size_t NUM_VERTICES = 3;
    for (size_t i = 0; i < NUM_VERTICES; ++i)
    {
        VertexAttribute tmp;
        tmp.pos[0] = generateFloatInRange(0.f, 1.f);
        tmp.pos[1] = generateFloatInRange(0.f, 1.f);
        tmp.pos[2] = generateFloatInRange(0.f, 1.f);
        res->vb.emplace_back(tmp);
    }
    res->ib.emplace_back(0);
    res->ib.emplace_back(1);
    res->ib.emplace_back(2);

    //
    std::this_thread::sleep_for(10s);

    return res;
}

int main()
{
    auto &logger = DefaultLogger::Instance();
    logger.setLogLevel(LogLevel::DEBUG);

    std::promise<std::shared_ptr<InputAssembly>> inputAssembleReadyPromise;
    std::shared_future<std::shared_ptr<InputAssembly>> inputAssembleReadyFuture(inputAssembleReadyPromise.get_future());

    auto prepareInputAssemblyTask = [&]()
    {
        auto ptr = generateInputAssembly();
        inputAssembleReadyPromise.set_value(ptr);
    };

    // inputAssembleReadyFuture must be copy to avoid data race
    auto vertexShaderTask = [&, inputAssembleReadyFuture]()
    {
        logger.debug("init vertexShader");
        while (inputAssembleReadyFuture.wait_for(seconds(1)) != future_status::ready)
        {
            logger.debug("vertexShader thread is waiting...");
        }

        const auto inputAssembly = inputAssembleReadyFuture.get();
        logger.debug("run vertexShader");
    };

    // 2 threads to mimic vertex processing
    auto f3 = std::async(std::launch::async, prepareInputAssemblyTask);
    auto f1 = std::async(std::launch::async, vertexShaderTask);
    auto f2 = std::async(std::launch::async, vertexShaderTask);

    return 0;
}