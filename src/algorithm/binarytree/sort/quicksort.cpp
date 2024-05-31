#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <iostream>

using namespace std;

vector<int> quicksort(vector<int> &v)
{
    copy(std::begin(v), std::end(v), ostream_iterator<int>(cout, ","));
    cout << endl;

    // stop condition for recursion
    if (v.size() == 0)
    {
        return v;
    }
    vector<int> res;
    // 1. select pivot
    auto pivot = v.back();
    v.pop_back();
    cout << "pivot: " << pivot << endl;

    // [)
    // select first element as pivot
    // without proper size init

    // std::move(v.begin(), v.begin() + 1, std::back_inserter(res));
    // // moved element in unstable state
    // v.erase(v.begin(), v.begin() + 1);

    // quickly divide into two parts using stl algorithm partition
    // partition reorder the input
    auto partitionItr = std::partition(v.begin(), v.end(), [&](const auto &t)
                                       { return t < pivot; });

    vector<int> lessPart, greaterPart;
    std::move(partitionItr, v.end(), std::back_inserter(greaterPart));
    v.erase(partitionItr, v.end());
    std::move(v.begin(), partitionItr, std::back_inserter(lessPart));
    v.erase(v.begin(), partitionItr);
    vector<int> sortedLessPart = quicksort(lessPart);
    vector<int> sortedGreaterPart = quicksort(greaterPart);

    // std::move(sortedLessPart.begin(), sortedLessPart.end(), std::front_inserter(res));
    std::move(sortedLessPart.begin(), sortedLessPart.end(), std::back_inserter(res));
    res.emplace_back(pivot);
    std::move(sortedGreaterPart.begin(), sortedGreaterPart.end(), std::back_inserter(res));

    return res;
}

int main()
{
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 100);

    vector<int> unsorted;
    for (int i = 0; i < 100; ++i)
    {
        unsorted.emplace_back(distrib(gen));
    }

    vector<int> sorted = quicksort(unsorted);
    copy(std::begin(sorted), std::end(sorted), ostream_iterator<int>(cout, ","));
    return 0;
}