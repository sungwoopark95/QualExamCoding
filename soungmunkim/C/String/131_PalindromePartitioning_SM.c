/*
[Palindrome Partitioning]
string이 palindrome substring으로 다 나눠질 수 있다면 그 palindrome들 각 list에 저장하기

Given a string s, partition s such that every substring of the partition is a palindrome. 
Return all possible palindrome partitioning of s.

(base) soungmunkim@gimseongmun-ui-MacBookPro String % gcc 131_PalindromePartitioning_SM.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                     
Please enter a string:  abb
["a", "b", "b"], ["a", "bb"]

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: 
kabccba
["k", "a", "b", "c", "c", "b", "a"], ["k", "a", "b", "cc", "b", "a"], ["k", "a", "bccb", "a"], ["k", "abccba"]
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 문자열이 회문인지 확인하는 함수
bool palindrome(char *s){
    char reversed_s[300] = {0}; // 문자 배열 초기화
    int n = strlen(s);
    int j = 0; // 추가된 변수

    // 문자열을 거꾸로 복사
    for(int i = n-1; i >= 0; i--){
        reversed_s[j++] = s[i];
    }
    reversed_s[j] = '\0'; // 문자열 종료

    // 원래 문자열과 거꾸로 된 문자열이 동일한지 확인
    if (strcmp(s, reversed_s) == 0){
        return true;
    }
    return false;
}

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

void palindrome_partition(char *s){
    char path[1000][100]; // 현재 경로를 저장하는 배열
    int path_count = 0;
    char result[1000][1000] = {0}; // 결과를 저장하는 배열
    int result_count = 0;
    backtrack(0, s, &path_count, path, result, &result_count);

    // // 결과 출력
    // for (int j = 0; j < result_count; j++) {
    //     printf("[");
    //     printf("%s", result[j]);
    //     printf("]");
    //     if (j != result_count - 1) {
    //         printf(", ");
    //     }
    // }
    // printf("\n");

    // 결과를 출력
    for (int j = 0; j < result_count; j++) {
        printf("[");
        char* token = strtok(result[j], ",");
        while(token) {
            printf("\"%s\"", token);
            token = strtok(NULL, ",");
            if(token) printf(", ");
        }
        printf("]");
        if (j != result_count - 1) {
            printf(", ");
        }
    }
    printf("\n");
}


int main(){
    char s[300];

    printf("Please enter a string: ");
    scanf("%s", s);
    
    palindrome_partition(s);

    return 0;
}
