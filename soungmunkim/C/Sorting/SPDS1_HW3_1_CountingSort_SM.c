/*
[Counting sort 구현]
1. 가장 작은 데이터부터 가장 큰 데이터까지의 범위가 모두 담길 수 있는 리스트를 생성
2. 데이터를 하나씩 확인하며 데이터의 값과 동일한 인덱스의 데이터를 1씩 증가
3. 증가된 리스트에서 0인 값을 제외하고, 인덱스를 인덱스 값만큼 출력
*/

#include <stdio.h>
#include <stdlib.h> //calloc, free 동적할당 할 때 써야함

void counting_sort(int arr[], int n){
    // 주어진 배열에서 가장 큰 값과 가장 작은 값을 찾습니다.
    int max_val = arr[0];
    int min_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) max_val = arr[i];
        if (arr[i] < min_val) min_val = arr[i];
    }

    // 카운팅 배열의 크기를 결정합니다. (최대값 - 최소값 + 1)
    // 이후 카운팅 배열을 0으로 초기화합니다.
    int count_size = max_val - min_val + 1;
    // calloc은 메모리 할당 + 0으로 초기화까지 함 (malloc은 메모리 할당만 함)
    int* count_array = (int*)calloc(count_size, sizeof(int));

    // 주어진 배열의 각 숫자를 순회하며, 해당 숫자의 발생 횟수를 카운팅 배열에 저장합니다.
    for (int i = 0; i < n; i++) {
        count_array[arr[i] - min_val]++;
    }

    // 카운팅 배열의 정보를 사용하여 입력 배열을 정렬합니다.
    int idx = 0;
    for (int i = 0; i < count_size; i++) {
        while (count_array[i] > 0) {
            // 카운팅 배열의 인덱스와 최소값을 더하여 실제 숫자를 구합니다.
            arr[idx] = i + min_val;
            idx++;
            count_array[i]--;
        }
    }

    // 동적 할당한 메모리 해제
    free(count_array);
}

int main() {
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    counting_sort(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
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

    // 배열을 counting_sort 함수를 사용하여 정렬
    counting_sort(arr, n);

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

    counting_sort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
*/