/*
[string 거꾸로 뒤집기]
공백이 얼마나 있던 간에 뒤집었을 때는 공백 1개로 프린트되게 하게

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a sentence: the sky is blue
blue is sky the 
--------------------------------------------------------------
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a sentence: "the sky is blue"
blue is sky the 

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a sentence:   hello world  
world hello 

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a sentence: a good   example
example good a 
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

void reverseWords(char** strs){
    int strsSize = 0;
    // strs 배열의 크기를 파악합니다. (NULL을 만날 때까지 반복)
    while (strs[strsSize] != NULL) {
        strsSize++;
    }

    // 문자열이 없는 경우 빈 문자열을 반환합니다.
    if (strsSize == 0) {
        printf("");
    }
    // 거꾸로 돌면서 단어 프린트하기 
    for(int i = strsSize-1; i >= 0; i--){
        printf("%s ", strs[i]);
    }
    printf("\n");
 
}

int main() {
    char input[1000];
    // 사용자에게 문자열 배열을 입력받습니다.
    printf("Enter a sentence: ");
    fgets(input, 1000, stdin);

    input[strcspn(input, "\n")] = 0;  // 개행 문자 제거

    char* token;
    int count = 0;
    char* strs[101];  // 최대 100개의 문자열 + NULL 포인터를 저장하기 위한 배열

    // 입력 받은 문자열을 파싱하여 개별 단어를 추출합니다.
    token = strtok(input, "[\",\t\n\r ]");

    while (token != NULL) {
        strs[count] = (char*)malloc(strlen(token) + 1);
        strcpy(strs[count], token);
        count++;

        token = strtok(NULL, "[\",\t\n\r ]");
    }
    strs[count] = NULL;  // 마지막에 NULL 포인터 추가

    // 가장 긴 공통 접두사를 출력합니다.
    reverseWords(strs);

    // 동적 할당한 메모리를 해제합니다.
    for(int i = 0; i < count; i++) {
        free(strs[i]);
    }

    return 0;
}

/*-------------------- int main에 예제가 주어졌을 때 ---------------------*/
// int main() {
//     // 예제 문자열들을 저장하는 배열을 정의합니다.
//     char* examples[] = {
//         "the sky is blue",
//         "  hello world  ",
//         "a good   example",
//         NULL  // 배열의 끝을 나타내기 위한 NULL 포인터
//     };

//     // 각 예제 문자열에 대해서 처리하기 위한 반복문을 시작합니다.
//     for (int ex = 0; examples[ex] != NULL; ex++) {
//         char* token;
//         int count = 0;
//         char* strs[101]; // 파싱된 단어를 저장할 배열을 정의합니다.

//         // examples 배열에서 문자열을 복사합니다.
//         char input[1000];
//         strcpy(input, examples[ex]);

//         // 입력 받은 문자열을 파싱하여 개별 단어를 추출합니다.
//         token = strtok(input, "[\",\t\n\r ]");

//         // 단어가 NULL이 아닐 동안 반복해서 단어를 추출하고 저장합니다.
//         while (token != NULL) {
//             // 동적 메모리 할당으로 문자열의 저장 공간을 생성합니다.
//             strs[count] = (char*)malloc(strlen(token) + 1);
//             // 추출된 단어를 strs 배열에 복사합니다.
//             strcpy(strs[count], token);
//             count++; // 단어 카운트를 증가시킵니다.

//             // 다음 단어를 추출합니다.
//             token = strtok(NULL, "[\",\t\n\r ]");
//         }
//         strs[count] = NULL;  // 마지막에 NULL 포인터 추가

//         // 원래 문자열과 뒤집힌 문자열을 출력합니다.
//         printf("Original: %s\n", examples[ex]);
//         printf("Reversed: ");
//         reverseWords(strs);
//         printf("\n");

//         // 동적 할당한 메모리를 해제합니다.
//         for(int i = 0; i < count; i++) {
//             free(strs[i]);
//         }
//     }

//     return 0;
// }



