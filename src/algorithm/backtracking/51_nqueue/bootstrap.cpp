#include <iostream>
#include <iterator>
#include <solution.h>

using namespace std;

int main() {
    Solution s;

    const auto allGoodResults = s.solveNQueens(8);

    for(const auto& r : allGoodResults) {
        std::copy(begin(r), end(r), ostream_iterator<std::string>(cout, " "));
        std::cout << endl;
    }
}