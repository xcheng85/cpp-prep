#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <format>
#include <chrono>
#include <functional>
#include <vector>
#include <list>
#include <forward_list>
#include <utility> // for std::pair
#include <tuple>   // for std::tuple
#include <random>
#include <algorithm> // partition
#include <concepts>
#include <iterator> // ostream_iterator


// 215. Kth Largest Element in an Array

// pure function
// no const due to splice, no ref due to splice
// rvalue reference: hint to the caller, abondon the input
template <typename T>
    requires std::three_way_comparable<T>
std::list<T> quickSort(std::list<T> &&input)
{
    // compiler optimization
    std::list<T> res;
    // recursive end condition
    if (input.size() == 0)
    {
        return res;
    }
    // move one element as a pivot
    res.splice(res.begin(), input, input.begin());
    const auto &pivot = *(res.begin());

    // quickly divide into two parts using stl algorithm partition
    // partition reorder the input
    auto partitionItr = std::partition(input.begin(), input.end(), [&](const auto &t)
                                       { return t < pivot; });

    // move the lower part out using range
    std::list<T> lowerPart;
    lowerPart.splice(lowerPart.begin(), input, input.begin(), partitionItr);

    auto sortedLowerPart{quickSort(std::move(lowerPart))};
    // input only left higher part
    auto sortedHigherPart{quickSort(std::move(input))};

    // merge
    res.splice(res.end(), sortedHigherPart);
    res.splice(res.begin(), sortedLowerPart);
    return res;
}
