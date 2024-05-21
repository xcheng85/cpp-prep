#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>
#include <cassert>
#include <iterator>

// random from [1, n]

using namespace std;

// books: Real-World Algorithms: P.463
template <typename T>
vector<T> ReservoirSampling(const vector<T> &src, size_t k)
{
    vector<T> res(k);
    // k items in reservoir
    for (size_t i = 0; i < k; ++i)
    {
        res[i] = src[i];
    }
    // t: number of items that is encountered.
    for (size_t i = k + 1; i < src.size(); ++i)
    {
        auto t = i;

        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(1, t);
        auto u = distrib(gen);

        // probability of replace one of the items already in the reservoir:
        // m / t
        if (u <= k)
        {
            res[u - 1] = src[i];
        }
    }
    return res;
}

int main(int argc, char **argv)
{
    assert(argc == 3);

    const auto streamSize = stoi(argv[1]);
    const auto reservoirSize = stoi(argv[2]);

    assert(streamSize);
    assert(reservoirSize);

    vector<int> srcStream(streamSize);
    std::iota(srcStream.begin(), srcStream.end(), 0);

    auto samplingResult = ReservoirSampling(srcStream, reservoirSize);
    std::copy(samplingResult.begin(), samplingResult.end(),
              ostream_iterator<int>(cout, " "));
    return 0;
}