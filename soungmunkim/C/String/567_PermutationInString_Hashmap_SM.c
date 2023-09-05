/*
[s1 string의 permutation 중 하나라도 s2의 substring이라면 True]
!! window 방법처럼 한문자씩 옮기면서 char 빈도 테이블 업뎃하기 !!
** dict 사용 방법 -> struct 이용

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

#define ALPHABET_SIZE 26  // 알파벳 크기 정의 (영어 소문자는 26개)

// 문자 빈도를 저장하는 구조체 정의
typedef struct {
    int count[ALPHABET_SIZE];
} Counter;

// 새로운 Counter를 초기화하는 함수. 모든 알파벳의 빈도를 0으로 설정
Counter newCounter() {
    Counter c;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        c.count[i] = 0;
    }
    return c;
}

// 주어진 문자열의 문자 빈도를 계산하는 함수
Counter countFrequency(const char *s, int len) {
    Counter c = newCounter();
    for (int i = 0; i < len; i++) {
        // 해당 alphabet의 index = 'a' 뺀 것
        c.count[s[i] - 'a']++;  // 문자열의 각 문자에 대한 빈도 계산
    }
    return c;
}

// 두 Counter 객체가 동일한지 확인하는 함수
bool isEqual(Counter c1, Counter c2) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (c1.count[i] != c2.count[i]) {
            return false;
        }
    }
    return true;
}

bool checkInclusion(const char *s1, const char *s2) {
    int len_s1 = strlen(s1);
    int len_s2 = strlen(s2);

    if (len_s1 > len_s2) {
        return false;
    }

    Counter s1_counter = countFrequency(s1, len_s1);  // s1 문자열에 대한 빈도 계산
    Counter s2_counter = countFrequency(s2, len_s1);  // s2 문자열의 처음 len(s1)에 대한 빈도 계산

    for (int i = len_s1; i < len_s2; i++) {
        if (isEqual(s1_counter, s2_counter)) {
            return true;
        }

        // 슬라이딩 윈도우에서 새로운 문자 추가 (해당 char index 알 수 있음)
        s2_counter.count[s2[i] - 'a']++;

        // 슬라이딩 윈도우에서 가장 오래된 문자 제거
        s2_counter.count[s2[i - len_s1] - 'a']--;

    }

    // 마지막 슬라이딩 윈도우에 대한 빈도 비교
    return isEqual(s1_counter, s2_counter);
}

int main() {
    const char *s1 = "ab";
    const char *s2 = "eidbaooo";
    if (checkInclusion(s1, s2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return 0;
}
