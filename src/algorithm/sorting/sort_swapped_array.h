// Sort an almost sorted array where only two elements are swapped

// two pointers
// left-right: 60, 40
// right->left:

// Input:  arr[] = {10, 20, 60, 40, 50, 30}
// // 30 and 60 are swapped
// Output: arr[] = {10, 20, 30, 40, 50, 60}

// Input:  arr[] = {10, 20, 40, 30, 50, 60}

#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<int> SortAlmostSortedArray(vector<int> &array)
    {
        int n = array.size();
        for (int i = n - 1; i > 0; i--)
        {
            if (array[i] < array[i - 1])
            {
                // array[i]: one candidate to swap

                // to find the other candidate must larger than

                // 40, 30
                // find [0, i-1]

                // find the leftmost in-order position,
                // 20, 60 j will stop at 20, and we need j+1
                int j = i - 1;
                while (j >= 0 && array[i] < array[j])
                    j--;
                // 
                j++;
                swap(j, i);
                break;
            }
        }
    }
};