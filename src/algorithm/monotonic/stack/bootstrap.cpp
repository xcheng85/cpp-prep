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

template <typename T>
vector<int> nextGreaterElementIndex(const vector<T> &elements)
{
    vector<int> res(elements.size());
    // store index
    stack<size_t> indexStack;
    // size_t has problem
    for (int i = elements.size() - 1; i >= 0; --i)
    {
        // it is <=
        while (!indexStack.empty() && elements[indexStack.top()] <= elements[i])
        {
            indexStack.pop();
        }
        // case 3,4 and case 2
        res[i] = indexStack.empty() ? -1 : indexStack.top();
        indexStack.push(i);
    }
    return res;
}

// Find next Smaller of next Greater in an array
template <typename T>
vector<T> nextSmallerOfNextGreaterElement(const vector<T> &elements)
{
    // o(n) + o(n)
    // index
    const auto ngi = nextGreaterElementIndex(elements);
    std::cout << "ngi\n";
    copy(begin(ngi), end(ngi), ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    const auto nse = nextSmallerElement(elements);

    vector<T> res(elements.size());
    for (size_t i = 0; i < res.size(); ++i)
    {
        // don't forget the -1 case
        if (ngi[i] == -1)
        {
            res[i] = -1;
        }
        else
        {
            res[i] = nse[ngi[i]];
        }
    }
    return res;
}

int main()
{
    const auto nge = nextGreaterElement(vector<int>{2, 1, 2, 4, 3});

    std::cout << "nge\n";
    copy(begin(nge), end(nge),
         ostream_iterator<int>(std::cout, " "));

    std::cout << "nse\n";
    const auto nse = nextSmallerElement(vector<int>{2, 1, 2, 4, 3});
    copy(begin(nse), end(nse),
         ostream_iterator<int>(std::cout, " "));

    std::cout << "nsnge\n";
    const auto nsnge = nextSmallerOfNextGreaterElement(vector<int>{5, 1, 9, 2, 5, 1, 7});
    copy(begin(nsnge), end(nsnge),
         ostream_iterator<int>(std::cout, " "));
    return 0;
}