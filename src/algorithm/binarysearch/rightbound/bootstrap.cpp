#include <vector>
#include <iostream>

using namespace std;

// [1, 2, 2, 2, 3]
// l = 0, r = 3
// mid = 2, update l = 3, [3, 4]

// mid = 3, update l = 4, [4, 4]

// mid = 4, update r = 3, [4, 3], done, right is the answer

template <typename T>
    requires requires(T t) {
        t <=> t;
    }
int rightBoundIndex(const vector<T> &inputs, T target)
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
            // r = mid - 1; //left bound
            l = mid + 1; //right bound
         }
    }
    // left bound
    // return inputs[l] == target ? l : -1;
    // right bound
    return inputs[r] == target ? r : -1;
}

int main()
{
    cout << rightBoundIndex<int>({1, 2, 2, 2, 3}, 2);
    return 0;
}