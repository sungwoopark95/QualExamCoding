/*
[palindrome partitions 중에 가장 적은 cut 수 구하기]

Given a string s, 
partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: 
"aab"
After removing quotes: aab
["a", "a", "b"], ["aa", "b"]
min length: 2
min cut: 1

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: 
a 
After removing quotes: a
["a"]
min length: 1
min cut: 0

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: 
"a"
After removing quotes: a
["a"]
min length: 1
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

/*---------------------------- string 뒤집는 함수 --------------------------------*/
void reverseString(char* str) {
    int length = strlen(str);            // 문자열의 길이를 계산
    int i, j;
    char temp;

    for (i = 0, j = length - 1; i < j; i++, j--) {
        temp = str[i];                  // 임시 변수에 현재 문자 저장
        str[i] = str[j];                // 현재 문자를 뒤쪽 문자로 교체
        str[j] = temp;                  // 뒤쪽 문자를 임시 변수에 저장한 문자로 교체
    }
}


/*---------------------- 복잡한 문자열도 palindrome인지 확인 가능한 함수 -------------------------*/
// 문자열이 회문인지 판별하는 함수
bool palindrome(char* s) {
    char cleanedString[1000] = "";      // 알파벳과 숫자만 포함하는 문자열 저장
    int k = 0;
    for(int i = 0; i < strlen(s); i++) {
        if(isalnum(s[i])) {             // 현재 문자가 알파벳 또는 숫자인지 확인
            cleanedString[k++] = tolower(s[i]);  // 현재 문자를 소문자로 변환하여 cleanedString에 추가
        }
    }
    cleanedString[k] = '\0';            // 문자열의 끝을 나타내는 NULL 문자 추가

    char reversedString[1000];          // cleanedString을 뒤집어 저장할 문자열
    strcpy(reversedString, cleanedString);  // cleanedString의 내용을 reversedString에 복사
    reverseString(reversedString);      // reversedString 뒤집기

    return strcmp(cleanedString, reversedString) == 0;  // 두 문자열이 동일한지 비교하여 회문인지 반환
}

/*---------------------- Backtrack 하면서 모든 partitions 찾는 방법 -------------------------*/
// 재귀적으로 모든 회문 문자열 파티션을 찾는 함수
void backtrack(int start, char* s, int* path_count, char path[1000][100], char result[1000][1000], int* result_count){
    // 현재 위치가 문자열의 끝이라면, 결과에 path를 추가
    if (start == strlen(s)){
        for(int i = 0; i < *path_count; i++){
            strcat(result[*result_count], path[i]);
            if(i != *path_count - 1) {
                strcat(result[*result_count], ",");
            }
        }
        (*result_count)++;
        return;
    }

    // 현재 위치에서 시작하는 모든 부분 문자열에 대해
    for (int end = start; end < strlen(s); end++){
        char slice[300];
        strncpy(slice, &s[start], end-start+1);
        slice[end-start+1] = '\0'; // 문자열 종료
        
        // 현재 부분 문자열이 회문이라면
        if(palindrome(slice)){
            // 이 부분 문자열을 path에 추가
            strcpy(path[*path_count], slice);
            (*path_count)++;
            
            // 다음 부분 문자열을 위해 재귀 호출
            backtrack(end+1, s, path_count, path, result, result_count);
            
            // 백트래킹
            (*path_count)--; 
        }
    }
}

/*---------------------- partitions 프린트 + Min cut 프린트하는 함수 -------------------------*/
void palindrome_partition(char* s) {
    char path[1000][100];  // 경로를 저장하기 위한 문자열 배열
    int path_count = 0;  // 현재 경로의 수
    char result[1000][1000] = {0};  // 결과를 저장할 문자열 배열
    int result_count = 0;  // 현재 결과의 수

    backtrack(0, s, &path_count, path, result, &result_count);  // backtrack 함수를 호출하여 모든 파티션을 찾음

    // 파티션 출력
    for (int j = 0; j < result_count; j++) {
        char temp[1000];  // 토큰화를 위해 임시로 문자열을 저장할 배열
        strcpy(temp, result[j]);  // 원본 문자열 복사
        
        printf("[");
        char* token = strtok(temp, ",");  // ","를 기준으로 토큰화
        while(token) {
            printf("\"%s\"", token);  // 토큰 출력
            token = strtok(NULL, ",");
            if(token) printf(", ");  // 다음 토큰이 있으면 콤마 출력
        }
        printf("]");
        if (j != result_count - 1) {
            printf(", ");  // 마지막 파티션이 아니면 콤마 출력
        }
    }
    printf("\n");

    // 가장 짧은 파티션 찾기
    int min_len = INT_MAX;  // 최소 길이 초기값을 매우 큰 값으로 설정
    for (int i = 0; i < result_count; i++) {
        char temp[1000];  // 토큰화를 위해 임시로 문자열을 저장할 배열
        strcpy(temp, result[i]);  // 원본 문자열 복사
        
        int partition_size = 0;  // 현재 파티션의 크기
        char* token = strtok(temp, ",");
        while(token) {
            partition_size++;  // 토큰 개수 증가
            token = strtok(NULL, ",");
        }
        
        if(partition_size < min_len) {  // 현재 파티션 크기가 최소값보다 작으면
            min_len = partition_size;  // 최소값 업데이트
        }
    }

    printf("min length: %d\n", min_len);  // 최소 길이 출력
    printf("min cut: %d\n", min_len - 1);  // 최소 컷(최소 분할 횟수) 출력
}


/*---------------------- "" 쌍따옴표 제거하는 함수 -------------------------*/
// 쌍따옴표를 제거하는 함수
void removeQuotes(char* input) {
    int j = 0;
    for(int i = 0; i < strlen(input); i++) {
        if(input[i] != '"') {
            input[j++] = input[i];
        }
    }
    input[j] = '\0';
}

int main() {
    char s[1000];
    printf("Please enter a string: \n");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = 0; // 개행 문자 제거 (끝 부분 체크 후 \0넣기)

    removeQuotes(s);
    printf("After removing quotes: %s\n", s);
    
    palindrome_partition(s);

    return 0;
}