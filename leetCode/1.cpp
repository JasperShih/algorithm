#include <iostream>
#include <vector>

/*

Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

*/

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int idx1 = 0; idx1 <= nums.size(); ++idx1) {
            int tmp = target - nums[idx1];
            for (int idx2 = idx1 + 1; idx2 < nums.size(); ++idx2) {
                if (tmp == nums[idx2])
                {
                    return std::vector<int> {idx1, idx2};
                }
            }
        }
        return {};
    }
};

int main() {
    std::vector<int> vec {2, 7, 11, 15};

    Solution sol = Solution();
    sol.twoSum(vec, 9);

    return 0;
}