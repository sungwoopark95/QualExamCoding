#include <stdio.h>
#include <stdlib.h>

// 내부 함수: 문자열의 길이를 반환
int len(char* str) {
    int i = 0; // 문자열의 인덱스를 나타내는 변수
    // 문자열의 끝('\0')에 도달할 때까지 반복
    while (str[i] != '\0') {
        i++; // 인덱스 증가
    }
    return i; // 문자열의 길이 반환
}

// 주어진 문자열 배열에서 가장 긴 공통 접두사를 찾는 함수
char * longestCommonPrefix(char ** strs, int strsSize) {
    // 모든 문자열을 순회하며 빈 문자열이 있는지 확인
    for (int i=0;i<strsSize;i++) {
        char* word = strs[i]; // 현재 문자열을 가리키는 포인터
        // 문자열이 빈 경우
        if (len(word) == 0) {
            return ""; // 공통 접두사는 없다는 뜻이므로 빈 문자열 반환
        }
    }

    int max_length = 1000; // 문자열의 최대 길이 초기값 설정
    // 모든 문자열을 순회하며 가장 짧은 문자열의 길이를 찾음
    for (int i=0;i<strsSize;i++) {
        char* word = strs[i]; // 현재 문자열을 가리키는 포인터
        // 현재 문자열의 길이가 최대 길이보다 작은 경우
        if (max_length > len(word)) {
            max_length = len(word); // 최대 길이 업데이트
        }
    }

    char common[max_length]; // 공통 접두사를 저장할 배열
    int idx = 0; // 공통 접두사의 현재 인덱스
    int is_break = 0; // 중단 플래그
    // 가장 짧은 문자열의 길이만큼 반복
    for (int i=0;i<max_length;i++) {
        char start = strs[0][i]; // 첫 번째 문자열의 현재 문자
        // 나머지 문자열들과 비교
        for (int j=1;j<strsSize;j++) {
            // 다른 문자열의 현재 문자와 첫 번째 문자열의 현재 문자가 다른 경우
            if (strs[j][i] != start) {
                is_break = 1; // 중단 플래그 설정
                break; // 내부 반복문 종료
            }
        }
        // 모든 문자열이 동일한 문자를 가지면 공통 접두사 배열에 추가
        if (!is_break) {
            common[idx++] = start;
        }
    }

    // 결과를 저장할 동적 메모리 할당
    char* to_return = (char*)malloc((idx+1) * sizeof(char));
    // 공통 접두사 배열의 내용을 결과 메모리에 복사
    for (int i=0;i<idx;i++) {
        to_return[i] = common[i];
    }
    to_return[idx] = '\0'; // 문자열 끝 표시
    return to_return; // 결과 반환
}

int main() {
    char* strs[4] = {"flower", "flow", "flight", "float"};
    char* ans = longestCommonPrefix(strs, 4);
    printf("%s\n", ans);

    return 0;
}
