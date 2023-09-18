/*
주어진 array에서 "연결된 가장 짧은 subarray"를 찾되, 해당 subarray만 정렬하면 전체 array가 정렬되어야 한다.

Input: nums = [2,6,4,8,10,9,15]
Output: 5
Explanation: [6, 4, 8, 10, 9]만 정렬하면 전체 array가 정렬된다.

Input: nums = [1,2,3,4]
Output: 0

Input: nums = [1]
Output: 0
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Merge(int arr[], int start, int mid, int last){
    int k = start;
    int len1 = (mid+1) - start; // 첫 번째 부분 리스트의 길이
    int len2 = last - mid; // 두 번째 부분 리스트의 길이
    int sub1[len1]; // 첫 번째 부분 리스트를 저장할 배열
    int sub2[len2]; // 두 번째 부분 리스트를 저장할 배열

    // 첫 번째 부분 리스트의 원소들을 sub1에 복사
    for (int i=0; i<len1; i++) { 
        sub1[i] = arr[start+i]; 
    }

    // 두 번째 부분 리스트의 원소들을 sub2에 복사
    for (int j=0; j<len2; j++) { 
        sub2[j] = arr[mid+1+j]; 
    }

    int m=0; int l=0;
    // sub1과 sub2의 원소들 중 작은 값을 arr에 병합
    while (m < len1 && l < len2) {
        if (sub1[m] > sub2[l]) { 
            arr[k] = sub2[l++]; 
        } else { 
            arr[k] = sub1[m++]; 
        }
        k++;
    }

    // sub1의 모든 원소가 병합되었으면, sub2의 나머지 원소들을 arr에 복사
    if (m == len1) {
        for (int x=l; x<len2; x++) { 
            arr[k++] = sub2[x]; 
        }
    } 
    // sub2의 모든 원소가 병합되었으면, sub1의 나머지 원소들을 arr에 복사
    else {
        for (int x=m; x<len1; x++) { 
            arr[k++] = sub1[x]; 
        }
    }
}

// 재귀적인 병합 정렬 도우미 함수
void MergeHelp(int arr[], int start, int last) {
    if (start == last) { return; } // 부분 리스트의 길이가 1이면 반환
    int mid = (start+last) / 2; // 중간 위치 계산
    MergeHelp(arr, start, mid); // 첫 번째 부분 리스트 정렬
    MergeHelp(arr, mid+1, last); // 두 번째 부분 리스트 정렬
    
    Merge(arr, start, mid, last); // 두 부분 리스트를 병합
}

// 병합 정렬 메인 함수
void MergeSort(int arr[], int n, int output[]) {
    for (int i=0; i<n; i++) {
        output[i] = arr[i];
    }
    MergeHelp(output, 0, n-1); // 병합 정렬 시작
}

int findUnsortedSubarray(int nums[], int size) {
    int sorted[size];
    MergeSort(nums, size, sorted);
    if (size == 1) {
        return 0;
    }

    bool isSorted = true;
    for (int i = 0; i < size; i++) {
        if (nums[i] != sorted[i]) {
            isSorted = false;
            break;
        }
    }
    if (isSorted) {
        return 0;
    }

    int max_idx = -1;
    int min_idx = 10000000;
    for (int i=0; i<size; i++) {
        if (nums[i] != sorted[i]) {
            if (min_idx > i) { min_idx = i; }
            if (max_idx < i) { max_idx = i; }
        }
    }

    printf("%d, %d\n", max_idx, min_idx);
    return (max_idx - min_idx) + 1;
}

int main() {
    char input[1000];
    int arr[100];
    int size = 0;
    int num;

    printf("Enter the list of numbers in the format [a,b,c,...]: ");
    fgets(input, sizeof(input), stdin);

    char* token = strtok(input, "[], \n");
    while (token != NULL) {
        sscanf(token, "%d", &num);
        arr[size++] = num;
        token = strtok(NULL, "[], \n");
    }

    printf("%d\n", findUnsortedSubarray(arr, size));

    return 0;
}
