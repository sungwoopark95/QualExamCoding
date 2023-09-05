/*
두 행렬 곱셈하기
*/

#include <stdio.h>
#include <stdlib.h>

// 행렬의 최대 크기를 정의합니다.
#define MAX_SIZE 100

// 두 행렬의 곱셈을 수행하는 함수
void matrixMultiplication(int A[MAX_SIZE][MAX_SIZE], int rowsA, int colsA, int B[MAX_SIZE][MAX_SIZE], int rowsB, int colsB, int result[MAX_SIZE][MAX_SIZE]) {
    // 행렬 곱셈의 조건을 검사합니다. 행렬 A의 열의 수와 행렬 B의 행의 수가 같아야 합니다.
    if (colsA != rowsB) {
        printf("행렬 A의 열 수와 행렬 B의 행 수가 일치하지 않습니다. 행렬 곱셈을 수행할 수 없습니다.\n");
        exit(1); // 조건에 맞지 않으면 프로그램을 종료합니다.
    }

    // 행렬 곱셈을 수행합니다.
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0; // 결과 행렬의 해당 위치를 초기화합니다.
            for (int k = 0; k < colsA; k++) {
                // A의 i번째 행의 원소와 B의 j번째 열의 원소를 곱하여 결과 행렬의 (i, j) 위치에 더합니다.
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // 테스트용 행렬 A와 B를 정의합니다.
    int A[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    int B[3][2] = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    // 행렬 A와 B의 행과 열의 크기를 정의합니다.
    int rowsA = 2;
    int colsA = 3;
    int rowsB = 3;
    int colsB = 2;

    // 결과를 저장할 행렬을 정의합니다.
    int result[MAX_SIZE][MAX_SIZE];

    // 두 행렬의 곱셈 함수를 호출하여 결과를 얻습니다.
    matrixMultiplication(A, rowsA, colsA, B, rowsB, colsB, result);

    // 결과 행렬을 화면에 출력합니다.
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
