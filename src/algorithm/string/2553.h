// to_string, 
// 
class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        int numDigets = 0;
        vector<string> snums;
        snums.reserve(nums.size());
        for (const auto& n : nums) {
            snums.push_back(std::to_string(n));
            numDigets += snums.back().size();
        }
        vector<int> res(numDigets);
        int i = 0;
        for (const auto& sn : snums ) {
            for(const auto& c : sn){
                res[i++] = c - '0';
            }
        }
        return res;
    }

    // int count_digit(int number) {
    //     int count = 0;
    //     while (number != 0) {
    //         number = number / 10;
    //         count++;
    //     }
    //     return count;
    // }

    // void write(vector<int>& res, int start) {
    //     int count = 0;
    //     while (number != 0) {
    //         number = number / 10;
    //         count++;
    //     }
    //     return count;
    // }
};