#include <chrono>
#include <sstream>
#include "app.h"
#include <logger.h>
#include <unordered_set>
#include <thread_factory.h>

using namespace core::utility;
using namespace core::system;

void foo()
{
    this_thread::sleep_for(10s);
}

void foo2(std::chrono::seconds s)
{
    this_thread::sleep_for(s);
}

int main()
{
    // auto logger is wrong
    auto &logger = DefaultLogger::Instance();

    unordered_set<thread::id> threadSet;

    auto lamda = [&](std::chrono::seconds s)
    {
        this_thread::sleep_for(s);
        threadSet.insert(this_thread::get_id());
    };
    auto thread = CreateThread(lamda, 3s);
    thread->join();

    for (const auto &k : threadSet)
    {
        std::ostringstream os;
        os << k;
        logger.info(os.str());
    }

    DBInstance &db = DBInstance::instance();
    App app{db, logger, 10};
    app.init();
    app.run();
}