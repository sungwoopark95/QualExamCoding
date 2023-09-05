/*
[CNN 구현하기] -> 2d array인 matrix 활용법

image: m x n np array
pattern: n x n np array
stride도 감안해야 함 (Padding, Dilation 등은 없음)
    stride 기본 값인 1
m < n이거나, stride와 m, n이 정확히 맞아 떨어지지 않으면 error 출력

(base) soungmunkim@gimseongmun-ui-MacBookPro PreviousExams % gcc 2021_1_CNN.c -o CNN
(base) soungmunkim@gimseongmun-ui-MacBookPro PreviousExams % ./CNN                  
15 18 
30 35 
*/
#include <stdio.h>
#include <stdlib.h>

// 2차원 array를 동적으로 생성하는 함수
double** create2DArray(int rows, int cols) {
    // row의 크기만큼 메모리를 할당하여 2차원 배열의 첫 번째 차원 생성
    double** array = (double**)malloc(rows * sizeof(double*));
    for(int i = 0; i < rows; i++){
        // 각 row마다 col의 크기만큼 메모리를 할당하여 2차원 배열의 두 번째 차원 생성
            array[i] = (double*)malloc(cols * sizeof(double));
    }
    return array;
}

// convolution 연산을 수행하는 함수
double** conv(double** image, int m, double** pattern, int n, int stride, int* output_size){
    // 이미지가 패턴 차원보다 작은 경우
    if (m < n) {
        printf("Error: m < n\n");
        return NULL;
    }

    // stride 값을 이용하여 output size 계산
    *output_size = (m-n) / stride + 1;

    // stride 값과 m, n이 맞아 떨어지지 않을 경우, Error
    if ((m-n) % stride != 0){
        printf("Error: Incompatible stride, m, and n\n");
        return NULL;
    }

    // conv 연산의 결과를 저장할 2차원 배열을 동적으로 할당 (matrix)
    double** result = create2DArray(*output_size, *output_size);

    // 각 영역에 대해 convolution 연산 수행
    for(int i=0; i < *output_size; i++){
        for(int j=0; j < *output_size; j++){
            double sum = 0;
            // 패턴의 크기만큼 이미지의 부분과 패턴을 곱하고 그 결과를 합산함
            for(int x = 0; x < n; x++){
                for(int y = 0; y < n; y++){
                    sum += image[i*stride + x][j*stride + y] * pattern[x][y];
                }
            }
            // 합산된 결과를 ouput array에 저장
            result[i][j] = sum;
        }
    } 
    return result;
}

int main() {
    // 예제 이미지와 패턴을 선언합니다.
    int m = 5, n = 3, stride = 2;
    double* image[5] = {(double[]){1, 2, 3, 3, 3}, 
                        (double[]){4, 5, 6, 6, 6}, 
                        (double[]){7, 8, 9, 9, 9}, 
                        (double[]){10, 11, 12, 13, 13},
                        (double[]){10, 11, 12, 13, 13}};
    double* pattern[3] = {(double[]){1, 0, 0}, 
                          (double[]){0, 1, 0}, 
                          (double[]){0, 0, 1}};

    int output_size;
    // 합성곱 연산을 수행하고 그 결과를 저장합니다.
    double** result = conv(image, m, pattern, n, stride, &output_size);

    // 합성곱 연산의 결과를 출력합니다.
    for (int i = 0; i < output_size; i++) {
        for (int j = 0; j < output_size; j++) {
            printf("%.0f ", result[i][j]);
        }
        printf("\n");
    }

    // 동적 할당된 메모리를 해제합니다.
    for (int i = 0; i < output_size; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}