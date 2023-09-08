"""
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
"""
import math

class Solution(object):
    def reverse(self, x):
        """
        :type x: int
        :rtype: int
        """
        if 0 <= x <= math.pow(2, 31) - 1:
            x = list(str(x))
            x.reverse()
            output = int("".join(x))
        elif -math.pow(2, 31) <= x < 0:
            x = list(str(x))[1:]
            x.reverse()
            output = -int("".join(x))
        else:
            return 0

        if  -math.pow(2, 31) <= output <=  math.pow(2, 31) - 1:
            return output
        else:
            return 0        

