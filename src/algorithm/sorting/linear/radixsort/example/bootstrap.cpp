#include <cmath>
#include <chrono>
#include <random>
#include <format>
#include <memory>
#include <iostream>
#include <radixsort.h>
#include <iterator>

using namespace std::chrono;
using namespace std;

int main(int argc, char **argv)
{
    vector<int> input{170, 45, 75, 90, 802, 24, 2, 66};

    vector<int> output{radixSort(input)};
    
    std::copy(std::begin(output), std::end(output), std::ostream_iterator<int>(std::cout, " "));

    return 0;
}