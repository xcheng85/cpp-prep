#pragma once

#include <algorithm>
#include <iostream>

using namespace std;

namespace combinatorics
{
    class Solution
    {
    public:
        int uniquePaths(int m, int n)
        {
            //  return factorial(m + n - 2) // factorial(n - 1) // factorial(m - 1)
            // horizontal step: n - 1
            // vertical step: m - 1
            // n = h + v
            // r = h or v

            // C(n,r) = P(n, r) / r! = n!/(n-r)! * r!

            // P(n, r) = n!/(n-r)!

            //int nn = (n + m - 2);
            // to overcome overflow issue
            // take off(m-1)! ---> nn starts from [nn, n+m-2]
            // dividsor and diveder lenght n-1
            // * and / at the same step.
            int nn = m;
            unsigned long long res{1};
            for(int i = 1; i <= n - 1; ++i) {
                res *= nn;
                res /= i;
                ++nn;
            } 
            return res;
        }
    };
}


