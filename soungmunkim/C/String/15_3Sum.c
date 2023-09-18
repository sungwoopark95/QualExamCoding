/*
[3 Sum]
서로 다른 위치들 값 다 더해서 0이 나오는 조합 찾기

Example 1:
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.

Example 2:
Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.

Example 3:
Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
*/

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

// threeSum 함수: 주어진 배열에서 세 숫자의 합이 0이 되는 모든 고유한 조합을 찾습니다.
int** threeSum(int* nums, int numsSize, int* returnSize) {
    // 3개의 조합을 얻기 위해 list_comb 함수 호출
    int** three_comb = list_comb(nums, numsSize, 3, returnSize);

    // 최종 결과를 저장할 동적 배열 할당
    int** ans = malloc(MAX_SIZE * sizeof(int*));
    int ansSize = 0;

    // 모든 3개의 조합에 대해
    for (int i = 0; i < *returnSize; i++) {
        // 조합의 세 수의 합이 0인지 검사
        if (three_comb[i][0] + three_comb[i][1] + three_comb[i][2] == 0) {
            // 조합을 정렬하기 위한 임시 배열
            int sorted[3] = {three_comb[i][0], three_comb[i][1], three_comb[i][2]};
            // qsort를 사용하여 정렬
            qsort(sorted, 3, sizeof(int), (int(*)(const void*, const void*))strcmp);

            // 중복 조합 체크를 위한 플래그
            bool duplicate = false;
            for (int j = 0; j < ansSize; j++) {
                // 이미 추가된 조합과 현재 조합을 비교하여 중복 체크
                if (ans[j][0] == sorted[0] && ans[j][1] == sorted[1] && ans[j][2] == sorted[2]) {
                    duplicate = true;
                    break;
                }
            }

            // 중복이 아닌 경우 결과 배열에 추가
            if (!duplicate) {
                ans[ansSize] = malloc(3 * sizeof(int));
                memcpy(ans[ansSize], sorted, 3 * sizeof(int));
                ansSize++;
            }
        }
        // 조합 메모리 해제
        free(three_comb[i]);
    }

    // 조합 배열 메모리 해제
    free(three_comb);
    *returnSize = ansSize;
    return ans;
}

// printResults 함수: 주어진 결과 배열을 표준 출력에 깔끔하게 출력합니다.
void printResults(int** results, int resultsSize) {
    printf("[");
    for (int i = 0; i < resultsSize; ++i) {
        printf("[");
        // threeSum의 결과는 항상 크기가 3인 배열이므로, 3회 반복
        for (int j = 0; j < 3; ++j) {
            printf("%d", results[i][j]);
            if (j < 2) printf(", ");
        }
        printf("]");
        if (i < resultsSize - 1) printf(", ");
    }
    printf("]\n");
}
int main() {
    int nums[] = {-1, 0, 1, 2, -1, -4};
    int returnSize;
    int** results = threeSum(nums, sizeof(nums)/sizeof(int), &returnSize);
    printResults(results, returnSize);

    for (int i = 0; i < returnSize; i++) {
        free(results[i]);
    }
    free(results);

    int nums1[] = {0, 1, 1};
    results = threeSum(nums1, sizeof(nums1)/sizeof(int), &returnSize);
    printResults(results, returnSize);
    for (int i = 0; i < returnSize; i++) {
        free(results[i]);
    }
    free(results);

    int nums2[] = {0, 0, 0};
    results = threeSum(nums2, sizeof(nums2)/sizeof(int), &returnSize);
    printResults(results, returnSize);
    for (int i = 0; i < returnSize; i++) {
        free(results[i]);
    }
    free(results);

    return 0;  // 프로그램 종료
}

