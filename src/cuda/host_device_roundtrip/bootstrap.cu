#include <cmath>
#include <chrono>
#include <random>
#include <format>
// Thrust: The C++ Parallel Algorithms Library
#include <thrust/host_vector.h>
#include <logger.h>


using namespace std::chrono;
using namespace core::utility;
extern float run_kernel_reduce_v1(thrust::host_vector<float> &);
int main(int argc, char **argv)
{
    auto &logger = DefaultLogger::Instance();
    logger.setLogLevel(LogLevel::DEBUG);

    int N = (argc > 1) ? atoi(argv[1]) : 1 << 16;

    thrust::host_vector<float> vHost(N);
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(1.0, 2.0);
    for (int i{0}; i < N; ++i)
    {
        vHost[i] = dis(gen);
    }

    logger.debug("before run_kernel_integrate");
    auto res = run_kernel_reduce_v1(vHost);
    logger.debug(std::format("after run_kernel_integrate, res: {}", res));
    return 0;
}