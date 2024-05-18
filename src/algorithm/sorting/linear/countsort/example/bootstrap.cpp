#include <cmath>
#include <chrono>
#include <random>
#include <format>
#include <memory>
#include <iostream>
#include <countsort.h>
#include <iterator>

using namespace std::chrono;
using namespace std;

int main(int argc, char **argv)
{
    vector<int> input{2, 5, 3, 0, 2, 3, 0, 3};

    vector<int> output{countSort(input)};
    
    std::copy(std::begin(output), std::end(output), std::ostream_iterator<int>(std::cout, " "));

    return 0;
}