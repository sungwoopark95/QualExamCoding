#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*-------- 문자열 word에서 문자 ch가 있는지 확인하는 함수: ---------*/
bool in_char(const char* word, char ch) {
    // strchr 함수는 주어진 문자 ch를 문자열 word에서 찾습니다. 
    // ch를 찾지 못하면 NULL을 반환합니다.
    return strchr(word, ch) != NULL;
}

/*-------- 문자열 sentence에서 단어 word가 있는지 확인하는 함수: ---------*/
bool in_str(const char* sentence, const char* word) {
    // strstr 함수는 하나의 문자열에서 다른 문자열을 찾습니다.
    // word를 찾지 못하면 NULL을 반환합니다.
    return strstr(sentence, word) != NULL;
}

/*-------- 배열에 특정 원소가 있는지 확인하는 함수 (정수형을 대상으로 합니다): ---------*/
bool in_array(const int arr[], int length, int value) {
    for(int i = 0; i < length; i++) {
        if(arr[i] == value) return true; // 배열에서 값을 찾으면 true 반환
    }
    return false; // 값을 찾지 못하면 false 반환
}


int main() {
    // 예제 코드
    char sentence[] = "This is a sample sentence.";
    char word[] = "sample";
    char ch = 's';

    printf("%d\n", in_char(sentence, ch)); // 1 출력
    printf("%d\n", in_str(sentence, word)); // 1 출력

    int arr[] = {1, 2, 3, 4, 5};
    int value = 3;
    printf("%d\n", in_array(arr, sizeof(arr) / sizeof(int), value)); // 1 출력

    return 0;
}


/*-------- 문자열 str에서 부분 문자열 substring이 있는지 확인하는 함수: ---------*/
bool in_substring(const char* str, const char* substring) {
    // strstr 함수는 str 문자열에서 substring을 찾습니다.
    // substring을 찾지 못하면 NULL을 반환합니다.
    return strstr(str, substring) != NULL;
}

int main() {
    // 예제 코드
    char sentence[] = "This is a sample sentence.";
    char word[] = "sample";

    printf("%d\n", in_substring(sentence, word)); // 1 출력 (찾았을 때)
    printf("%d\n", in_substring(sentence, "notfound")); // 0 출력 (찾지 못했을 때)

    return 0;
}