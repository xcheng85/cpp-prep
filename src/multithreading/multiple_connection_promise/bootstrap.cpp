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

// requires boost/filesystem
#include <boost/filesystem.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp> // to_string

using namespace std::chrono;
using namespace core::utility;
using namespace core::system;
using namespace core::container;

// 2 client threads: blocking on future-promise pair

// 1 server thread (main thread): forever process request

// data model(entity)
// 1. Connection, promise, uuid
// 2. Request
// 3. Response

using namespace boost::uuids;

using HTTP_RESPONSE = int;

struct Request
{
    // promise is only movable
    std::promise<HTTP_RESPONSE> promise;
    std::string reqId;
    bool hasIncomingData{false};
    bool clientAbort{false};
    bool isDone{false};

    inline Request()
    {
        boost::uuids::random_generator generator;
        uuid id = generator();
        reqId = to_string(id);
    }
};

int main()
{
    auto &logger = DefaultLogger::Instance();
    logger.setLogLevel(LogLevel::DEBUG);

    constexpr size_t NUM_CLIENTS = 10;
    std::vector<Request> reqs;
    for (size_t i{0}; i < NUM_CLIENTS; ++i)
    {
        reqs.emplace_back(Request{});
    }

    // std::future<HTTP_RESPONSE> httpResponseFuture = httpResponsePromise.get_future();

    auto clientWait = [&](Request &req)
    {
        std::future<HTTP_RESPONSE> httpResponseFuture = req.promise.get_future();
        std::this_thread::sleep_for(10s);
        // req.hasIncomingData = true;
        //  trigger promise exception
        req.clientAbort = true;

        try
        {
            const auto httpResponse = httpResponseFuture.get();
            logger.debug(std::format("client recieved response and its status code: {}", static_cast<int>(httpResponse)));
        }
        catch (const std::exception &e)
        {
            ;
        }
    };

    std::vector<std::jthread> clientThreads;

    for (size_t i{0}; i < NUM_CLIENTS; ++i)
    {
        clientThreads.emplace_back(clientWait, std::ref(reqs[i]));
        // non-blocking daemon
        clientThreads.back().detach();
    }

    // main thread handle request
    auto serverHandler = [&]()
    {
        for (auto &req : reqs)
        {
            if (req.isDone)
            {
                continue;
            }

            if (req.clientAbort)
            {
                logger.debug(std::format("client: {} was disconnected", req.reqId));
                req.promise.set_exception(std::make_exception_ptr(std::runtime_error("Client Abort")));
                req.isDone = true;
            }

            if (req.hasIncomingData)
            {
                // ready to response
                req.promise.set_value(200);
                req.isDone = true;
                logger.debug(std::format("server responded to request: {}", req.reqId));
            }
        }
    };

    while (true)
    {
        serverHandler();
        this_thread::sleep_for(1s);
    }

    // // client thread
    // std::cout << boost::filesystem::current_path() << std::endl;

    // //std::cout << s << '\n';

    // //std::cout << boost::lexical_cast<std::string>(id) << '\n';
    return 0;
}