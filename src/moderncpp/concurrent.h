#pragma once

#include <future>
#include <mutex>
#include <thread>
#include <functional>

#include <shared.h>
#include <vector>

namespace Concurrent
{
    class ClickCounter
    {
    public:
        ClickCounter(std::mutex &mux)
            : _mux{mux}
        {
        }

        constexpr static int dt{1};
        // pass in from controller thread
        void operator()(int &gCt)
        {
            //std::lock_guard lg{_mux};
            gCt += dt;
        }

    private:
        std::mutex &_mux;
    };

    void testFunctorDataContention(size_t numThreads)
    {
        std::mutex mux;
        int gCt = 0;

        std::vector<std::thread> threadGrp;
        for (int i = 0; i < numThreads; i++)
        {
            threadGrp.emplace_back(std::thread(ClickCounter(mux), std::ref(gCt)));
        }
        for (int i = 0; i < numThreads; i++)
        {
            threadGrp[i].join();
        }
        LOG_I(gCt);
    }
}
