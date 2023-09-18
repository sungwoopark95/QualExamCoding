#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ===================== 더해서 n이 되는 모든 k개의 정수 조합을 찾는 함수 ===================== */
// 2차원 배열과 그 배열의 크기를 나타내는 구조체 정의
typedef struct {
    int** data; // 2차원 정수 배열
    int size;   // 배열의 크기 (첫 번째 차원)
} TwoDArray;

// 주어진 n과 k에 대해 n의 합으로 k개의 숫자를 구성하는 모든 조합을 찾는 함수
TwoDArray sum_comb(int n, int k, int* current, int currentSize, int start) {
    // n이 0이고 k도 0일 때 현재 조합을 결과로 반환
    if (k == 0 && n == 0) {
        TwoDArray result;
        result.data = (int**)malloc(sizeof(int*));
        result.data[0] = (int*)malloc(currentSize * sizeof(int));
        for (int i = 0; i < currentSize; i++) {
            result.data[0][i] = current[i];
        }
        result.size = 1;
        return result;
    }
    // k가 0이거나 n이 음수일 때 빈 결과 반환
    if (k == 0 || n < 0) {
        TwoDArray result = { NULL, 0 };
        return result;
    }

    // 결과를 저장할 변수 초기화
    TwoDArray result = { NULL, 0 };
    
    // start부터 n까지의 숫자를 하나씩 현재 조합에 추가해보면서 재귀 호출
    for (int i = start; i <= n; ++i) {
        current[currentSize] = i;
        
        // 재귀 호출로 부분 문제 해결
        TwoDArray temp = sum_comb(n - i, k - 1, current, currentSize + 1, i);

        // 현재 결과 배열의 크기를 재할당하여 확장
        result.data = (int**)realloc(result.data, (result.size + temp.size) * sizeof(int*));
        
        // 재귀 호출로 얻은 결과를 현재 결과에 추가
        for (int j = 0; j < temp.size; j++) {
            result.data[result.size + j] = (int*)malloc(currentSize * sizeof(int));
            for (int k = 0; k < currentSize; k++) {
                result.data[result.size + j][k] = temp.data[j][k];
            }
            // 임시로 사용된 메모리 해제
            free(temp.data[j]);
        }
        // 현재 결과 배열의 크기 업데이트
        result.size += temp.size;
        
        // 임시로 사용된 메모리 해제
        free(temp.data);
    }

    // 최종 결과 반환
    return result;
}
/* ==================================================================================== */

/* ==================================== My Code ======================================= */
// 주어진 배열에 특정 값이 있는지 확인하는 함수
bool contains(int* array, int size, int value) {
    for (int i = 0; i < size; i++) { // 배열 전체를 순회
        if (array[i] == value) { // 만약 원하는 값이 배열에 있으면
            return true; // true 반환
        }
    }
    return false; // 배열에 값이 없으면 false 반환
}

// 두 배열이 동일한지 확인하는 함수
bool equalArrays(int* arr1, int* arr2, int size) {
    for (int i = 0; i < size; i++) { // 배열의 모든 원소를 순회
        if (arr1[i] != arr2[i]) { // 두 배열의 원소가 다르면
            return false; // false 반환
        }
    }
    return true; // 모든 원소가 동일하면 true 반환
}

// candidates 배열의 숫자들을 사용하여 target 합계를 만들 수 있는 조합을 찾는 함수
TwoDArray combinationSum(int* candidates, int candidatesSize, int target) {
    TwoDArray result = { NULL, 0 }; // 결과를 저장할 구조체 초기화
    int current[1000]; // 현재 조합을 저장할 배열

    // 1부터 target까지 각 i 값에 대해 조합을 찾음
    for (int i = 1; i <= target; ++i) {
        // target의 합으로 i개의 숫자로 구성된 모든 조합을 찾는다
        TwoDArray combinations = sum_comb(target, i, current, 0, 1);
        
        // 찾은 조합들 중에서 candidates에 있는 숫자만 사용된 조합을 결과에 추가
        for (int j = 0; j < combinations.size; j++) {
            bool flag = true; // 현재 조합이 유효한지 나타내는 플래그
            for (int k = 0; k < i; k++) {
                // 조합의 모든 숫자가 candidates에 있는지 확인
                if (!contains(candidates, candidatesSize, combinations.data[j][k])) {
                    flag = false; // 없는 숫자가 있다면 플래그를 false로 설정
                    break;
                }
            }
            if (flag) { // 현재 조합이 유효하면
                bool alreadyPresent = false; // 조합이 이미 결과에 있는지 나타내는 플래그
                for (int l = 0; l < result.size; l++) {
                    // 현재 조합이 결과에 이미 있는지 확인
                    if (equalArrays(result.data[l], combinations.data[j], i)) {
                        alreadyPresent = true;
                        break;
                    }
                }
                // 조합이 결과에 없으면 추가
                if (!alreadyPresent) {
                    result.data = (int**)realloc(result.data, (result.size + 1) * sizeof(int*));
                    result.data[result.size] = (int*)malloc(i * sizeof(int));
                    for (int m = 0; m < i; m++) {
                        result.data[result.size][m] = combinations.data[j][m];
                    }
                    result.size++;
                }
            }
            free(combinations.data[j]); // 메모리 해제
        }
        free(combinations.data); // 메모리 해제
    }

    return result; // 최종 결과 반환
}
/* ===================================================================================== */

int main() {
    int candidates[] = { 2 };
    int candidatesSize = sizeof(candidates) / sizeof(int);
    int target = 1;

    TwoDArray result = combinationSum(candidates, candidatesSize, target);
    for (int i = 0; i < result.size; i++) {
        for (int j = 0; j < candidatesSize; j++) {
            printf("%d ", result.data[i][j]);
        }
        printf("\n");
        free(result.data[i]);
    }
    free(result.data);
    return 0;
}
