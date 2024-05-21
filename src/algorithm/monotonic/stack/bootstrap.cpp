#include <vector>
#include <stack>
#include <iostream>
#include <iterator>

using namespace std;

// 1. reverse iterator
// 2. human height, any occuluded element (<=) to be popped out. ex: 4 occuluds 3

// input: [2, 1, 2, 4, 3]
// output: [4, 2, 4, -1, -1]
template <typename T>
vector<T> nextGreaterElement(const vector<T> &elements)
{
    vector<T> res(elements.size());
    stack<T> s;
    // size_t has problem
    for (int i = elements.size() - 1; i >= 0; --i)
    {
        // it is <=
        while (!s.empty() && s.top() <= elements[i])
        {
            s.pop();
        }
        // case 3,4 and case 2
        res[i] = s.empty() ? -1 : s.top();
        s.push(elements[i]);
    }
    return res;
}

// input: [2, 1, 2, 4, 3]
// output: [1, -1, -1, 3, -1]

template <typename T>
vector<T> nextSmallerElement(const vector<T> &elements)
{
    vector<T> res(elements.size());
    stack<T> s;
    // size_t has problem
    for (int i = elements.size() - 1; i >= 0; --i)
    {
        // it is <=
        while (!s.empty() && s.top() >= elements[i])
        {
            s.pop();
        }
        // case 3,4 and case 2
        res[i] = s.empty() ? -1 : s.top();
        s.push(elements[i]);
    }
    return res;
}

int main()
{
    const auto nge = nextGreaterElement(vector<int>{2, 1, 2, 4, 3});
    
    copy(begin(nge), end(nge),
         ostream_iterator<int>(std::cout, " "));

    const auto nse = nextSmallerElement(vector<int>{2, 1, 2, 4, 3});

    copy(begin(nse), end(nse),
         ostream_iterator<int>(std::cout, " "));
    return 0;
}