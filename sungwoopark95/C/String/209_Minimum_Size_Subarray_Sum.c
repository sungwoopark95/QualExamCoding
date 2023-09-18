/*
합이 target보다 같은 subarray 가운데 길이가 가장 짧은 subarray의 길이를 반환하는 함수
Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.

Input: target = 4, nums = [1,4,4]
Output: 1

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0
*/

#include <stdio.h>
#include <limits.h> // for INT_MAX

/* ================================== Two-point window 사용하는 Chat GPT =================================== */
int min_subarray_length(int target, int nums[], int n) {
    // left: 부분 배열의 시작 인덱스
    // total: 현재 부분 배열의 합
    // min_len: target 이상의 합을 가진 최소 길이의 부분 배열 길이
    int left = 0;
    int total = 0;
    int min_len = INT_MAX;

    // nums 배열을 순회하면서 각 원소를 right로 참조
    for (int right = 0; right < n; right++) {
        // 현재 원소(nums[right])를 total에 더함
        total += nums[right];

        // 현재 부분 배열의 합(total)이 target보다 크거나 같은 경우
        while (total >= target) {
            // 최소 길이 부분 배열을 찾기 위해, 현재 부분 배열의 길이(right - left + 1)와 
            // 이전까지의 최소 길이(min_len) 중 작은 값을 선택
            if (right - left + 1 < min_len) {
                min_len = right - left + 1;
            }
            
            // 부분 배열의 합에서 가장 왼쪽 원소(nums[left])를 뺌
            total -= nums[left];
            
            // left 포인터를 오른쪽으로 이동시킴
            left++;
        }
    }

    // 최소 길이 부분 배열을 찾았다면 그 길이(min_len)를 반환하고, 찾지 못했다면 0을 반환
    return (min_len != INT_MAX) ? min_len : 0;
}

int main() {
    int nums[] = {2,3,1,2,4,3};
    int n = sizeof(nums) / sizeof(nums[0]);
    int target = 7;
    printf("%d\n", min_subarray_length(target, nums, n));
    return 0;
}
