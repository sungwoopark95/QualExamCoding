/*
[word dict가 s의 segmentation이 되어야 true]
!! string replace 사용함 !!

Given a string s and a dictionary of strings wordDict, 
    return true if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times 
    in the segmentation.

Example 1:
Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:
Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as 
    "apple pen apple".
Note that you are allowed to reuse a dictionary word.

Example 3:
Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false

(base) soungmunkim@gimseongmun-ui-MacBookPro String % gcc 139_WordBreak.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                     
문자열을 입력하세요: leetcode
사전 단어를 입력하세요 (입력을 마치려면 빈 줄을 입력하세요):
leet
code

True
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
문자열을 입력하세요: applepenapple
사전 단어를 입력하세요 (입력을 마치려면 빈 줄을 입력하세요):
apple
pen

True
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
문자열을 입력하세요: catsandog
사전 단어를 입력하세요 (입력을 마치려면 빈 줄을 입력하세요):
cats
dog
sand
and
cat

False
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-------------- string replace 함수 구현 -------------------*/

// 문자열 대체 함수
char* replace(char* str, const char* find, const char* replace) {
    // 결과 문자열을 저장할 포인터
    char* result;

    // 다음 복사 위치를 나타내는 포인터
    char* ins;

    // 임시 포인터
    char* tmp;

    // 입력 문자열의 길이, 찾을 문자열의 길이, 대체할 문자열의 길이 구하기
    int len_str = strlen(str);
    int len_find = strlen(find);
    int len_replace = strlen(replace);

    // 문자열 대체 횟수
    int count = 0;

    // 대체할 문자열이 없으면 원본 문자열을 복사한 후 반환
    if (len_find == 0) {
        result = (char*)malloc(len_str + 1);
        strcpy(result, str);
        return result;
    }

    // 찾을 문자열의 등장 횟수 계산
    ins = str;
    while ((tmp = strstr(ins, find)) != NULL) {
        ins = tmp + len_find;
        count++;
    }

    // 결과 문자열을 위한 메모리 할당
    tmp = result = (char*)malloc(len_str + (len_replace - len_find) * count + 1);

    // 문자열 대체 수행
    while (count--) {
        ins = strstr(str, find);
        int len_front = ins - str;
        tmp = strncpy(tmp, str, len_front) + len_front;
        tmp = strcpy(tmp, replace) + len_replace;
        str += len_front + len_find;
    }

    // 나머지 문자열 복사
    strcpy(tmp, str);

    return result;
}
// int str size 안 쓰고 사용하는 방법
int wordBreak(char* s, char** wordDict) {
    // 이전 문자열을 가리키는 포인터
    char* prev_s = NULL;

    while (*s) {
        // 대체된 단어 수 초기화
        int replaced = 0;

        for (int i = 0; wordDict[i] != NULL; i++) {
            // 해당 단어가 문자열에 존재하는 동안 반복
            while (strstr(s, wordDict[i])) {
                // 단어를 빈 문자열로 대체
                char* new_s = replace(s, wordDict[i], "");
                if (s != new_s) {
                    // 이전 문자열이 있으면 메모리 해제
                    if (prev_s) {
                        free(prev_s);
                    }
                    prev_s = s = new_s;
                }
                replaced = 1;
            }
        }

        // 대체된 단어가 없으면 종료
        if (!replaced) {
            if (prev_s) {
                free(prev_s);
            }
            return 0;
        }
    }

    // 마지막으로 할당된 문자열 해제
    if (prev_s) {
        free(prev_s);
    }

    return 1;
}

int main() {
    // 사용자 입력을 받을 문자열
    char input[1000];

    // 문자열 입력 받기
    printf("문자열을 입력하세요: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;  // 개행 문자 제거

    // 단어 사전을 저장할 포인터 배열 초기화
    char** wordDict = NULL;
    int wordDictSize = 0;

    // 단어 입력 받기
    /* 입력받는 형태
    apple
    pen
    
    */
    printf("사전 단어를 입력하세요 (입력을 마치려면 빈 줄을 입력하세요):\n");
    while (1) {
        char word[100];
        fgets(word, sizeof(word), stdin);
        if (word[0] == '\n') {
            break;  // 빈 줄이면 입력 종료
        }
        word[strcspn(word, "\n")] = 0;  // 개행 문자 제거

        // 단어를 배열에 추가
        wordDict = (char**)realloc(wordDict, (wordDictSize + 1) * sizeof(char*));
        wordDict[wordDictSize] = (char*)malloc((strlen(word) + 1) * sizeof(char));
        strcpy(wordDict[wordDictSize], word);
        wordDictSize++;
    }

    /* 리스트 형태로 입력받을 경우 */
    // printf("문자열을 입력하세요 ([word1, word2, ...] 형식으로 입력): ");
    // fgets(input, sizeof(input), stdin);
    // input[strcspn(input, "\n")] = 0;  // 개행 문자 제거

    // char** wordDict = NULL;  // 단어 사전을 저장할 배열
    // int wordDictSize = 0;    // 단어 사전 크기

    // char* token = strtok(input, "[, ]");
    // while (token != NULL) {
    //     wordDict = (char**)realloc(wordDict, (wordDictSize + 1) * sizeof(char*));
    //     wordDict[wordDictSize] = (char*)malloc((strlen(token) + 1) * sizeof(char));
    //     strcpy(wordDict[wordDictSize], token);
    //     wordDictSize++;

    //     token = strtok(NULL, "[, ]");
    // }

    // 단어 사전의 마지막을 NULL로 설정 (탐색 종료 표시)
    wordDict = (char**)realloc(wordDict, (wordDictSize + 1) * sizeof(char*));
    wordDict[wordDictSize] = NULL;

    // 단어 대체 함수 호출
    int result = wordBreak(input, wordDict);

    // 결과 출력
    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    // 메모리 해제
    for (int i = 0; i < wordDictSize; i++) {
        free(wordDict[i]);
    }
    free(wordDict);

    return 0;
}
