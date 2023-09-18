#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 임시 저장소의 최대 크기 정의
#define MAX_SIZE 1000
#define MAX_STRING_SIZE 1000

// 함수 프로토타입 선언 (함수의 시그니처만 선언)
char** str_perm(char* s, int* returnSize);
void backtrack_str(char* s, int start, char** permutation_lst, int* idx);
void swap(char* a, char* b);
int** int_perm(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);
void backtrack_int(int* nums, int numsSize, int start, int** permutation_lst, int* idx);
void swap_int(int* a, int* b);

/* ================== 주어진 문자열의 모든 순열을 반환하는 함수 ================== */
// 주어진 문자열의 모든 순열을 반환하는 함수
char** str_perm(char* s, int* returnSize) {
    char** permutation_lst = (char**)malloc(MAX_SIZE * sizeof(char*));
    int idx = 0;
    backtrack_str(s, 0, permutation_lst, &idx);
    *returnSize = idx;
    return permutation_lst;
}

// 문자열의 순열을 위한 백트래킹 함수
void backtrack_str(char* s, int start, char** permutation_lst, int* idx) {
    if (start == strlen(s)) {
        permutation_lst[*idx] = (char*)malloc((strlen(s) + 1) * sizeof(char));
        strcpy(permutation_lst[*idx], s);
        (*idx)++;
        return;
    }

    for (int i = start; i < strlen(s); ++i) {
        swap(&s[start], &s[i]);
        backtrack_str(s, start + 1, permutation_lst, idx);
        swap(&s[start], &s[i]);
    }
}

// 문자 위치를 교환하는 함수
void swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}
/* ====================================================================== */

/* ================ 주어진 정수 리스트의 모든 순열을 반환하는 함수 ================= */
int** int_perm(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** permutation_lst = (int**)malloc(MAX_SIZE * sizeof(int*));
    *returnColumnSizes = (int*)malloc(MAX_SIZE * sizeof(int));
    int idx = 0;

    backtrack_int(nums, numsSize, 0, permutation_lst, &idx);

    *returnSize = idx;
    for (int i = 0; i < idx; ++i) {
        (*returnColumnSizes)[i] = numsSize;
    }

    return permutation_lst;
}

// 정수 리스트의 순열을 위한 백트래킹 함수
void backtrack_int(int* nums, int numsSize, int start, int** permutation_lst, int* idx) {
    if (start == numsSize) {
        permutation_lst[*idx] = (int*)malloc(numsSize * sizeof(int));
        memcpy(permutation_lst[*idx], nums, numsSize * sizeof(int));
        (*idx)++;
        return;
    }

    for (int i = start; i < numsSize; ++i) {
        swap_int(&nums[start], &nums[i]);
        backtrack_int(nums, numsSize, start + 1, permutation_lst, idx);
        swap_int(&nums[start], &nums[i]);
    }
}

// 정수 위치를 교환하는 함수
void swap_int(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
/* ====================================================================== */

int main() {
    int nums[] = {3, 2, 1};
    int returnSize;
    int* returnColumnSizes;
    
    int** result = int_perm(nums, 3, &returnSize, &returnColumnSizes);
    
    // 결과를 출력
    for (int i = 0; i < returnSize; ++i) {
        for (int j = 0; j < returnColumnSizes[i]; ++j) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
        free(result[i]);  // 할당된 메모리 해제
    }
    free(result);        // 할당된 메모리 해제
    free(returnColumnSizes); // 할당된 메모리 해제

    return 0;
}