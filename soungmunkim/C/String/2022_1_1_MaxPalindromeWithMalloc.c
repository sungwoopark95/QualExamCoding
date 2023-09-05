/*
[Max palindrome 찾기] 동적 할당 활용!

"palindrome"은 앞에서 뒤로 읽었을 때와 뒤에서 앞으로 읽었을 때 동일한 문자열이나 숫자, 또는 다른 시퀀스를 의미
    즉, palindrome은 그 내용이 앞뒤가 똑같은 단어나 문장을 지칭
    
The list contains palindromes that are not a substring of another palindrome.
A substring is a contiguous sequence of characters within a string.
The characters used in a string are only lower-case alphabets and a space character.

# TestCase
(base) soungmunkim@gimseongmun-ui-MacBookPro String % gcc 2022_1_1_MaxPalindrome_SM.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                 
Please enter a string: 
kabccbadzdefgfeda
"k", "abccba", "dzd", "defgfed"
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                 
Please enter a string: 
kabccba dzabccbaza
"k", " ", "d", "zabccbaz", "aza"
*/

/*
1. 문자열 s의 모든 substring을 찾습니다.
2. 각 substring이 palindrome인지 확인합니다.
3. palindrome이라면, 이 palindrome이 다른 palindrome의 substring인지 확인합니다.
4. substring이 아닌 palindrome 중에서 가장 긴 palindrome을 선택합니다. (palindrome 중에 서로 substring 아닌지 체크)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 동적 배열의 기본 구조를 정의하기 위한 구조체
typedef struct {
    char** data;      // 문자열 데이터를 저장할 이중 포인터
    int size;         // 현재 저장된 문자열의 수
    int capacity;     // 할당된 메모리의 크기
} DynamicArray;

// 초기 용량을 가진 동적 배열을 생성하는 함수
DynamicArray* createDynamicArray(int initialCapacity) {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));  // 동적 배열의 메모리 할당
    arr->data = (char**)malloc(initialCapacity * sizeof(char*));     // 초기 용량만큼의 메모리 할당
    arr->size = 0;                                                   // 초기 사이즈는 0
    arr->capacity = initialCapacity;                                 // 초기 용량 설정
    return arr;                                                      // 생성된 동적 배열 반환
}

// 동적 배열에 문자열 값을 추가하는 함수
void insertDynamicArray(DynamicArray* arr, char* value) {
    // 현재 크기가 용량을 초과할 경우
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;   // 용량을 두 배로 확장
        arr->data = (char**)realloc(arr->data, arr->capacity * sizeof(char*));  // 확장된 용량만큼 메모리 재할당
    }
    arr->data[arr->size] = strdup(value); // 문자열 복사 후 저장
    arr->size++;                       // 사이즈 증가
}

// 동적 배열의 메모리를 해제하는 함수
void freeDynamicArray(DynamicArray* arr) {
    for (int i = 0; i < arr->size; i++) {
        free(arr->data[i]);  // 각 문자열 메모리 해제
    }
    free(arr->data); // 이중 포인터 메모리 해제
    free(arr);        // 구조체 메모리 해제
}

// 문자열이 회문인지 검사하는 함수
bool palindrome(char *s){
    char reversed_s[300] = {0}; // 뒤집힌 문자열을 저장하기 위한 배열
    int n = strlen(s);    // 원본 문자열의 길이 계산
    int j = 0;

    // 문자열을 뒤집어 reversed_s에 저장
    for(int i = n-1; i >= 0; i--){
        reversed_s[j++] = s[i];
    }
    reversed_s[j] = '\0'; // 뒤집힌 문자열 종료

    // 원래 문자열과 뒤집은 문자열이 같으면 true 반환
    if (strcmp(s, reversed_s) == 0){
        return true;
    }
    else {
        return false;
    }
}

// t 문자열이 s 문자열의 부분 문자열인지 검사하는 함수
bool substring(char* s, char* t){
    int n = strlen(s); // s 문자열의 길이
    int m = strlen(t); // t 문자열의 길이

    if (m > n) return false;

    // s의 각 부분 문자열과 t를 비교
    for(int i = 0; i <= n-m; i++){
        char slice[300];
        strncpy(slice, &s[i], m);// s의 부분 문자열 복사
        slice[m] = '\0';
        if(strcmp(slice, t) == 0) return true;   // 부분 문자열과 t가 같으면 true 반환
    }
    return false;
}

// 문자열 s에서 가장 긴 회문을 찾는 함수
void max_palindrome(char* s){
    DynamicArray* max_pals = createDynamicArray(10);    // 최대 회문들을 저장할 동적 배열 생성
    DynamicArray* filtered_max_pals = createDynamicArray(10);   // 필터링된 회문들을 저장할 동적 배열 생성

    // 가능한 모든 부분 문자열에 대해서 회문인지 검사
    for(int i = 0; i < strlen(s); i++){
        for(int j = i; j < strlen(s); j++){
            char sub[100] = {0};
            strncpy(sub, &s[i], j-i+1);  // s의 부분 문자열 복사
            sub[j - i + 1] = '\0';

            if(palindrome(sub)){  // 부분 문자열이 회문인 경우
                bool is_maximal = true;

                // 현재 부분 문자열이 이미 찾은 회문들 중 하나의 부분 문자열인지 검사
                for(int k = 0; k < max_pals->size; k++){
                    if(substring(max_pals->data[k], sub) && strcmp(max_pals->data[k], sub) != 0){
                        is_maximal = false;
                        break;
                    }
                }

                // 현재 부분 문자열이 회문이고 다른 회문의 부분 문자열이 아니면 추가
                if(is_maximal) {
                    insertDynamicArray(max_pals, sub);
                }
            }
        }
    }

    // 찾은 회문들 중에서 다른 회문의 부분 문자열인 것을 제외
    for(int i=0; i < max_pals->size; i++){
        bool is_substring = false;
        for(int j=0; j < max_pals->size; j++){
            if(i != j) {
                if(substring(max_pals->data[j], max_pals->data[i])){
                    is_substring = true;
                    break;
                }
            }
        }
        if(!is_substring){
            insertDynamicArray(filtered_max_pals, max_pals->data[i]);
        }
    }

    // 최종 결과 출력
    printf("[");
    for (int k=0; k < filtered_max_pals->size; k++) {
        printf("\"%s\"", filtered_max_pals->data[k]);
        if(k != filtered_max_pals->size -1) {
            printf(", ");
        }
    }
    printf("]\n");

    // 동적 배열의 메모리 해제
    freeDynamicArray(max_pals);
    freeDynamicArray(filtered_max_pals);
}