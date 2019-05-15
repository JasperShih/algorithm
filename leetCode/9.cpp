#include <iostream>
#include <vector>
#include <math.h>

/*

Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

Example 1:

Input: 121
Output: true
Example 2:

Input: -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
Example 3:

Input: 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
Follow up:

Coud you solve it without converting the integer to a string?

*/

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        vector<int> vec;
        int idx = 0;
        int integer;

        if (x == 0)
        {
            return true;
        }
        for(;;)
        {
            integer = x/pow(10, idx);
            if (integer > 0)
            {
                vec.push_back(integer%10);
                idx++;
            } else{
                break;
            }
        }

        for (int i = 0; i < vec.size() / 2; ++i) {
            if (vec[i] != vec[vec.size()-1-i])
            {
                return false;
            }
        }
        return !vec.empty();
    }
};

int main() {

    Solution sol = Solution();
    cout << sol.isPalindrome(0);
    return 0;
}