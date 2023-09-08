/*
[숫자를 로마 숫자로 바꾸기]
!! 큰수부터 빼면서 작은 수까지 다 처리하는 방식 !!
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, 2 is written as II in Roman numeral, just two one's added together. 
12 is written as XII, which is simply X + II. 
The number 27 is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. 
However, the numeral for four is not IIII. Instead, 
    the number four is written as IV. 
    
Because the one is before the five we subtract it making four. 
The same principle applies to the number nine, which is written as IX. 
There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.

Example 1:
Input: num = 3
Output: "III"
Explanation: 3 is represented as 3 ones.

Example 2:
Input: num = 58
Output: "LVIII"
Explanation: L = 50, V = 5, III = 3.

Example 3:
Input: num = 1994
Output: "MCMXCIV"
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4

(base) soungmunkim@gimseongmun-ui-MacBookPro String % g++ -std=c++17 12_IntegerToRoman.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                      
Enter numbers: 3
III
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter numbers: 58
LVIII
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter numbers: 1994 
MCMXCIV
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int len(char* string) {
    int length = 0;
    while (string[length] != '\0') {
        length++;
    }
    return length;
}

void intToRoman(int num){
    // 로마 숫자와 해당 숫자의 값을 정의
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char* symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    // int array size 구하기 (static 할당)
    int size = sizeof(values) / sizeof(values[0]);

    char result[100][100];
    int result_idx = 0;

    // 각 값에 해당하는 로마 숫자를 결과 문자열에 추가
    for(int i=0; i<size; i++){
        // 주어진 숫자가 현재 로마 숫자 값보다 크거나 같은 동안 반복
        while(num >= values[i]){
            num -= values[i];  // 숫자에서 로마 숫자 값만큼 빼고
            // 결과 문자열에 로마 숫자 추가
            strcpy(result[result_idx++], symbols[i]);

            // printf("%s %d\n", symbols[i], len(symbols[i]));
           
        }
    }
    for(int i=0; i<result_idx; i++){
        printf("%s", result[i]);
    }
    printf("\n");
}


int main(int argc, char* argv[]){
    char* input = argv[1];
    int num;

    printf("Enter the number: ");
    scanf("%d", &num);

    intToRoman(num);

    int* input = (int*)malloc(sizeof(int));
    
    int idx = 0;
    
}