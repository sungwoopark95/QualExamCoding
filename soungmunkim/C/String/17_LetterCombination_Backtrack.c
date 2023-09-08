/*
[숫자패드에 letters가 써있는 핸드폰 생각하기]
[ 해당 숫자패드의 letters의 모든 조합 리턴하는 방식]

Given a string containing digits from 2-9 inclusive, 
return all possible letter combinations that the number could represent. 
Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. 
Note that 1 does not map to any letters.


Enter a sequence of digits (2-9): 23
["ad","ae","af","bd","be","bf","cd","ce","cf"]

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a sequence of digits (2-9): ""
[]

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a sequence of digits (2-9): 2
["a","b","c"]

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test 23                                                
["ad","ae","af","bd","be","bf","cd","ce","cf"]

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test ""
[]

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test 2 
["a","b","c"]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 전화기 버튼에 해당하는 문자들을 정의합니다.
char* phone[10] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

char** result;  // 결과로 나올 문자 조합들을 저장할 포인터 배열입니다.
int resultSize = 0;  // 현재까지 저장된 결과의 개수를 표시합니다.

// 백트래킹 방식으로 모든 문자 조합을 찾는 함수입니다.
void backtrack(char* combination, char* next_digit) {
    // 조합이 완성된 경우 (모든 숫자를 다 처리한 경우)
    if (*next_digit == '\0') {
        result[resultSize] = (char*)malloc(strlen(combination) + 1);  // 결과 저장 공간 할당
        strcpy(result[resultSize], combination);  // 결과를 배열에 복사
        resultSize++;  // 결과 개수 증가
        return;
    }
    int index = *next_digit - '0';  // 현재 처리할 숫자를 index로 변환
    // 현재 숫자에 해당하는 문자 각각에 대해서 다음 숫자로 넘어가며 재귀적으로 탐색
    for (int i = 0; i < strlen(phone[index]); i++) {
        char new_combination[strlen(combination) + 2];  // 새로운 조합을 저장할 배열
        strcpy(new_combination, combination);  // 기존의 조합 복사
        strncat(new_combination, &phone[index][i], 1);  // 새 문자 추가
        backtrack(new_combination, next_digit + 1);  // 다음 숫자로 재귀
    }
}

// 주어진 숫자들에 대한 모든 문자 조합을 반환하는 함수입니다.
char** letterCombinations(char* digits, int* returnSize) {
    resultSize = 0;
    result = (char**)malloc(1000 * sizeof(char*));  // 임의로 크게 메모리를 할당

    // 입력 값이 없거나 길이가 0인 경우 처리
    if (!digits || strlen(digits) == 0) {
        *returnSize = 0;
        return NULL;
    }
    // 백트래킹 시작
    backtrack("", digits);
    *returnSize = resultSize;  // 결과 개수 설정

    return result;  // 결과 반환
}

// 메인 함수
int main() {
    char input[100];  // 사용자 입력을 저장할 배열
    
    printf("Enter a sequence of digits (2-9): ");
    scanf("%s", input);  // 사용자로부터 입력 받기

    bool hasInvalidDigit = false;

    // 입력된 문자열에서 2 미만이거나 9 초과인 문자가 있는지 확인
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] < '2' || input[i] > '9') {
            hasInvalidDigit = true;
            break;
        }
    }

    // 잘못된 문자가 있으면 [] 출력 후 프로그램 종료
    if (hasInvalidDigit) {
        printf("[]\n");
        return 1;
    }

    int returnSize = 0;
    char** combinations = letterCombinations(input, &returnSize);  // 문자 조합을 찾기

    // 결과 출력
    printf("[");
    for (int i = 0; i < returnSize; i++) {
        printf("\"%s\"", combinations[i]);
        if (i < returnSize - 1) {
            printf(", ");
        }
        free(combinations[i]);  // 할당된 메모리 해제
    }
    printf("]\n");

    free(combinations);  // 전체 결과 배열에 대한 메모리 해제
    return 0;  // 프로그램 종료
}


// /*-------- shell 에서 직접 입력받을 때 ./test 23 이렇게 넣을 경우 --------------*/
// int main(int argc, char* argv[]) {
//     // 인자 개수 확인
//     if (argc != 2) {
//         fprintf(stderr, "Usage: %s <digits>\n", argv[0]);
//         return 1;
//     }

//     char* digits = argv[1];
//     bool hasInvalidDigit = false;
//     for (int i = 0; digits[i] != '\0'; i++) {
//         if (digits[i] < '2' || digits[i] > '9') {
//             hasInvalidDigit = true;
//             break;
//         }
//     }

//     // 유효하지 않은 숫자가 있는 경우
//     if (hasInvalidDigit) {
//         printf("[]\n");
//         return 1;
//     }

//     int returnSize = 0;
//     char** combinations = letterCombinations(digits, &returnSize);

//     // 결과 출력
//     printf("[");
//     for (int i = 0; i < returnSize; i++) {
//         printf("\"%s\"", combinations[i]);
//         if (i < returnSize - 1) {
//             printf(", ");
//         }
//         free(combinations[i]);  // 할당된 메모리 해제
//     }
//     printf("]\n");

//     free(combinations);  // 전체 결과 배열에 대한 메모리 해제
//     return 0;
// }