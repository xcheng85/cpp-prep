#include <iostream>
#include <iterator>
#include <solution.h>

using namespace std;

int main()
{
    Solution s;
    vector<string> deadends{"0201"s, "0101"s, "0102"s, "1212"s, "2002"s};
    auto steps = s.openLock(deadends, "0202"s);
    cout << steps << endl;
}