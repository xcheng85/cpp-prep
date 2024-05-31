#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <iostream>

using namespace std;

vector<int> mergesort(vector<int>::iterator s, vector<int>::iterator e)
{
    // 1. end condition
    if (distance(s, e) == 0)
    {
        return {*s};
    }

    auto mid = s + distance(s, e) / 2;
    // cout << "mid: " << *mid << endl;
    vector<int> left = mergesort(s, mid);
    // copy(std::begin(left), std::end(left), ostream_iterator<int>(cout, ","));
    // cout << endl;
    vector<int> right = mergesort(mid + 1, e);
    // copy(std::begin(right), std::end(right), ostream_iterator<int>(cout, ","));
    // cout << endl;

    // merge step
    vector<int> result(left.size() + right.size());
    size_t wPos = 0;
    size_t currL = 0, currR = 0;
    while (wPos < result.size())
    {
        if (currL < left.size() && currR < right.size())
        {
            if (left[currL] < right[currR])
            {
                result[wPos++] = left[currL];
                ++currL;
            }
            else
            {
                result[wPos++] = right[currR];
                ++currR;
            }
        }
        else if (currL < left.size())
        {
            result[wPos++] = left[currL];
            ++currL;
        }
        else if (currR < right.size())
        {
            result[wPos++] = right[currR];
            ++currR;
        }
    }

    return result;
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
    // --on the end iterator
    vector<int> sorted = mergesort(unsorted.begin(), --unsorted.end());
    copy(std::begin(sorted), std::end(sorted), ostream_iterator<int>(cout, ","));
    return 0;
}