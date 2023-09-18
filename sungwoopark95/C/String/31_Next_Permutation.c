/*
주어진 배열의 순열 중에서 다음에 오는 순열(사전식 순서로 다음 순서)을 찾아야 합니다. 
만약 주어진 배열이 사전식 순서로 가장 큰 경우(내림차순으로 정렬된 경우)에는 가장 작은 순서(오름차순으로 정렬된 경우)로 배열을 변경합니다. 
주어진 배열을 직접 변경해야 하며, 상수 시간 복잡도를 가진 추가 메모리만을 사용해야 합니다.

Example 1:
Input: nums = [1,2,3]
Output: [1,3,2]

Example 2: 
Input: nums = [3,2,1]
Output: [1,2,3]

Example 3:
Input: nums = [1,1,5]
Output: [1,5,1]
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* ================================================ permutation ================================================ */
bool contains(int** permList, int permSize, int* nums, int numsSize) {
    for (int i = 0; i < permSize; i++) {
        if (memcmp(permList[i], nums, sizeof(int) * numsSize) == 0) {
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

int permSize = 0;
void int_perm(int start, int* nums, int numsSize, int*** permList) {
    if (start == numsSize && !contains(*permList, permSize, nums, numsSize)) {
        (*permList)[permSize] = (int*) malloc(sizeof(int) * numsSize);
        memcpy((*permList)[permSize], nums, sizeof(int) * numsSize);
        permSize++;
        return;
    }

    for (int i = start; i < numsSize; i++) {
        // 현재 시작 인덱스와 루프의 인덱스 위치의 정수를 교환 (스왑)
        swap(&nums[start], &nums[i]);

        // 현재 시작 인덱스를 제외한 나머지 리스트에 대해 순열을 생성하기 위해 재귀적으로 호출
        int_perm(start + 1, nums, numsSize, permList);

        // 이전 상태로 리스트를 복원하기 위해 다시 정수 위치를 교환 (백트래킹)
        swap(&nums[start], &nums[i]);
    }
}

// 비교 함수: qsort() 함수를 위해 사용됩니다. 
// 주어진 두 개의 포인터 a와 b가 가리키는 배열을 memcmp를 이용하여 비교합니다.
int compare(const void* a, const void* b) {
    return memcmp(*(int**)a, *(int**)b, sizeof(int));
}

void nextPermutation(int* nums, int numsSize) {
    // 최대 10000개의 순열을 저장하기 위한 동적 메모리 할당. 실제 필요한 공간은 이보다 적을 수 있습니다.
    int** permList = (int**) malloc(sizeof(int*) * 10000);  

    // 주어진 배열 nums의 모든 가능한 순열을 생성하여 permList에 저장합니다.
    int_perm(0, nums, numsSize, &permList);

    // permList에 저장된 순열들을 오름차순으로 정렬합니다.
    qsort(permList, permSize, sizeof(int*), compare);

    // permList에 저장된 순열 중 현재 nums와 일치하는 순열을 찾습니다.
    for (int i = 0; i < permSize; i++) {
        if (memcmp(permList[i], nums, sizeof(int) * numsSize) == 0) {
            // 만약 nums가 마지막 순열이면 첫 번째 순열로 변경합니다.
            if (i == permSize - 1) {
                memcpy(nums, permList[0], sizeof(int) * numsSize);
            } else {
                // 아니라면 다음 순열로 변경합니다.
                memcpy(nums, permList[i + 1], sizeof(int) * numsSize);
            }
            break;
        }
    }
}
/* ================================================ two pointer ================================================ */
/*
Example
nums = [3,2,1]
i = 1 # len(nums) - 2
nums[i] = 2, nums[i+1] = 1 -> while loop 들어감, i -> 0
nums[i] = 3, nums[i+1] = 2 -> while loop 들어감, i -> -1, while 종료
i < 0이므로 if문 들어가지 않고 통과
nums[i+1:] = nums[0:] = nums 자체
nums[i+1:] = sorted(nums[i+1:]) -> nums = [1,2,3]
*/
// nums 배열의 다음 순열을 찾는 함수
void next_permutation(int* nums, int numsSize) {
    // i를 배열의 끝에서 두 번째 원소의 인덱스로 초기화
    int i = numsSize - 2;

    // nums[i]가 nums[i+1]보다 크거나 같은 동안 계속 뒤로 이동
    // 이는 순열의 다음 위치를 찾기 위한 과정
    while (i >= 0 && nums[i] >= nums[i + 1]) {
        i--;
    }

    // i가 0 이상인 경우, 즉 내림차순이 깨진 위치가 있는 경우
    if (i >= 0) {
        int j = numsSize - 1;
        // j를 뒤에서부터 찾아서 nums[j]가 nums[i]보다 큰 첫 번째 위치를 찾음
        while (nums[j] <= nums[i]) {
            j--;
        }
        // nums[i]와 nums[j]의 위치를 바꿈
        swap(&nums[i], &nums[j]);
    }

    // i 뒤의 원소들을 오름차순으로 정렬하기 위해 위치를 바꾸는 과정
    int start = i + 1, end = numsSize - 1;
    while (start < end) {
        swap(&nums[start], &nums[end]);
        start++;
        end--;
    }
}
/* ============================================================================================================= */

int main() {
    int nums[] = {1, 1, 5};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    next_permutation(nums, numsSize);

    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}
