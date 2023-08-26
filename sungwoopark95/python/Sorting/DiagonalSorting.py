"""
Matrix를 받아서 오른쪽 아래 대각선 방향으로 ascending sort
"""
from typing import List

def P4(arr:List[List]):
    # 대각선에 있는 item들은 i-j가 서로 같음
    # i-j = 0 -> [1, 5, 1], i-j = 1 -> [2, 4, 0]
    # 대각선에 있는 item들끼리 묶어놓은 dict 만들기
    diag = dict()
    M, N = len(arr), len(arr[0]) # 행과 열
    for i in range(M):
        for j in range(N):
            key = i-j
            if key not in diag:
                diag[key] = [arr[i][j]]
            else:
                diag[key].append(arr[i][j])
    
    # sort each value
    for key in diag:
        diag[key].sort()
    
    # reconstruct the matrix
    ans = [[0 for _ in range(N)] for _ in range(M)]
    for i in range(M):
        for j in range(N):
            key = i-j
            ans[i][j] = diag[key].pop(0) # 어차피 정렬되어 있으므로 i-j가 같은 구역에 순서대로 끼워맞추기만 하면 됨
    
    return ans

if __name__ == "__main__":
    print(P4([[1, 3, 0], [2, 5, 3], [3, 4, 1], [2, 0, 0]]))
