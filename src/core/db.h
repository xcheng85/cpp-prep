#pragma once

#include <string>
#include <thread>
#include <functional>
#include <string_view>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <logger.h>

namespace core::db
{
    using namespace std::chrono;
    using namespace core::utility;

    // mimic over tcp connection
    class DBClient
    {
    public:
        DBClient(std::string_view connectionString) : _connectionString{connectionString}
        {
        }

    private:
        const std::string _connectionString;
    };

    class DBInstance
    {
    public:
        static DBInstance &instance();

        std::unique_ptr<DBClient> connect(std::string_view connectionString);

    private:
        DBInstance(ILogger &logger);
        DBInstance(DBInstance &) = delete;
        DBInstance &operator=(const DBInstance &) = delete;

        ILogger &_logger;
    };
}