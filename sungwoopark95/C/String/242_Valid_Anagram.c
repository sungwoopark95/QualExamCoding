#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 주어진 문자열을 사용하여 알파벳 별 빈도수를 배열로 반환하는 함수
void hashtable(const char* str, int* ans) {
    // 'a'부터 'z'까지의 각 알파벳에 대한 빈도수를 0으로 초기화
    for(int i = 0; i < 26; i++) {
        ans[i] = 0;
    }

    // 문자열의 각 문자에 대해 해당 문자의 빈도수를 증가
    int length = strlen(str);
    for(int i = 0; i < length; i++) {
        int idx = str[i] - 'a';  // 알파벳 'a'를 기준으로 한 문자의 인덱스 계산
        ans[idx]++;
    }
}

// 두 문자열이 아나그램인지 확인하는 함수
bool isAnagram(const char* s, const char* t) {
    int s_hash[26];
    int t_hash[26];

    // 주어진 문자열을 사용하여 알파벳 별 빈도수를 배열로 반환하는 함수
    // 두 문자열 s와 t에 대한 빈도수 배열 생성
    hashtable(s, s_hash);
    hashtable(t, t_hash);

    // 두 문자열의 빈도수 배열이 동일한지 비교하여 결과 반환
    for(int i = 0; i < 26; i++) {
        if(s_hash[i] != t_hash[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    const char* s = "anagram";
    const char* t = "nagaram";
    
    // 두 문자열이 아나그램인지 확인하고 결과 출력
    printf("%s\n", isAnagram(s, t) ? "True" : "False");

    return 0;
}
