/*
[주어진 정수 배열 nums에서 가능한 모든 고유한 순열을 생성하는 함수]

Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.


Example 1:
Input: nums = [1,1,2]
Output:
[[1,1,2],
 [1,2,1],
 [2,1,1]]
 
Example 2:
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]


(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                
Enter the list of integers in the format [x,y,z,...]: [1,1,2]
[DEBUG] Backtrack called with start=0
[DEBUG] Swapping nums[0]=1 with nums[0]=1
[DEBUG] Backtrack called with start=1
[DEBUG] Swapping nums[1]=1 with nums[1]=1
[DEBUG] Backtrack called with start=2
[DEBUG] Swapping nums[2]=2 with nums[2]=2
[DEBUG] Backtrack called with start=3
[DEBUG] Permutation candidate: 1 1 2 
[DEBUG] New permutation added.
[DEBUG] Swapping nums[1]=1 with nums[2]=2
[DEBUG] Backtrack called with start=2
[DEBUG] Swapping nums[2]=1 with nums[2]=1
[DEBUG] Backtrack called with start=3
[DEBUG] Permutation candidate: 1 2 1 
[DEBUG] New permutation added.
[DEBUG] Swapping nums[0]=1 with nums[1]=1
[DEBUG] Backtrack called with start=1
[DEBUG] Swapping nums[1]=1 with nums[1]=1
[DEBUG] Backtrack called with start=2
[DEBUG] Swapping nums[2]=2 with nums[2]=2
[DEBUG] Backtrack called with start=3
[DEBUG] Permutation candidate: 1 1 2 
[DEBUG] Found a duplicate permutation
[DEBUG] Swapping nums[1]=1 with nums[2]=2
[DEBUG] Backtrack called with start=2
[DEBUG] Swapping nums[2]=1 with nums[2]=1
[DEBUG] Backtrack called with start=3
[DEBUG] Permutation candidate: 1 2 1 
[DEBUG] Found a duplicate permutation
[DEBUG] Swapping nums[0]=1 with nums[2]=2
[DEBUG] Backtrack called with start=1
[DEBUG] Swapping nums[1]=1 with nums[1]=1
[DEBUG] Backtrack called with start=2
[DEBUG] Swapping nums[2]=1 with nums[2]=1
[DEBUG] Backtrack called with start=3
[DEBUG] Permutation candidate: 2 1 1 
[DEBUG] New permutation added.
[DEBUG] Swapping nums[1]=1 with nums[2]=1
[DEBUG] Backtrack called with start=2
[DEBUG] Swapping nums[2]=1 with nums[2]=1
[DEBUG] Backtrack called with start=3
[DEBUG] Permutation candidate: 2 1 1 
[DEBUG] Found a duplicate permutation
The unique permutations are:
1 1 2 
1 2 1 
2 1 1 
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PERMUTATIONS 1000
#define MAX_NUM_LENGTH 20

int result_count = 0;
int permutations[MAX_PERMUTATIONS][MAX_NUM_LENGTH];
int nums_length;

bool contains(int length, int arr[MAX_PERMUTATIONS][MAX_NUM_LENGTH], int* candidate) {
    for (int i = 0; i < length; i++) {
        if (memcmp(arr[i], candidate, nums_length * sizeof(int)) == 0) {
            printf("[DEBUG] Found a duplicate permutation\n");
            return true;
        }
    }
    return false;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void backtrack(int nums[], int start) {
    printf("[DEBUG] Backtrack called with start=%d\n", start);

    if (start == nums_length) {
        printf("[DEBUG] Permutation candidate: ");
        for(int k = 0; k < nums_length; k++) {
            printf("%d ", nums[k]);
        }
        printf("\n");

        if (!contains(result_count, permutations, nums)) {
            printf("[DEBUG] New permutation added.\n");
            memcpy(permutations[result_count], nums, nums_length * sizeof(int));
            result_count++;
        }
        return;
    }

    for (int i = start; i < nums_length; i++) {
        printf("[DEBUG] Swapping nums[%d]=%d with nums[%d]=%d\n", start, nums[start], i, nums[i]);
        swap(&nums[start], &nums[i]);
        backtrack(nums, start + 1);
        swap(&nums[start], &nums[i]);
    }
}

int main() {
    printf("Enter the list of integers in the format [x,y,z,...]: ");
    char line[1000];
    fgets(line, sizeof(line), stdin);

    char *newline = strchr(line, '\n');
    if (newline) {
        *newline = '\0';
    }

    int nums[MAX_NUM_LENGTH];
    nums_length = 0;
    char *token = strtok(line, "[], ");
    while (token) {
        nums[nums_length++] = atoi(token);
        token = strtok(NULL, "[], ");
    }

    backtrack(nums, 0);

    printf("The unique permutations are:\n");
    for (int i = 0; i < result_count; i++) {
        for (int j = 0; j < nums_length; j++) {
            printf("%d ", permutations[i][j]);
        }
        printf("\n");
    }

    return 0;
}
