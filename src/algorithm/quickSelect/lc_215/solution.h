#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

namespace QuickSelect
{
    // test case passed but took too lang
    class Solution215
    {
    public:
        int findKthLargest(vector<int> &nums, int k)
        {
            if (k > nums.size() || k <= 0)
            {
                return -1;
            }

            const auto pivot = nums.back();
            nums.pop_back();

            const auto itr = std::partition(nums.begin(), nums.end(), [=](const auto &n)
                                            { return n > pivot; });
            // std::move(v1.begin(), it, std::back_inserter(v2));  // ##
            vector<int> larger;

            std::move(nums.begin(), itr, std::back_inserter(larger));
            // difference from std::list, list no need to erase explictly
            nums.erase(nums.begin(), itr); // they are moved

            const auto s = larger.size();
            if (s == k - 1)
            {
                return pivot;
            }
            else if (s > k - 1)
            {
                // -1 for the pivot
                return findKthLargest(larger, k);
            }
            else
            {
                vector<int> smaller = std::move(nums);
                // -1: for pivot element
                return findKthLargest(smaller, k - s - 1);
            }
        }
    };
}

namespace PQ
{
    // test case passed but took too lang
    class Solution215
    {
    public:
        int findKthLargest(vector<int> &nums, int k)
        {
            // adaptor, default container is vector and less
            // max-heap
            // std::less and greater are template functor
            // std::priority_queue<int, vector<int>, std::greater<int>> pq;
            std::priority_queue<int, vector<int>, std::less<int>> maxHeap;

            for (const auto &n : nums)
            {
                // in-place
                maxHeap.emplace(n);
            }

            int count{0};
            int curr;
            while (!maxHeap.empty())
            {
                curr = maxHeap.top();
                maxHeap.pop();
                if (++count == k)
                {
                    break;
                }
            }
            return curr;
        }
    };

    class Solution247
    {
    public:
        vector<int> topKFrequent(vector<int> &nums, int k)
        {
            vector<int> res;

            unordered_map<int, int> countMap;

            for (const auto &n : nums)
            {
                ++countMap[n];
            }
            // [count, key]
            priority_queue<std::pair<int, int>> pq;
            for (const auto &[k, c] : countMap)
            {
                pq.emplace(make_pair(c, k));
            }

            int poppedCount{0};
            while (!pq.empty())
            {
                if (poppedCount == k)
                {
                    break;
                }
                const auto &[c, k] = pq.top();
                res.emplace_back(k);
                pq.pop();
                ++poppedCount;
            }
            return res;
        }
    };

    // minheap
    class Solution973
    {
    public:
        vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
        {
            // 1. calculate the euclidean distance, igore the sqrt
            // key: distance
            // value: offset in the input array
            // closest, min-heap
            priority_queue<pair<int, size_t>, vector<pair<int, size_t>>,
                           std::greater<pair<int, size_t>>>
                pq;
            for (size_t i = 0; i < points.size(); ++i)
            {
                const auto &x = points[i][0];
                const auto &y = points[i][1];
                const auto d = x * x + y * y;
                pq.emplace(make_pair(d, i));
            }

            vector<vector<int>> res;
            int count{0};
            while (!pq.empty())
            {
                if (count == k)
                    break;
                const auto &[d, offset] = pq.top();
                res.emplace_back(points[offset]);
                pq.pop();
                ++count;
            }
            return res;
        }
    };

    // The value of coordinate (a, b) of the matrix is the XOR of all matrix[i][j]
    // where 0 <= i <= a < m and 0 <= j <= b < n (0-indexed).

    // This like two-pass filtering
    // pass1: row direction (xor)
    // write to matrix
    // pass2: col direction (xor)
    // write to matrix
    // do normal pq

    // logic of XOR of multiple inputs, number of 1 is odd return 1

    // xor: a ^ b
    // bitwise nor:  ~
    class Solution1738
    {
    public:
        int kthLargestValue(vector<vector<int>> &matrix, int k)
        {
            // pass1: xor alongside x direction
            for (size_t r = 0; r < matrix.size(); ++r)
            {
                for (size_t c = 1; c < matrix[0].size(); ++c)
                {
                    matrix[r][c] = matrix[r][c - 1] ^ matrix[r][c];
                }
            }
            // pass2: xor alongside y direction
            for (size_t r = 1; r < matrix.size(); ++r)
            {
                for (size_t c = 0; c < matrix[0].size(); ++c)
                {
                    matrix[r][c] = matrix[r - 1][c] ^ matrix[r][c];
                }
            }

            priority_queue<int, vector<int>, greater<int>> minHeap;
            for (size_t r = 0; r < matrix.size(); ++r)
            {
                for (size_t c = 0; c < matrix[0].size(); ++c)
                {
                    const auto &curr = matrix[r][c];
                    if (minHeap.size() == k)
                    {
                        if (curr <= minHeap.top())
                        {
                        }
                        else
                        {
                            minHeap.pop();
                            minHeap.emplace(curr);
                        }
                    }
                    else
                    {
                        minHeap.emplace(curr);
                    }
                }
            }
            return minHeap.top();
        }
    };
}