class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        if (nums.size() == 0)
        {
            return 0;
        }

        auto curr = nums[0];
        auto currIdx = 0;

        for (size_t i = 1; i < nums.size(); ++i)
        {
            if (curr == nums[i])
            {
            }
            else
            {
                curr = nums[i];
                ++currIdx;
                nums[currIdx] = nums[i];
            }
        }
        return currIdx + 1;
    }
};