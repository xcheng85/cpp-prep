#include <solution.h>

using namespace std;

int main(int argc, char **argv)
{
    QuickSelect::Solution215 s;
    std::vector<int> input{3, 2, 1, 5, 6, 4};
    // cout << s.findKthLargest(input, 2) << std::endl;

    // as increasing order
    //nth_element(input.begin(), input.begin() + 1, input.end(), std::less{});

    // 2nd largest
    std::nth_element(input.begin(), input.begin() + 1, input.end(), std::greater{});
    cout << input[1] << std::endl;
    return 0;
}