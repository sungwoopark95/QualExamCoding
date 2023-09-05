"""
[CNN 구현하기]

image: m x n np array
pattern: n x n np array
stride도 감안해야 함 (Padding, Dilation 등은 없음)
    stride 기본 값인 1
m < n이거나, stride와 m, n이 정확히 맞아 떨어지지 않으면 error 출력

>>> image = np.array([[1,2,3,3,3], [4,5,6,6,6], [7,8,9,9,9], [10,11,12,13,13], [10,11,12,13,13]])
>>> pattern = np.array([[1,0,0],[0,1,0],[0,0,1]])
>>> conv(image, pattern, 2)
array([[15, 18],
       [30, 35]])
"""

import numpy as np

def convolution(image, pattern, stride=1):
    # 이미지와 패턴의 크기를 얻습니다.
    m = image.shape[0]
    n = pattern.shape[0]
    
    # m이 n보다 작은 경우, 합성곱을 수행할 수 없으므로 에러 메시지를 출력합니다.
    if m < n:
        print("Error: m < n")
        return None

    # stride 값에 따라 출력의 크기가 정수가 아니면 에러 메시지를 출력합니다.
    if (m - n) % stride != 0:
        print("Error: Incompatible stride, m, and n")
        return None

    # 합성곱 연산 결과를 저장할 배열의 크기를 계산합니다.
    output_size = (m - n) // stride + 1
    result = np.zeros((output_size, output_size))

    # 합성곱 연산을 수행합니다.
    for i in range(0, output_size):
        for j in range(0, output_size):
            # i*stride:i*stride+n 은 이미지의 행 방향에서 추출할 부분의 시작과 끝 인덱스를 나타냅니다.
            # j*stride:j*stride+n 은 이미지의 열 방향에서 추출할 부분의 시작과 끝 인덱스를 나타냅니다.
            # 따라서 image[i*stride:i*stride+n, j*stride:j*stride+n]은 합성곱 연산에 사용될 이미지의 부분을 나타냅니다.
            # 이 부분과 패턴을 element-wise로 곱한 후, 모든 값을 합하여 결과 배열에 저장합니다.
            result[i][j] = np.sum(image[i*stride:i*stride+n, j*stride:j*stride+n] * pattern)
            
    return result
