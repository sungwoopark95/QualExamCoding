/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: 
(you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
 
Example 1:
Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:
Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I

Example 3:
Input: s = "A", numRows = 1
Output: "A"
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* convert(char* s, int numRows) {
    int len = strlen(s);
    // numRows가 1인 경우 바로 원본 문자열 반환
    if (numRows == 1) return s;

    // 결과 문자열을 저장할 버퍼 할당
    char* ret = (char*)malloc(len + 1);
    int k = 0; // ret의 현재 인덱스

    for (int row = 0; row < numRows; row++) {
        int i = row;
        while (i < len) {
            // 주 대각선 문자 추가
            ret[k++] = s[i];
            i += (numRows - 1) * 2; // 다음 주 대각선 문자 위치로 점프

            // 부 대각선 문자 추가 (첫 번째와 마지막 행 제외)
            if (row > 0 && row < numRows - 1 && i - row * 2 < len) {
                ret[k++] = s[i - row * 2];
            }
        }
    }
    ret[k] = '\0'; // 문자열 종료
    return ret;
}

int main() {
    char s[] = "PAYPALISHIRING";
    int numRows = 3;
    char* result = convert(s, numRows);
    printf("%s\n", result);
    free(result); // 동적 할당 해제
    return 0;
}
