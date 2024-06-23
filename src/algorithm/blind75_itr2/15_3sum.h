
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); ++i)
        {
            // why i+1, because the previous value has been considered.
            // like a tree.
            vector<vector<int>> matchedPairs = twoSum(nums, i + 1, nums.size() - 1, 0 - nums[i]);
            if (matchedPairs.size() > 0)
            {
                for (auto &p : matchedPairs)
                {
                    p.emplace_back(nums[i]);
                    res.emplace_back(p);
                }
            }
            // avoid duplicate 
            while(i + 1 < nums.size() && nums[i+1] == nums[i]) {
                ++i;
            }
        }
        return res;
    }

private:
    // multiple pairs
    vector<vector<int>> twoSum(vector<int> &sortedNums, int l, int r, int target)
    {
        //cout << "l: " << l << " r: " << r << " target: " << target << endl;
        vector<vector<int>> res;
        //  you may not use the same element twice
        while (l < r)
        {
            //cout << "l: " << l << " r: " << r << " target: " << target << endl;
            int leftValue = sortedNums[l], rightValue = sortedNums[r];
            int sum = (leftValue + rightValue);
            if (sum == target)
            {
                res.push_back({leftValue, rightValue});
                // avoid duplicates
                // 跳过所有重复的元素
                // difference vs 2sum one pair question
                while (l < r && sortedNums[l] == leftValue)
                {
                    ++l;
                }
                while (l < r && sortedNums[r] == rightValue)
                {
                    --r;
                }
            }
            else if (sum < target)
            {
                ++l;
            }
            else
            {
                --r;
            }
        }
        return res;
    }
};