#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

// not comparion based, only applied to int with small range
vector<int> countSort(vector<int> &v)
{
    // step1: get the maxvalue
    auto itr = std::max_element(v.begin(), v.end());

    // step2: count array
    vector<int> prefixCountVec(*itr + 1, 0);

    // step3: fill in the count array
    for (const auto &e : v)
    {
        ++prefixCountVec[e];
    }

    // step4: prefix sum
    for (size_t i = 1; i < prefixCountVec.size(); ++i)
    {
       prefixCountVec[i] += prefixCountVec[i-1];
    }

    std::copy(std::begin(prefixCountVec), std::end(prefixCountVec), std::ostream_iterator<int>(std::cout, " "));

    // step4: reverse fill
    vector<int> res(v.size());
    for (auto itr = v.rbegin(); itr != v.rend(); ++itr)
    {
        auto writeIdx = prefixCountVec[*itr] - 1; // count is 7, means the 7th,
        res[writeIdx] = *itr;
        cout << "writeIdx: " << writeIdx << " value: " << *itr << std::endl;
        --prefixCountVec[*itr];
    }
    return res;
}