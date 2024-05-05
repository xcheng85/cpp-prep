#include <string>
#include <sstream>
#include <iostream>
#include <format>
#include <chrono>
#include <thread_factory.h>
#include <logger.h>
#include <queuethreadsafe.h>
#include <future> //packaged_task<>
#include <functional>
#include <vector>
#include <list>
#include <utility> // for std::pair
#include <tuple>   // for std::tuple
#include <random>
#include <algorithm> // partition
#include <concepts>
#include <iterator> // ostream_iterator

using namespace std::chrono;
using namespace core::utility;

// signature of fp

// why list ?
// the list.splice(move) between two lists can avoid copying

template <typename T>
    requires three_way_comparable<T>
std::list<T> quickSort(std::list<T> input) // no const due to splice, no ref due to splice
{
    std::list<T> res;

    if (input.size() == 0)
    {
        return res;
    }

    // dst itr,
    // source list
    // src itr of source list
    // a move for only one element pointed by src itr

    // only transfer the pivot
    // must guard against input.
    res.splice(res.begin(), input, input.begin());

    // select the first element as pivot
    const auto &pivot = *(res.begin());
    // quickly divide into two parts using stl algorithm partition

    auto partitionItr = std::partition(input.begin(), input.end(), [&](const auto &t)
                                       { return t < pivot; });

    // move the lower part out using range
    std::list<T> lowerPart;
    lowerPart.splice(lowerPart.begin(), input, input.begin(), partitionItr);

    // recursive, divide and conquer
    // avoid copy and also marks the lowerPart should not be used after next line.
    auto sortedLowerPart{quickSort(std::move(lowerPart))};
    auto sortedHigherPart{quickSort(std::move(input))};

    // merge two sorted part with pivot
    // the res so far only has pivot one value
    // move after the pivot
    res.splice(res.end(), sortedHigherPart);
    // move before the pivot
    res.splice(res.begin(), sortedLowerPart);
    return res;
}

int main()
{
    auto &logger = DefaultLogger::Instance();
    logger.setLogLevel(LogLevel::DEBUG);

    auto sorted{quickSort<int>({1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92})};
    std::copy(std::begin(sorted), std::end(sorted), std::ostream_iterator<int>(std::cout, " "));

    return 0;
}