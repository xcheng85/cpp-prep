#include <vector>
#include <stack>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <format>

// histogram = {6, 2, 5, 4, 5, 1, 6}

// next smaller index at right

// {1, 5, 3, 5, 5, -1, -1}

// previous smaller index at left (offset)
// {-1, -1, 1, 1, 3, -1, 5}

// 6: -1, 1   (1-0)*6 = 6
// 2: -1, 5   (5 - 1) * 2 = 8
// 5: 1, 3     (3 - 2) * 5 = 5
// 4: 1, 5  ((5 - 3) + (3 - 2)) * 4 = 12
// 5: 3, 5   ((5 - 4) + (4 - 3)) * 5 = 10
// 1: -1, -1,
// 6: -1, 5  (6-5) * 1 = 6

using namespace std;

class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        vector<int> prevSmallerIndex = previousSmallerIndex(heights);
        // copy(begin(prevSmallerIndex), end(prevSmallerIndex), ostream_iterator<int>(cout, " "));
        // cout << endl;

        vector<int> nextSmallerIndex = nextSmallerindex(heights);
        // copy(begin(nextSmallerIndex), end(nextSmallerIndex), ostream_iterator<int>(cout, " "));
        // cout << endl;

        assert(prevSmallerIndex.size() == nextSmallerIndex.size());
        int maxArea = 0;
        for (size_t i = 0; i < prevSmallerIndex.size(); ++i)
        {
            // start with self
            int currArea = heights[i];
            const auto leftIndex = prevSmallerIndex[i];
            const auto rightIndex = nextSmallerIndex[i];
            // extend left
            if (leftIndex != -1)
            {
                // don't forget -1
                const auto leftArea = heights[i] * (i - (leftIndex+1));
                currArea += leftArea;
            }
            else
            {
                // -1, everyting include on the left
                const auto leftArea = heights[i] * i;
                currArea += heights[i] * i;
            }
            // extend right
            if (rightIndex != -1)
            {
                const auto rightArea = heights[i] * (rightIndex - 1 - i);
                currArea += rightArea;
            }
            else
            {
                // -1, everyting include on the RIGHT
                const auto rightArea = heights[i] * (heights.size() - 1 - i);
                currArea += rightArea;
            }
            maxArea = max({currArea, maxArea});
        }
        return maxArea;
    }

private:
    vector<int> previousSmallerIndex(vector<int> &heights)
    {
        vector<int> res(heights.size());
        stack<int> indexS;
        for (size_t i = 0; i < heights.size(); ++i)
        {
            // pop all the bigger one
            while (!indexS.empty() && heights[indexS.top()] >= heights[i])
            {
                indexS.pop();
            }
            res[i] = indexS.empty() ? -1 : indexS.top();
            indexS.emplace(i);
        }
        return res;
    }

    vector<int> nextSmallerindex(vector<int> &heights)
    {
        vector<int> res(heights.size());
        stack<int> indexS;
        for (int i = heights.size() - 1; i >= 0; --i)
        {
            // pop all the bigger one
            while (!indexS.empty() && heights[indexS.top()] >= heights[i])
            {
                indexS.pop();
            }
            res[i] = indexS.empty() ? -1 : indexS.top();
            indexS.emplace(i);
        }
        return res;
    }
};

int main()
{
    Solution s;

    vector<int> heights{2, 4};

    cout << s.largestRectangleArea(heights);
    return 0;
}