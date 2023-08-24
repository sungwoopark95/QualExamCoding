"""
행렬을 다음과 같이 표현할 때, [[1, 3, 0], [2, 5, 3], [3, 4, 1], [2, 0, 0]]
행렬을 변수(argument)로 받아서 오른쪽 아래 대각선 방향으로 정렬한 행렬을 리턴하는 함수를 작성하시오.

TestCase1)
>>> P4([[1, 3, 0], [2, 5, 3], [3, 4, 1], [2, 0, 0]]) [[1, 3, 0], [0, 1, 3], [0, 2, 5], [2, 3, 4]]
TestCase2)
>>> P4([[1, 6, 2, 4, 6, 2, 4, 7, 0]]) [[1, 6, 2, 4, 6, 2, 4, 7, 0]]
"""

def P4_ans(mat):
    dic = {}
    for i in range(len(mat)):
        for j in range(len(mat[0])):
            if i-j not in dic:
                dic[i-j] = [mat[i][j]] # list type인 value로 넣기
            else:
                dic[i-j].append(mat[i][j])
    for k in dic:
        dic[k].sort()
    
    for i in range(len(mat)):
        for j in range(len(mat[0])):
            mat[i][j] = dic[i-j].pop(0) # 정렬된 list에서 젤 작은 값인 맨 앞 숫자 가져오기
    return mat