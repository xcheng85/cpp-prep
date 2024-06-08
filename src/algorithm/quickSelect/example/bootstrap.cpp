#include <cmath>
#include <chrono>
#include <random>
#include <format>
#include <memory>
#include <quicksort.h>
#include <quickselect.h>

using namespace std::chrono;
using namespace std;

int main(int argc, char **argv)
{
    if(argc != 2) {
        throw std::runtime_error("Usage: quickSelect-example 7");
    }

    std::list<int> unsorted{
        7, 10, 4, 3, 20, 15
    };
    // auto sorted = quickSort(std::move(unsorted));
    // for(const auto& e : sorted) {
    //     cout << e << "\n";
    // }

    cout << quickSelect(std::move(unsorted), std::stoi(argv[1])) << std::endl;
    return 0;
}