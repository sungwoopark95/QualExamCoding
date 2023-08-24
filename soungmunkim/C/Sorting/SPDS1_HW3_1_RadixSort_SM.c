/*
[Radix sort 구현]
Radix Sort는 낮은 자리수부터(일의자리, 십의자리, 등) 비교하여 정렬해 간다는 것을 기본 개념으로 정렬하는 알고리즘이다.
비교 연산을 하지 않으며 정렬 속도가 빠르지만 데이터 전체 크기에 기수 테이블의 크기만한 메모리가 더 필요하다. (공간 복잡도가 높아진다.)
*/

#include <stdio.h>

// 주어진 자릿수에 따라 배열을 분류하는 함수
void countingSort(int arr[], int n, int exp) {
    int output[n];  // 정렬된 결과를 저장할 임시 배열
    int i, count[10] = {0};  // 0부터 9까지의 숫자를 세기 위한 카운트 배열 초기화

    // 해당 자릿수의 숫자를 기반으로 count 배열 업데이트
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // count 배열을 업데이트하여 실제 위치 정보를 포함하도록 함
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // 원래 배열의 값을 출력 배열에 복사
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // 출력 배열의 값을 원래 배열로 복사
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// 레디스 정렬 메인 함수
void radix_sort(int arr[], int n) {
    // 주어진 배열에서 최대값을 찾음
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    // 최대값의 각 자릿수에 대해 countingSort를 호출
    // (1의 자리부터 시작하여 최대 자릿수까지 반복)
    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSort(arr, n, exp);
}



int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    radix_sort(arr, n);

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

    // 배열을 radix_sort 함수를 사용하여 정렬
    radix_sort(arr, n);

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

    radix_sort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
*/

