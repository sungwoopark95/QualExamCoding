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

#include <stdio.h>
#include <math.h>
#include <string.h>

int reverse(int x) {
    if (0 <= x && x <= pow(2, 31) - 1) {
        char str[12]; // Max length of integer digits + 1
        sprintf(str, "%d", x);
        int len = strlen(str);
        //가운데 값 기준으로 swapping하는 방식
        for (int i = 0; i < len / 2; i++) {
            char temp = str[i];
            str[i] = str[len - 1 - i];
            str[len - 1 - i] = temp;
        }
        
        int output;
        sscanf(str, "%d", &output);
        return output;

		//음수인 경우 제일 첫번째 - 부호는 그대로 두기 때문에 그대로 output을 리턴함
    } else if (-pow(2, 31) <= x && x < 0) {
        char str[12]; // Max length of integer digits + 1
        sprintf(str, "%d", x);
        int len = strlen(str);
        
        for (int i = 1; i < len / 2 + 1; i++) {
            char temp = str[i];
            str[i] = str[len - i];
            str[len - i] = temp;
        }
        
        int output;
        sscanf(str, "%d", &output);
        return output;
    } else {
        return 0;
    }
}

int main(){
    int x = -121233;
    int result = reverse(x);
    printf("%d", result);
    
    return 0;
}