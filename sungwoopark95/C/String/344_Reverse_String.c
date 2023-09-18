/*
주어진 string을 뒤집되, 새로운 list를 생성하지 않고 in-place로 작동하도록 해야 함

Input: s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]

Input: s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseString(char* s) {
    // 길이 -> c의 strlen 사용
    int sSize = strlen(s);

    // 주어진 문자열의 절반만큼만 반복하며
    for (int i = 0; i < (sSize / 2); i++) {
        // 현재 문자를 임시 변수에 저장
        char temp = s[i];
        
        // 현재 문자의 위치와 대응하는 문자의 위치를 바꾼다.
        s[i] = s[sSize - 1 - i];
        
        // 임시 변수에 저장한 문자를 대응하는 문자의 위치에 놓는다.
        s[sSize - 1 - i] = temp;
    }
}

int main() {
    // string to Char*
    char buffer[1000];  // 임시 버퍼. 적당한 크기로 지정해야 합니다.
    printf("Enter a string you want : ");
    scanf("%s", buffer);
    char* result = (char*)malloc(strlen(buffer) + 1);  // 필요한 크기만큼 메모리 할당
    strcpy(result, buffer);
    printf("%s\n", result);

    reverseString(result);
    printf("%s\n", result);

    free(result);  // 메모리 해제
    return 0;
}
