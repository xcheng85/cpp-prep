#include <vector>
#include <unordered_map>
#include <random>

using namespace std;

class Solution
{
public:
    Solution(vector<int> &nums)
    {
        for (size_t i = 0; i < nums.size(); ++i)
        {
            _m[nums[i]].emplace_back(i);
        }
    }

    int pick(int target)
    {
        auto numHit = _m[target].size();
        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(1, numHit);
        auto u = distrib(gen);

        return _m[target][u - 1];
    }

private:
    unordered_map<int, vector<size_t>> _m;
};
