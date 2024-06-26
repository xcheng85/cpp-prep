// Input: coins = [1,2,5], amount = 11
// Output: 3
// Explanation: 11 = 5 + 5 + 1

// dp[11] = min(dp[10], dp[9], dp[6]) + 1

// dp[5] = dp[0] + 1

// base case dp[0] = 0

// dp[-1] = INFINITY

// recursive
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int minCoins = numeric_limits<int>::max();
        if(amount < 0) {
            return -1;
        }
        if(amount == 0) {
            return 0;
        }
        if(_memorization.contains(amount)) {
            return _memorization.at(amount);
        }
        for(const auto& coin: coins) {
            int subResult = coinChange(coins, amount - coin);
            if(subResult != -1) {
                minCoins = min(minCoins, subResult + 1);
            }
        }
        int res = minCoins == numeric_limits<int>::max() ? -1 : minCoins;
        _memorization[amount] = res;
        return res;
    }

private: 
    unordered_map<int, int> _memorization;
};