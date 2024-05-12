#include <cmath>
#include <chrono>
#include <kernel.h>
// Thrust: The C++ Parallel Algorithms Library
#include <thrust/host_vector.h>
#include <logger.h>

using namespace std::chrono;
using namespace core::utility;

int main(int argc, char **argv)
{
    auto &logger = DefaultLogger::Instance();
    logger.setLogLevel(LogLevel::DEBUG);

    // x axis
    int numSteps = argc > 1 ? atoi(argv[1]) : 888888888;
    // taylor series
    int numTerms = argc > 2 ? atoi(argv[2]) : 888;
    constexpr int numThreadsInBlock = 128;
    int numThreadBlocks = std::ceil((float)numSteps / (float)numThreadsInBlock);

    float stepSize = M_PI / (numSteps - 1);

    logger.debug("before run_kernel_integrate");
    run_kernel_integrate(numThreadBlocks, numThreadsInBlock, numSteps, numTerms, stepSize);
    logger.debug("after run_kernel_integrate");

    return 0;
}