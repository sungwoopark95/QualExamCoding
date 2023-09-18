/*
[order 순서대로 s의 순서를 바꾸기] replace 방법 사용한 것
!! word한개를 각 각 받을 땨ㅐ !!

Example 1:
Input: order = "cba", s = "abcd"
Output: "cbad"
Explanation: 
"a", "b", "c" appear in order, so the order of "a", "b", "c" should be "c", "b", and "a". 
Since "d" does not appear in order, it can be at any position in the returned string. "dcba", "cdba", "cbda" are also valid outputs.

(base) soungmunkim@gimseongmun-ui-MacBookPro String % gcc 791_CustomSortString_SM.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test    
Enter a order string: cba
Enter a string: abcd
Result: cbad

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a order string: "cbafg"
Enter a string: "abcd"
Result: cbad
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

# define ALPHABET_SIZE 26

// character 빈도 저장하는 구조체 정의
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

// 주어진 문자열(substring)의 문자 빈도를 계산하는 함수
Counter countFrequency(const char *s) {
    Counter c = newCounter();
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        // 해당 alphabet의 index = 'a' 뺀 것
        c.count[s[i] - 'a']++;  // 문자열의 각 문자에 대한 빈도 계산
    }
    return c;
}

// 문자열 내의 특정 문자를 다른 문자열로 바꾸는 함수 (word에서 한 char 지울 때)
/*
이 함수는 문자열 내의 특정 문자(char_to_find)를 다른 문자열(replace)로 대체
예를 들면, replace("Hello World!", 'o', "everyone")를 호출하면 
결과는 "Helleveryone Weveryonerld!"가 됩니다.
이 함수는 주어진 문자열에서 char_to_find 문자의 모든 인스턴스를 찾아 replace 문자열로 대체합니다.
*/
char* replace(char* str, const char char_to_find, const char* replace) {
    char *result, *tmp;
    size_t len_str = strlen(str);           // 원본 문자열의 길이 계산
    size_t len_replace = strlen(replace);   // 대체할 문자열의 길이 계산
    size_t count = 0;

    // 원본 문자열 내에서 바꿀 문자의 등장 횟수를 센다.
    for (size_t i = 0; i < len_str; i++) {
        if (str[i] == char_to_find)
            count++;
    }

    // 결과 문자열에 필요한 메모리 할당
    tmp = result = (char*)malloc(len_str + (len_replace - 1) * count + 1);

    // 원본 문자열을 순회하며 바꿀 문자를 찾아 대체 문자열로 바꾼다.
    while (*str) {
        if (*str == char_to_find) {
            strcpy(tmp, replace);
            tmp += len_replace;
            str++;
        } else {
            *tmp++ = *str++;
        }
    }
    *tmp = '\0';  // 결과 문자열의 끝에 NULL 문자 추가
    return result;
}

// 주어진 order 문자열에 따라 s 문자열을 정렬하는 함수
char* customSort(const char* order, const char* s){

    Counter s_counter = countFrequency(s);  // s 문자열의 문자 빈도수 계산

    char ans[1000] = {0}; // ans로 내보낼 word 초기화 
    size_t idx = 0;

    // order 문자열에 따라 s 문자열에서 해당 문자를 추출하고 삭제한다.
    for (size_t i = 0; i < strlen(order); i++) {

        // 해당 char의 빈도수 만큼 ans에 붙이기 
        int repeatCount = s_counter.count[order[i]-'a'];
        for (int j = 0; j < repeatCount; j++) {
            ans[idx++] = order[i];
        }

        // 해당 char을 s에서 지우기
        s = replace((char*)s, order[i], "");
    }

    strcat(ans, s);  // 남은 s 문자열을 결과 문자열 뒤에 추가
    char* result = (char*)malloc(strlen(ans) + 1);

    strcpy(result, ans);  // 결과 문자열을 동적 메모리에 복사
    return result;        // 결과 문자열 포인터 반환
}



// 불필요한 "" 나 , 제거하는 함수 
void removeExtraChars(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != '"' && str[i] != ',') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    // 입력받는 게 string array가 아닌 word형태임 (char*)
    char order[100];  // order 문자열을 저장하기 위한 배열
    char str[100];    // 입력받을 문자열을 저장하기 위한 배열
    char* sorted;     // 정렬된 결과를 저장하기 위한 포인터

    printf("Enter a order string: ");
    scanf("%[^\n]s", order);   // 줄바꿈 문자 전까지의 문자열을 입력받기 (공백 포함)
    getchar();  // 버퍼에 남아있는 줄바꿈 문자 제거

    printf("Enter a string: ");
    scanf("%[^\n]s", str);     // 줄바꿈 문자 전까지의 문자열을 입력받기 (공백 포함)

    removeExtraChars(order);   // order에서 불필요한 문자 제거
    removeExtraChars(str);     // str에서 불필요한 문자 제거

    sorted = customSort(order, str);  // 문자열 정렬

    printf("Result: %s\n", sorted);  // 정렬된 결과 출력

    free(sorted);  // 동적 할당된 메모리 반환
    return 0;
}


/*------------- 예제가 정해져 있을 경우의 int main ---------------*/
// int main() {
//     // 예제 데이터를 저장하는 2차원 문자열 배열 선언
//     char* examples[][2] = {
//         {"cba", "abcd"},
//         {"cba", "abcd"},
//         {"cbafg", "abcd"}
//     };

//     char* sorted;  // 정렬된 결과를 저장할 문자열 포인터 선언

//     // 예제 데이터를 순회하면서 각 예제에 대해 처리
//     for (int i = 0; i < sizeof(examples) / sizeof(examples[0]); i++) {
//         printf("Order: %s\n", examples[i][0]);  // 예제의 order 문자열 출력
//         printf("String: %s\n", examples[i][1]);  // 예제의 입력 문자열 출력
        
//         // customSort 함수를 사용하여 문자열 정렬
//         sorted = customSort(examples[i][0], examples[i][1]);
        
//         // 정렬된 결과 출력
//         printf("Result: %s\n\n", sorted);
        
//         // 동적으로 할당된 메모리 해제
//         free(sorted);
//     }

//     return 0;  // 프로그램 종료
// }
