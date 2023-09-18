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