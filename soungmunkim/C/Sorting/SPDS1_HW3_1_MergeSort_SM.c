/*
[Merge Sort 구현]
하나의 리스트를 두 개의 균등한 크기로 분할하고 분할된 부분 리스트를 정렬한 다음, 
    두 개의 정렬된 부분 리스트를 합하여 전체가 정렬된 리스트가 되게 하는 방법

1. 분할(Divide): 주어진 배열을 두 개의 동일한 크기의 하위 배열로 분할합니다. 
    만약 배열의 크기가 홀수라면, 한 배열은 추가 요소를 포함할 수 있습니다.
2. 정복(Conquer): 두 개의 하위 배열을 재귀적으로 병합 정렬로 정렬합니다.
3. 병합(Merge): 두 개의 정렬된 하위 배열을 병합하여 하나의 정렬된 배열을 만듭니다.
*/

#include <stdio.h>

// start, mid, last는 인덱스래유
void Merge(int arr[], int start, int mid, int last){
    int k = start;
    int len1 = (mid+1) - start; // 첫 번째 부분 리스트의 길이
    int len2 = last - mid; // 두 번째 부분 리스트의 길이
    int sub1[len1]; // 첫 번째 부분 리스트를 저장할 배열
    int sub2[len2]; // 두 번째 부분 리스트를 저장할 배열

    // 첫 번째 부분 리스트의 원소들을 sub1에 복사
    for (int i=0;i<len1;i++) { 
        sub1[i] = arr[start+i]; 
    }
    // 두 번째 부분 리스트의 원소들을 sub2에 복사
    for (int j=0; j<len2; j++) { 
        sub2[j] = arr[mid+1+j]; 
    }
    
    int m = 0; int l = 0;    
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
void MergeHelp(int* arr, int start, int last) {
    if (start == last) { return; } // 부분 리스트의 길이가 1이면 반환
    int mid = (start+last) / 2; // 중간 위치 계산
    MergeHelp(arr, start, mid); // 첫 번째 부분 리스트 정렬
    MergeHelp(arr, mid+1, last); // 두 번째 부분 리스트 정렬
    
    Merge(arr, start, mid, last); // 두 부분 리스트를 병합
}

// 병합 정렬 메인 함수
void MergeSort(int* arr, int len) {
    MergeHelp(arr, 0, len-1); // 병합 정렬 시작
}

int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    MergeSort(arr, n);

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

    // 배열을 MergeSort 함수를 사용하여 정렬
    MergeSort(arr, n);

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

    MergeSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
*/