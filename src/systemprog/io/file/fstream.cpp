#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ifstream fs("dummy.txt"s);
    if (!fs.good())
    {
        cerr << "open dummy.txt has error" << endl;
        return 1;
    }
    // ifstream has a getline member
    // here is a globle getline, more generic
    string sLine;
    while (getline(fs, sLine, '|'))
    {
        // remove space
        // after c++14 erase_if
        // before remove then erase idiom
        // in-place
        erase_if(sLine, [](auto &c)
                 { return c == ' '; });
        cout << sLine << "\n";
    }
    return 0;
}