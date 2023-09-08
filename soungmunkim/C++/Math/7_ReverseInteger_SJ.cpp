/*
[숫자 뒤집기]
Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.

Assume the environment does not allow you to store 64-bit integers (signed or unsigned).

Example 1:
Input: x = 123
Output: 321

Example 2:
Input: x = -123
Output: -321

Example 3:
Input: x = 120
Output: 21
 
Constraints:
-231 <= x <= 231 - 1
*/
#include <iostream>
#include <cmath>
#include <string>

class Solution {
public:
    int reverse(int x) {
        if (0 <= x && x <= std::pow(2, 31) - 1) {
            std::string str = std::to_string(x);
            int len = str.length();
            
            for (int i = 0; i < len / 2; i++) {
                char temp = str[i];
                str[i] = str[len - 1 - i];
                str[len - 1 - i] = temp;
            }
            
            int output = std::stoi(str);
            return output;
        } else if (-std::pow(2, 31) <= x && x < 0) {
            std::string str = std::to_string(x);
            int len = str.length();
            
            for (int i = 1; i < len / 2 + 1; i++) {
                char temp = str[i];
                str[i] = str[len - i];
                str[len - i] = temp;
            }
            
            int output = std::stoi(str);
            return output;
        } else {
            return 0;
        }
    }
};

int main() {
    Solution solution;
    int x = -12345;
    int result = solution.reverse(x);
    std::cout << "Reversed: " << result << std::endl;
    return 0;
}

