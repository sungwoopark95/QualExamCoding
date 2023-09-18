#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

/* ========================= 리스트에서 정해진 길이만큼의 조합을 만드는 함수 ========================= */
void backtrack_list_comb(int* nums, int numsSize, int start, int length, int* path, int pathSize, int*** output, int* outputSize) {
    if (pathSize == length) {
        (*output)[*outputSize] = malloc(length * sizeof(int));
        memcpy((*output)[*outputSize], path, length * sizeof(int));
        (*outputSize)++;
        return;
    }

    for (int i = start; i < numsSize; i++) {
        path[pathSize] = nums[i];
        backtrack_list_comb(nums, numsSize, i + 1, length, path, pathSize + 1, output, outputSize);
    }
}

// 리스트에서 정해진 길이만큼의 조합을 만드는 함수
int** list_comb(int* nums, int numsSize, int length, int* returnSize) {
    if (length > numsSize) {
        printf("length cannot be greater than the length of nums\n");
        *returnSize = 0;
        return NULL;
    }

    int** output = malloc(MAX_SIZE * sizeof(int*));
    *returnSize = 0;
    int path[MAX_SIZE];
    int pathSize = 0;

    backtrack_list_comb(nums, numsSize, 0, length, path, pathSize, &output, returnSize);

    return output;
}
/* ======================================================================================= */

/* ========================= 문자열에서 정해진 길이만큼의 조합을 만드는 함수 ========================= */
void backtrack_str_comb(char* nums, int start, int length, char* path, int pathSize, char*** output, int* outputSize) {
    if (pathSize == length) {
        path[pathSize] = '\0'; // 문자열 종료
        (*output)[*outputSize] = strdup(path); // 문자열 복사
        (*outputSize)++;
        return;
    }

    for (int i = start; i < strlen(nums); i++) {
        path[pathSize] = nums[i];
        backtrack_str_comb(nums, i + 1, length, path, pathSize + 1, output, outputSize);
    }
}

// 문자열에서 정해진 길이만큼의 조합을 만드는 함수
char** str_comb(char* nums, int length, int* returnSize) {
    if (length > strlen(nums)) {
        printf("length cannot be greater than the length of nums\n");
        *returnSize = 0;
        return NULL;
    }

    char** output = malloc(MAX_SIZE * sizeof(char*));
    *returnSize = 0;
    char path[MAX_SIZE];
    int pathSize = 0;

    backtrack_str_comb(nums, 0, length, path, pathSize, &output, returnSize);

    return output;
}
/* ======================================================================================= */

/* ======================== 주어진 정수 리스트의 모든 순열을 반환하는 함수 ========================== */
int** backtrack_sum_comb(int n, int k, int start, int* returnSize) {
    if (k == 0 && n == 0) {
        int** result = malloc(sizeof(int*));
        result[0] = malloc(0); // Empty combination
        *returnSize = 1;
        return result;
    }

    if (k == 0 || n < 0) {
        *returnSize = 0;
        return NULL;
    }

    int** totalResult = malloc(MAX_SIZE * sizeof(int*));
    *returnSize = 0;

    for (int i = start; i <= n; i++) {
        int subSize;
        int** subResult = backtrack_sum_comb(n - i, k - 1, i, &subSize);

        for (int j = 0; j < subSize; j++) {
            totalResult[*returnSize] = malloc(k * sizeof(int));
            totalResult[*returnSize][0] = i;
            memcpy(totalResult[*returnSize] + 1, subResult[j], (k - 1) * sizeof(int));
            (*returnSize)++;
        }

        for (int j = 0; j < subSize; j++) {
            free(subResult[j]);
        }
        free(subResult);
    }

    return totalResult;
}

// 더해서 n이 되는 모든 k개의 정수 조합을 찾는 함수
int** sum_comb(int n, int k, int* returnSize) {
    return backtrack_sum_comb(n, k, 1, returnSize);
}
/* ====================================================================================== */

int main() {
    // 예제 테스트
    int nums[] = {1, 2, 3};
    int returnSize;
    int** result = list_comb(nums, 3, 2, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
        free(result[i]);
    }
    free(result);

    int strSize;
    char** strResult = str_comb("str", 2, &strSize);
    for (int i = 0; i < strSize; i++) {
        printf("%s ", strResult[i]);
        free(strResult[i]);
    }
    printf("\n");
    free(strResult);

    int sumSize;
    int** sumResult = sum_comb(4, 3, &sumSize);
    for (int i = 0; i < sumSize; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", sumResult[i][j]);
        }
        printf("\n");
        free(sumResult[i]);
    }
    free(sumResult);

    return 0;
}
