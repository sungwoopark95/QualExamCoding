/*
[Quick Sort 구현]

1. 기준이 되는 데이터인 pivot을 하나 선택한다.
    일반적으로 가장 많이 사용되는 것은 주어진 array의 첫 번째 요소이다. (array[0])
2. pivot을 기준으로 pivot 보다 작은 데이터와 pivot보다 큰 데이터로 구분한다.
3. pivot을 pivot보다 작은 데이터와 pivot보다 큰 데이터 사이에 위치시키면 pivot의 위치가 결정된다.
    [pivot 이하] [pivot] [pivot 초과]
4. pivot보다 작은 데이터와 pivot보다 큰 데이터 각각에서 동일하게 퀵 정렬을 수행한다. (재귀적으로)

g++ -std=c++17 SPDS1_HW3_1_QuickSort_SM.cpp -o QuickSort
*/

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

// start, end는 index임
int partition(vector<int>& arr, int start, int end){
    // 피벗을 기준으로 배열을 분할하고, 피벗의 위치를 반환합니다.
    int pivot = start;
    int left = start+1;
    int right = end;

    while(left <= right){
        // 피벗보다 큰 원소를 찾을 때까지 left를 증가
        while(left <= end && arr[left] <= arr[pivot]){
            left++;
        }
        // # 피벗보다 작은 원소를 찾을 때까지 right를 감소
        while(right > start && arr[right] >= arr[pivot]){
            right--;
        }
        // left와 right가 교차했다면, right와 피벗 위치의 원소를 교환
        if(left > right){
            swap(arr[right], arr[pivot]);
        }
        else {  // 그렇지 않다면, left와 right 위치의 원소를 교환
            swap(arr[right], arr[left]);
        }
    }
    return right;
}

void quick_sort(vector<int>& arr, int start, int end){
    // 주어진 배열을 quick sort 함
    if(start >= end) { return; }
    
    int pivot = partition(arr, start, end); // 피벗 위치를 얻음
    quick_sort(arr, start, pivot-1); // 왼쪽 부분 리스트 정렬
    quick_sort(arr, pivot+1, end); // 오른쪽 부분 리스트 정렬
}


int main() {
    vector<int> arr = {12, 11, 13, 5, 6};
    int n = arr.size();

    quick_sort(arr, 0, n-1);

    printf("Sorted array: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

/*사용자에게 input으로 sorting 하고 싶은 인자를 받았을 때

int main() {
    char input[1000];  // 사용자 입력을 저장할 문자열 배열
    int arr[1000];     // 숫자들을 저장할 배열
    int n = 0;         // 배열의 크기를 저장할 변수

    // 사용자로부터 정렬할 숫자들을 입력받음
    printf("정렬할 숫자들을 공백으로 구분하여 입력해주세요:\n");
    fgets(input, sizeof(input), stdin);

    // 입력받은 문자열을 공백을 기준으로 나누어 숫자로 변환하고 배열에 저장
    char *token = strtok(input, " ");
    while (token) {
        arr[n++] = atoi(token);  // 문자열을 숫자로 변환하여 배열에 저장
        token = strtok(NULL, " ");
    }

    // 배열을 quick_sort 함수를 사용하여 정렬
    quick_sort(arr, n);

    // 정렬된 배열 출력
    printf("정렬된 배열: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
*/


/* list형태로 사용자에게 input으로 받았을 때
#define MAX_SIZE 100
int main() {
    char input[MAX_SIZE];
    int arr[MAX_SIZE];
    int n = 0; // 배열의 크기

    printf("Enter the list of numbers in the format [a,b,c,...]: ");
    fgets(input, sizeof(input), stdin);

    // 입력된 문자열 처리
    char* token = strtok(input, "[,]"); // '[' 또는 ',' 또는 ']'를 기준으로 문자열 분리
    while (token) {
        arr[n++] = atoi(token); // 문자열을 숫자로 변환하여 배열에 저장
        token = strtok(NULL, "[,]");
    }

    quick_sort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
*/