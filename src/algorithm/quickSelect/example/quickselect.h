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


template <typename T>
    requires std::three_way_comparable<T>
int quickSelect(std::list<T> &&input, int k)
{
    // k is 1-based, not >=
    if(k > input.size()){
        return -1;
    }
    // std::list<T> pivot;
    // // move 1 element
    // pivot.splice(pivot.begin(), input, input.begin());
    // move range
    // pivot.splice(pivot.begin(), input, input.begin(), input.end());
    const auto pivot = input.front();
    input.pop_front();

    const auto itr = std::partition(input.begin(), input.end(), [&](const auto& i){
        return i < pivot;
    });

    std::list<T> leftPart, rightPart;
    // range move: [begin, itr]
    leftPart.splice(leftPart.begin(), input, input.begin(), itr);
    rightPart = std::move(input);

    // for(const auto& i : leftPart) {
    //     std::cout << " " << i;
    // }
    // std::cout << "\n";

    // for(const auto& i : rightPart) {
    //     std::cout << " " << i;
    // }
    // std::cout << "\n";

    auto leftSize = leftPart.size();
    if(leftSize == k - 1){
        return pivot;
    } else if(leftSize < k - 1) {
        // -1 for the pivot
        return quickSelect(std::move(rightPart), k - leftSize - 1);
    } else {
        return quickSelect(std::move(leftPart), k);
    }
}
