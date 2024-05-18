#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

vector<int> countSort(vector<int> &v, int currBit);

// pure function
vector<int> radixSort(vector<int> &v)
{
    // step1, numberofDigets
    auto itr = std::max_element(v.begin(), v.end());
    auto maxEl = *itr;

    int bits{0};
    // fp each step
    vector<int> res = v;
    while (maxEl > 0)
    {
        res = countSort(res, bits++);
        maxEl = maxEl >> 1;
    }
    return res;
}

// not comparion based, only applied to int with small range
vector<int> countSort(vector<int> &v, int currBit)
{
    // // step1: get the maxvalue
    // auto itr = std::max_element(v.begin(), v.end());

    // // step2: count array
    // vector<int> prefixCountVec(*itr + 1, 0);

    // skipped step1 and step2, due to worst case [0, 9]
    // no need to use dynamic size array: vector
    vector<int> prefixCountVec(10, 0);

    // step3: fill in the count array
    for (const auto &e : v)
    {
        // least digit
        ++prefixCountVec[(e >> currBit) %10];
    }

    // step4: prefix sum
    for (size_t i = 1; i < 10; ++i)
    {
        prefixCountVec[i] += prefixCountVec[i - 1];
    }

    //std::copy(std::begin(prefixCountVec), std::end(prefixCountVec), std::ostream_iterator<int>(std::cout, " "));

    // step4: reverse fill
    vector<int> res(v.size());
    for (auto itr = v.rbegin(); itr != v.rend(); ++itr)
    {
        auto digit = (*itr >> currBit) % 10;
        auto writeIdx = prefixCountVec[digit] - 1; // count is 7, means the 7th,
        res[writeIdx] = *itr;
        --prefixCountVec[digit];
    }
    return res;
}