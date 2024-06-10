#include <sstream>
#include <string>
using namespace std;

class Solution
{
public:
    string defangIPaddr(string address)
    {
        std::istringstream ss(address);
        std::string tokens[4];
        uint8_t i = 0;
        while (std::getline(ss, tokens[i++], '.'))
        {
        }
        std::string res;
        res.reserve(tokens[0].size() + tokens[1].size() + tokens[2].size() +
                    tokens[3].size());
        res += tokens[0];
        res += "[.]";
        res += tokens[1];
        res += "[.]";
        res += tokens[2];
        res += "[.]";
        res += tokens[3];
        return res;
    }
};