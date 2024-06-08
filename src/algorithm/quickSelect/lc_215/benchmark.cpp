#include <benchmark/benchmark.h>
#include <solution.h>

namespace
{
    void findKthLargestTest1(benchmark::State &state)
    {
        QuickSelect::Solution215 s;
        std::vector<int> input{3, 2, 1, 5, 6, 4};
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(s.findKthLargest(input, 2));
        }
    }

    void findKthLargestTest2(benchmark::State &state)
    {
        PQ::Solution215 s;
        std::vector<int> input{3, 2, 1, 5, 6, 4};
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(s.findKthLargest(input, 2));
        }
    }

    // register as a benchmark function
    BENCHMARK(findKthLargestTest1);
    BENCHMARK(findKthLargestTest2);
} // namespace

BENCHMARK_MAIN();