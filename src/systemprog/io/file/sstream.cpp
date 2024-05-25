#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ifstream fs("dummy2.txt"s);
    // ofstream only has seekp for write
    //ofstream os("dummy3.txt"s);
    // trunc or app
    // rw + truncate
    fstream ios("dummy3.txt"s, ios_base::trunc | std::fstream::in | std::fstream::out );
    if (!fs.good() || !ios.good())
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
        ios << gender << " " << last << " " << first << "\n";
    }
    // seekg: for read
    //ios.seekg(0) // same
    ios.seekg(0, ios_base::beg);
    while (getline(fs, sLine))
    {
        cout << sLine << endl;
    }
    return 0;
}