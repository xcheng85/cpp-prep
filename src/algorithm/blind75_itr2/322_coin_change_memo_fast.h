class Solution {
    private:
        vector<int> memo;
        
        /**
         * memo 数组记录了 amount 对应的最优解，-666 代表还未被计算。
         * 因此，在计算 amount 对应的最优解时需要先查找 memo。
         */
        int dp(vector<int>& coins, int amount){
            if(amount == 0) return 0; // 如果 amount = 0，那么硬币数量为 0
            if(amount < 0) return -1; // 如果 amount < 0，那么无解
            if(memo[amount] != -666) return memo[amount]; // 查备忘录，如果有最优解则直接返回
            
            int res = INT_MAX;
            /**
             * 在硬币数组 coins 中依次选取每个硬币。
             * 对于当前选择的硬币，计算是包含该硬币所需的子问题的最优解 subProblem。
             * 如果子问题无解，则直接跳过该硬币。
             * 在所有子问题中，选取最优解，并加上该硬币的数量。
             * 最终的结果 res 即为 amount 对应的最优解，该结果存入 memo 中。
             */
            for(int coin : coins){
                int subProblem = dp(coins, amount - coin);
                if(subProblem == -1) continue;
                res = min(res, subProblem + 1);
            }
            
            memo[amount] = res == INT_MAX ? -1 : res;
            return memo[amount];
        }
        
    public:
        int coinChange(vector<int>& coins, int amount) {
            /**
             * 初始化备忘录 memo，memo 数组的长度为 amount+1。
             * memo 数组记录了 amount 对应的最优解，-666 代表还未被计算。
             * 因此，在计算 amount 对应的最优解时需要先查找 memo，再根据结果进行计算。
             */
            memo = vector<int>(amount + 1, -666);
            return dp(coins, amount);
        }
};