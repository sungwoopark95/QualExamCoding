/*
[부분 문자열중에 가장 긴 palindrome 찾기]
Given a string s, return the longest 
palindromic substring in s.
 
Example 1:

Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Example 2:
Input: s = "cbbd"
Output: "bb"
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 주어진 시작과 끝 인덱스 사이의 문자열이 팰린드롬인지 확인하는 함수
bool isPalindrome(const char* s, int start, int end) {
    // 시작 인덱스가 끝 인덱스보다 작은 동안
    while (start < end) {
        // 시작과 끝 문자가 다르면 팰린드롬이 아님
        if (s[start] != s[end]) return false;
        start++;  // 시작 인덱스 증가
        end--;    // 끝 인덱스 감소
    }
    // 위의 조건을 모두 만족하면 팰린드롬
    return true;
}

// 문자열 s에서 가장 긴 팰린드롬 부분 문자열을 찾아 result에 저장하는 함수
void longestPalindrome(const char* s, char* result) {
    int len = strlen(s);  // 입력 문자열의 길이 계산
    // 입력 문자열의 길이가 1 이하일 경우 그대로 복사하고 함수 종료
    if (len < 2) {
        strcpy(result, s);
        return;
    }

    int start = 0;  // 팰린드롬의 시작 인덱스
    int maxLen = 1;  // 팰린드롬의 최대 길이

    // 문자열 전체를 순회
    for (int i = 0; i < len; ++i) {
        // 현재 인덱스에서 가장 긴 팰린드롬을 찾기 위한 조건문
        if (i - maxLen >= 1 && isPalindrome(s, i - maxLen - 1, i)) {
            start = i - maxLen - 1;
            maxLen += 2;
            continue;  // 다음 반복으로 넘어감
        }
        // 두 번째로 긴 팰린드롬을 찾기 위한 조건문
        if (isPalindrome(s, i - maxLen, i)) {
            start = i - maxLen;
            maxLen += 1;
        }
    }
    // 찾은 팰린드롬의 시작 인덱스와 길이를 사용하여 부분 문자열을 result에 복사
    strncpy(result, s + start, maxLen);
    result[maxLen] = '\0';  // 문자열의 끝을 나타내는 NULL 문자 추가
}

// 메인 함수
int main() {
    char s[1000], result[1000];  // 입력 문자열 및 결과 문자열 저장을 위한 배열 선언
    scanf("%s", s);  // 사용자로부터 문자열 입력 받음
    longestPalindrome(s, result);  // 가장 긴 팰린드롬 문자열 계산
    printf("%s\n", result);  // 결과 출력
    return 0;  // 프로그램 종료
}
