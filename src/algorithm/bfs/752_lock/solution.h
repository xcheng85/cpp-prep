#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>

// initial: "0000"

// deadends = ["0201","0101","0102","1212","2002"],
// end condition: target = "0202"

// 4 digit * 2 (positive and negative) = 8 neighbor

// shortest path

using namespace std;

class Solution
{
public:
    // 1. each member in bfs carry the steps, waste more memory
    // 2. all the nodes advance at the same time, only need one int.

    int openLock(vector<string> &deadends, string target)
    {
        queue<string> bfs;
        string curr{"0000"s};
        if (std::find(deadends.begin(), deadends.end(), curr) == deadends.end())
            bfs.emplace(curr);

        int step{0};
        unordered_set<string> visited;
        // perf boost from beat 5% to 67%, o(n)-->o(1) for find element in container
        unordered_set<string> deadendCache(
            deadends.begin(), deadends.end());

        while (!bfs.empty())
        {
            // all advance at the same step
            auto s = bfs.size();
            for (int i = 0; i < s; ++i)
            {
                curr = bfs.front();
                bfs.pop();

                if (curr == target)
                {
                    return step;
                }

                for (size_t i = 0; i < curr.size(); ++i)
                {
                    string tmp{curr};
                    // positive
                    if (curr[i] == '9')
                    {
                        tmp[i] = '0';
                    }
                    else
                    {
                        tmp[i] = curr[i] + 1;
                    }
                    if (visited.find(tmp) == visited.end() &&
                        deadendCache.find(tmp) == visited.end())
                    // std::find(deadends.begin(), deadends.end(), tmp) == deadends.end())
                    {
                        bfs.emplace(tmp);
                        visited.insert(tmp);
                    }
                    // negative
                    if (curr[i] == '0')
                    {
                        tmp[i] = '9';
                    }
                    else
                    {
                        tmp[i] = curr[i] - 1;
                    }
                    if (visited.find(tmp) == visited.end() &&
                        deadendCache.find(tmp) == visited.end())
                    {
                        bfs.emplace(tmp);
                        visited.insert(tmp);
                    }
                }
            }
            ++step;
        }
        return -1;
    }
};