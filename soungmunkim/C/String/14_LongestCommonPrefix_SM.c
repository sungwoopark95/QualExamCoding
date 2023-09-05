/*
[젤 첫번째 문자를 포함해서 다 겹치는 가장 긴 char 찾기]
!!!첫번째 문자가 무조건 같아야 함!!!

Write a function to find the longest common prefix string amongst an array of strings.
If there is no common prefix, return an empty string "".

 

Example 1:
Input: strs = ["flower","flow","flight"]
Output: "fl"

Example 2:
Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.


(base) soungmunkim@gimseongmun-ui-MacBookPro String % gcc 14_LongestCommonPrefix_SM.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                 
문자열 배열을 입력하세요 (예: ["단어1", "단어2"]): ["flower","flow","flight"]
가장 긴 공통 접두사: fl
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 가장 긴 공통 접두사를 찾는 함수
char* longestCommonPrefix(char** strs) {
    int strsSize = 0;
    // strs 배열의 크기를 파악합니다. (NULL을 만날 때까지 반복)
    while (strs[strsSize] != NULL) {
        strsSize++;
    }
    
    // 문자열이 없는 경우 빈 문자열을 반환합니다.
    if (strsSize == 0) {
        return "";
    }
    
    // 첫 번째 문자열을 접두사로 초기화합니다. (malloc 사용)
    char* prefix = (char*)malloc(sizeof(char) * (strlen(strs[0]) + 1));
    strcpy(prefix, strs[0]);
    
    // 첫 번째 문자열의 각 문자를 순회
    for (int i = 0; prefix[i] != '\0'; i++) {
        char c = prefix[i];  // 첫 번째 문자열의 i번째 문자

        // 다른 문자열들 순회
        for (int j = 1; j < strsSize; j++) {
            // i가 현재 문자열의 길이와 같거나, 현재 문자열의 i번째 문자가 c와 다를 경우
            if (i == strlen(strs[j]) || strs[j][i] != c) {
                prefix[i] = '\0';  // 현재까지의 접두사 마지막을 표시하고 반환
                return prefix;     // 여기서 접두사를 반환합니다. (break처럼)
            }
        }
    }
    return prefix;
}

int main() {
    char input[1000];
    // 사용자에게 문자열 배열을 입력받습니다.
    printf("문자열 배열을 입력하세요 (예: [\"단어1\", \"단어2\"]): ");
    fgets(input, 1000, stdin);

    input[strcspn(input, "\n")] = 0;  // 개행 문자 제거

    char* token;
    int count = 0;
    char* strs[101];  // 최대 100개의 문자열 + NULL 포인터를 저장하기 위한 배열

    // 입력 받은 문자열을 파싱하여 개별 단어를 추출합니다.
    token = strtok(input, "[\",\t\n\r ]");

    while (token != NULL) {
        strs[count] = (char*)malloc(strlen(token) + 1);
        strcpy(strs[count], token);
        count++;

        token = strtok(NULL, "[\",\t\n\r ]");
    }
    strs[count] = NULL;  // 마지막에 NULL 포인터 추가

    // 가장 긴 공통 접두사를 출력합니다.
    printf("가장 긴 공통 접두사: %s\n", longestCommonPrefix(strs));

    // 동적 할당한 메모리를 해제합니다.
    for(int i = 0; i < count; i++) {
        free(strs[i]);
    }

    return 0;
}
