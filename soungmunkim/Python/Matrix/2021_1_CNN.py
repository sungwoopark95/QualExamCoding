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

def conv(image, pattern, stride = 1):
    # 패턴의 시작과 끝 Index 정의
    beg = 0
    end = pattern.shape[0]
    
    # 결과를 저장할 list 초기화
    res = []
    
    # 이미지와 패턴의 dimension 확인
    m = image.shape[0]
    n = pattern.shape[0]
    
    # 이미지 차원이 패턴보다 작을 경우 -> error
    if m < n:
        print("Error: m < n")
        return None
    # stride에 따른 출력 크기가 정수가 아닐 경우 -> error
    if (m - n) % stride > 0:
        print("Incompatible patterns")
        return None
    
    # 이미지를 Row 방향으로 stride 만큼 이동하며 convolution 수행
    for i in range(0, m-n+1, stride):
        k = [] # 각 row의 결과를 저장할 임시 List
        # 이미지를 Col 방향으로 stride 만큼 이동하며 convolution 수행
        for j in range(0, m-n+1, stride):
            # convolution 연산의 범위가 이미지를 벗어나면 pass
            if i + end > m or j + end > m:
                continue
            # convolution 연산: 이미지의 일부분과 패턴을 element-wise 곱한 후 합
            k.append(np.sum(image[i:i+end, j:j+end] * (pattern)))
        # row의 결과를 최종 결과에 추가
        res.append(k)
    # 결과를 Numpy array로 변환하여 반환
    return np.array(res)

# Test Cases
# image = np.array([[1,2,3,3,3], [4,5,6,6,6], [7,8,9,9,9], [10,11,12,13,13], [10,11,12,13,13]])
# pattern = np.array([[1,0,0],[0,1,0],[0,0,1]])

# conv(image, pattern, 2)
