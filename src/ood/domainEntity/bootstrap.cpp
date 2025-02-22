#include <ipv4.h>

using namespace Entity;
int main()
{
    IpAddress ip1{127, 0, 0, 1};
    auto ip2 = std::move(ip1);
    std::cout << ip2;

    IpAddress ip3{127, 0, 0, 1};
    std::cin >> ip3;
    if (!std::cin.fail())
        std::cout << ip3;

    std::cout << (ip2 <= ip3) << std::endl
              << std::flush;

    // for loop
    // copy assigned defined
    // operator <=
    // operator ++

    for(auto addr = ip2; addr <= ip3; addr++) {
        std::cout << addr;
    }

    return 0;
}