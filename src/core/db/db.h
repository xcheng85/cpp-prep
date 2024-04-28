#pragma once

#include <string>
#include <thread>
#include <functional>
#include <string_view>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex> //once_flag
#include <logger.h>

namespace core::db
{
    using namespace std::chrono;
    using namespace core::utility;

    // mimic over tcp connection
    // delayed initialization pattern

    class DBClient
    {
    public:
        DBClient(std::string_view connectionString) : _connectionString{connectionString}
        {
        }

        void xadd()
        {
            std::call_once(_connectionInitFlag, &DBClient::openDBConnection, this);
            DefaultLogger::Instance().info("xadd");
        }

        void xdel()
        {
            std::call_once(_connectionInitFlag, &DBClient::openDBConnection, this);
            DefaultLogger::Instance().info("xdel");
        }

    private:
        void openDBConnection()
        {
            // use _connectionString
            DefaultLogger::Instance().info("openDBConnection");
        }
        const std::string _connectionString;
        std::once_flag _connectionInitFlag;
    };

    class DBInstance
    {
    public:
        static DBInstance &instance();

        std::unique_ptr<DBClient> createClient(std::string_view connectionString);

    private:
        DBInstance(ILogger &logger);
        DBInstance(DBInstance &) = delete;
        DBInstance &operator=(const DBInstance &) = delete;

        ILogger &_logger;
    };
}