#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>

using namespace std;

// pure function
vector<float> bucketSort(vector<float> &v, const int &numBucket)
{
    // each bucket is a list
    vector<std::list<float>> buckets(numBucket);

    for (const auto &e : v)
    {
        int bucketId = static_cast<int>(e * numBucket);
        buckets[bucketId].emplace_back(e);
    }

    for (auto &bucket : buckets)
    {
        // std::sort requires operator- which list does not support
        // std::sort(bucket.begin(), bucket.end());
        bucket.sort();
        // debugging
        // std::copy(std::begin(bucket), std::end(bucket), std::ostream_iterator<float>(std::cout, " "));
    }

    vector<float> res;
    for (auto &bucket : buckets)
    {
        // move from list to vector
        std::move(std::begin(bucket), std::end(bucket), std::back_inserter(res));
    }
    return res;
}
