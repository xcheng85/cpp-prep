#include <vector>
#include <iostream>

using namespace std;

// [1, 2, 2, 2, 3]
// l = 0, r = 3
// mid = 2, update r = 1, [0, 1]

// mid = 0, update l = 1, [1, 1]

// mid = 1, update r = 0, [1, 0], done, left is the answer

template <typename T>
    requires requires(T t) {
        t <=> t;
    }
int leftBoundIndex(const vector<T> &inputs, T target)
{
    // framework of binary search
    int l{0}, r{inputs.size() - 1};
    // <=
    while (l <= r)
    {
        auto mid = l + (r - l) / 2;
        if (inputs[mid] < target)
        {
            l = mid + 1;
        }
        else if (inputs[mid] > target)
        {
            r = mid - 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return inputs[l] == target ? l : -1;
}

int main()
{
    cout << leftBoundIndex<int>({1, 2, 2, 2, 3}, 2);
    return 0;
}