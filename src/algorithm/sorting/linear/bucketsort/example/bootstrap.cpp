#include <cmath>
#include <chrono>
#include <random>
#include <format>
#include <memory>
#include <iostream>
#include <iterator>
#include <bucketsort.h>

using namespace std::chrono;
using namespace std;

int main(int argc, char **argv)
{
    vector<float> input{0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};

    vector<float> output{bucketSort(input, 10)};
    
    std::copy(std::begin(output), std::end(output), std::ostream_iterator<float>(std::cout, " "));

    return 0;
}