#include <logger.h>
#include <thread_factory.h>
#include <thread>
#include <db.h>

using namespace core::system;
using namespace core::utility;
using namespace core::db;
int main(int argc, char **argv)
{
    // one db client
    DBInstance &db = DBInstance::instance();
    auto dbClient = db.createClient("connectionstring");

    // 10 threads call xadd, and assert only 1 connection init occurs
    constexpr size_t NUM_THREADS = 10;
    {
        auto threadGroup = CreateThreadGroup(NUM_THREADS, &DBClient::xadd, dbClient.get());
        for (auto &thread : threadGroup)
        {
            thread->join();
        }
    }

    return 0;
}