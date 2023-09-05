/*
[s1 string의 permutation 중 하나라도 s2의 substring이라면 True]
!! string이 길면 엄청 오래걸림 !!
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.

In other words, return true if one of s1's permutations is the substring of s2.

Example 1:

Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input: s1 = "ab", s2 = "eidboaoo"
Output: false
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 순열 생성 함수
void str_perm(char *s, int start, char permutations[1000][100], int *perm_count) {
    int len = strlen(s); // 문자열의 길이를 계산합니다.
    if (start == len) { // 시작 인덱스가 문자열의 길이와 같다면, 순열을 완성했습니다.
        strcpy(permutations[*perm_count], s); // 완성된 순열을 저장합니다.
        (*perm_count)++; // 순열의 수를 증가시킵니다.
        return;
    }

    for (int i = start; i < len; i++) {
        // 문자 스왑: 시작 인덱스와 i 인덱스의 문자를 교환합니다.
        char temp = s[start];
        s[start] = s[i];
        s[i] = temp;

        // 재귀 호출: 현재 시작 인덱스를 제외하고 다음 인덱스부터 순열 생성을 계속합니다.
        str_perm(s, start + 1, permutations, perm_count);

        // 백트래킹: 이전 상태로 문자열을 복원합니다.
        temp = s[start];
        s[start] = s[i];
        s[i] = temp;
    }
}

// s2에서 s1을 검색하는 함수
bool contains(char *s2, char *s1) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    for (int i = 0; i <= len2 - len1; i++) {
        // s2의 서브스트링을 s1과 비교합니다.
        if (strncmp(&s2[i], s1, len1) == 0) {
            return true; // 일치하는 경우 true를 반환합니다.
        }
    }

    return false; // 일치하는 서브스트링이 없는 경우 false를 반환합니다.
}

bool checkInclusion(char *s1, char *s2) {
    char permutations[1000][100]; // 순열을 저장할 배열입니다.
    int perm_count = 0; // 생성된 순열의 수입니다.

    // s1의 모든 순열을 생성합니다.
    str_perm(s1, 0, permutations, &perm_count);

    for (int i = 0; i < perm_count; i++) {
        // s2 내에서 순열이 존재하는지 확인합니다.
        if (contains(s2, permutations[i])) {
            return true; // 존재한다면 true를 반환합니다.
        }
    }

    return false; // s2 내에 어떠한 순열도 존재하지 않는다면 false를 반환합니다.
}

int main() {
    char s1[100], s2[100];

    // 테스트 케이스 입력
    strcpy(s1, "ab");
    strcpy(s2, "eidbaooo");

    if (checkInclusion(s1, s2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }


    /* 사용자로부터 input 입력받고 싶을 때 */
    // char s1[MAX_STRING_LENGTH];
    // char s2[MAX_STRING_LENGTH];

    // printf("Enter string s1: ");
    // scanf("%s", s1);
    // printf("Enter string s2: ");
    // scanf("%s", s2);

    // if (checkInclusion(s1, s2)) {
    //     printf("True\n");
    // } else {
    //     printf("False\n");
    // }

    return 0;
}
