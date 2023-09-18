/*
[order 순서대로 s의 순서를 바꾸기] replace 방법 없이 푼 것
!! word한개를 각 각 받을 땨ㅐ !!

(base) soungmunkim@gimseongmun-ui-MacBookPro String % gcc 791_CustomSortStringWithoutReplace.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a order string: cba
Enter a string: abcd
Result: cbad

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a order string: "cbafg"
Enter a string: "abcd"
Result: cbad
*/

/*-----------------(with out replace) sorted로 order에 나온 만큼 붙이고 마지막 남은 것 붙이는 방법 -----------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26   // 알파벳 크기를 정의 (a부터 z까지 총 26개)

// 문자의 빈도를 저장하는 구조체 정의
typedef struct {
    int count[ALPHABET_SIZE];
} Counter;

// 새로운 Counter 구조체 인스턴스를 초기화하는 함수. 모든 알파벳의 빈도를 0으로 설정
Counter newCounter() {
    Counter c;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        c.count[i] = 0;   // 각 알파벳의 빈도수를 0으로 초기화
    }
    return c;
}

// 문자열의 문자 빈도를 계산하는 함수
Counter countFrequency(const char *s) {
    Counter c = newCounter();
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        c.count[s[i] - 'a']++;  // 문자열의 각 문자에 대한 빈도 계산
    }
    return c;
}

char* customSort(const char* order, const char* s) {
    // s 문자열 내 문자의 빈도를 계산
    Counter s_counter = countFrequency(s);
    
    // 정렬될 결과 문자열을 저장할 메모리를 할당하며, 
    // 입력 문자열 s의 길이만큼 할당하고 추가로 널 문자를 위한 공간을 확보한다.
    char* sorted = (char*) malloc(strlen(s) + 1);  
    int idx = 0;  // sorted 문자열의 현재 위치를 가리킬 인덱스 변수

    // order 문자열에 따라 s 문자열에서 문자를 순서대로 추출후 sorted에 넣기 
    for (int i = 0; i < strlen(order); i++) {

        // s 문자열 내에 order[i] 문자가 더 이상 없을 때까지 반복
        while (s_counter.count[order[i] - 'a'] > 0) {
            sorted[idx++] = order[i];  // order의 문자를 결과 문자열에 추가
            s_counter.count[order[i] - 'a']--;  // 해당 문자의 빈도를 감소
        }
    }

    // order 문자열에 포함되지 않은 s 문자열의 나머지 문자를 추가
    for (int i = 0; i < ALPHABET_SIZE; i++) {

        // i번째 알파벳 문자가 s 문자열 내에 더 이상 없을 때까지 반복
        while (s_counter.count[i] > 0) {
            sorted[idx++] = i + 'a';  // 해당 알파벳 문자를 결과 문자열에 추가
            s_counter.count[i]--;  // 해당 문자의 빈도를 감소
        }
    }

    sorted[idx] = '\0';  // 결과 문자열의 끝에 널 문자를 추가하여 문자열을 종료
    return sorted;  // 정렬된 문자열 반환
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