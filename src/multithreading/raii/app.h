#pragma once

#include <thread>
#include <future>
#include <mutex>
#include <deque>
#include <tuple>
#include <utility>
#include <vector>
#include <iostream>
#include <format>
#include <algorithm>
#include <vector>
#include <thread>

#include "jthread.h"

#include <db.h>
#include <logger.h>

using namespace core::db;
using namespace core::utility;

class IApp
{
public:
    virtual ~IApp()
    {
    }

    void run()
    {
        runImp();
    }

protected:
    virtual void init() = 0;
    virtual void tearDown() = 0;

private:
    virtual void runImp() = 0;
};

// strategy pattern
// ioc
class App : public IApp
{
public:
    App(DBInstance &db, ILogger &logger, int numThreads = 1)
        : _db{db},
          _numThreads{numThreads},
          _logger{logger}
    {
    }

    void init() override
    {
        _logger.debug("init");
        for (int i = 0; i < _numThreads; ++i)
        {
            std::thread t{
                &DBInstance::connect,
                &_db,
                format("connectionString_{}", i)};
            _threadPool.emplace_back(core::system::jthread(move(t)));
        }
    }

    void runImp() override
    {
        _logger.debug("runImp");
        for (auto &t : _threadPool)
        {
            t.join();
        }
    }

    void tearDown() override
    {
        _logger.debug("tearDown");
    }

private:
    int _numThreads{0};
    std::vector<core::system::jthread> _threadPool;
    ILogger &_logger;
    DBInstance &_db;
};