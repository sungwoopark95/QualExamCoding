/*
[인접 문자가 같지 않게 string 다시 배치하기]
Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.

Return any possible rearrangement of s or return "" if not possible.

Example 1:
Input: s = "aab"
Output: "aba"

Example 2:
Input: s = "aaab"
Output: ""
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 26 // 알파벳 개수

typedef struct {
    char ch;   // 문자
    int count; // 해당 문자의 빈도수
} CharCount;

// 비교 함수: 우선순위 큐를 위한 함수
// CharCount 구조체의 count를 기반으로 내림차순 정렬
int compare(const void *a, const void *b) {
    return ((CharCount*)b)->count - ((CharCount*)a)->count;
}

char* reorganizeString(char* s) {
    int length = strlen(s); // 입력 문자열의 길이
    CharCount count[MAX_SIZE] = {0}; // 문자 빈도를 저장하기 위한 배열 초기화

    // 문자 빈도 계산
    for (int i = 0; i < length; i++) {
        count[s[i] - 'a'].ch = s[i]; // 해당 문자 저장
        count[s[i] - 'a'].count++;   // 해당 문자의 빈도수 증가
    }

    // 정렬: 빈도수에 따른 내림차순 정렬
    qsort(count, MAX_SIZE, sizeof(CharCount), compare);

    // 가장 높은 빈도가 문자열의 길이의 절반을 초과하는지 확인
    if (count[0].count > (length + 1) / 2) {
        return "";
    }

    // 결과 문자열을 저장할 공간 할당
    char* result = (char*)malloc(sizeof(char) * (length + 1));
    int idx = 0; // 결과 문자열에서 현재 채울 위치

    // 빈도수가 높은 문자부터 결과 문자열에 채우기
    for (int i = 0; i < MAX_SIZE; i++) {
        while (count[i].count > 0) {
            result[idx] = count[i].ch; // 결과 문자열에 문자 추가
            idx += 2; // 짝수 위치에 문자를 배치하기 위해 인덱스 2 증가

            // 짝수 위치가 부족한 경우 홀수 위치에 배치
            if (idx >= length) {
                idx = 1;
            }

            count[i].count--; // 해당 문자의 빈도수 감소
        }
    }
    result[length] = '\0'; // 결과 문자열 끝에 널 종료 문자 추가
    return result;
}

int main() {
    char s[501]; // 최대 500 문자 + 널 종료 문자
    printf("Enter string: ");
    scanf("%500s", s); // 최대 500문자를 읽습니다.

    char* result = reorganizeString(s); 
    printf("Reorganized: %s\n", result); 
    free(result); // 동적 할당 메모리 해제

    return 0;
}
