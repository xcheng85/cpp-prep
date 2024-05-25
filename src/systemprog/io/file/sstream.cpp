#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ifstream fs("dummy2.txt"s);
    ofstream os("dummy3.txt"s);
    if (!fs.good() || !os.good())
    {
        cerr << "open dummy2.txt has error" << endl;
        return 1;
    }
    // ifstream has a getline member
    // here is a globle getline, more generic
    string sLine;
    while (getline(fs, sLine))
    {
        // automatically skipped the whitespace
        stringstream ss(sLine);
        string first, last, gender;
        ss >> first >> last >> gender;
        cout << first << "," << last << "," << gender << endl;
        os << gender << " " << last << " " << first << "\n";
    }
    return 0;
}