/*
[숫자 리스트에서 k번째로 큰 숫자 반환하기]  C와 똑같음!
Given an integer array nums and an integer k, 
    return the kth largest element in the array.

Note that it is the kth largest element in the sorted order, 
    not the kth distinct element.

Can you solve it without sorting?

Example 1:
Input: nums = [3,2,1,5,6,4], k = 2
Output: 5

Example 2:
Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4

(base) soungmunkim@gimseongmun-ui-MacBookPro String % gcc 215_KthLargestElementNums.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
숫자 리스트를 [a,b,c,...] 형태로 입력하세요: [3,2,3,1,2,4,5,5,6]
K 값을 입력하세요: 4
K번째 큰 수: 4

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
숫자 리스트를 [a,b,c,...] 형태로 입력하세요: [3,2,1,5,6,4]
K 값을 입력하세요: 2
K번째 큰 수: 5
*/

#include <stdio.h>
#include <math.h>
#include <string.h>

// 배열에서 가장 큰 값을 찾는 함수
int findMax(int* nums, int numsSize) {
    int max = nums[0]; // 가장 큰 값을 저장할 변수를 첫 번째 원소로 초기화합니다.
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > max) { // 현재 원소가 max보다 크다면
            max = nums[i]; // max 값을 업데이트합니다.
        }
    }
    return max; // 최대값을 반환합니다.
}

// 배열에서 가장 큰 값을 제거하는 함수
void removeMax(int* nums, int* numsSize, int max) {
    int index = -1; // 제거할 값의 인덱스를 저장할 변수를 -1로 초기화합니다.
    for (int i = 0; i < *numsSize; i++) {
        if (nums[i] == max) { // 현재 원소가 max와 같다면
            index = i; // 인덱스를 저장하고 반복을 종료합니다.
            break;
        }
    }

    if (index != -1) { // 인덱스가 유효하다면
        for (int i = index; i < *numsSize - 1; i++) { // 해당 인덱스부터 배열 끝까지 순회하며
            nums[i] = nums[i + 1]; // 현재 원소를 다음 원소로 덮어씁니다.
        }
        (*numsSize)--; // 배열 크기를 감소시킵니다.
    }
}

int findKthLargest(int* nums, int numsSize, int k) {
    for (int i = 0; i < k - 1; i++) { // k-1번 반복해서
        int max = findMax(nums, numsSize); // 배열에서 가장 큰 값을 찾고
        removeMax(nums, &numsSize, max); // 그 값을 제거합니다.
    }
    return findMax(nums, numsSize); // k번째로 큰 값을 반환합니다.
}



/*---------- 숫자 리스트 형태로 사용자에게 입력받을 경우 + int array size 처리 포함 ---------*/

int main() {
    char input[1000];
    printf("숫자 리스트를 [a,b,c,...] 형태로 입력하세요: ");
    fgets(input, sizeof(input), stdin);

    // 문자열에서 숫자만 추출하여 배열에 저장
    int nums[1000]; // 입력할 수 있는 최대 숫자 개수
    int numsSize = 0; // 입력된 숫자 개수를 세는 변수
    char* token = strtok(input, "[,] "); // 공백을 기준으로 문자열을 토큰으로 분할합니다.
    
    while (token != NULL) {
        if (sscanf(token, "%d", &nums[numsSize]) == 1) {
            numsSize++; // 정수로 변환 가능한 토큰을 찾으면 숫자 배열에 저장하고 numsSize를 증가시킵니다.
        }
        token = strtok(NULL, "[,] "); // 다음 토큰을 찾습니다.
    }

    int k;
    printf("K 값을 입력하세요: ");
    scanf("%d", &k); // 사용자로부터 K 값을 입력받습니다.

    int result = findKthLargest(nums, numsSize, k); // findKthLargest 함수를 호출하여 결과를 얻습니다.

    printf("K번째 큰 수: %d\n", result); // 결과를 출력합니다.

    return 0;
}



