"""
M x N 리스트인 world를 함수의 입력으로 받는다. 
리스트의 원소는 1 또는 0으로 이루어 져 있고, 1은 땅, 0은 물을 의미한다. 
이 때, 인접한 땅으로 연결되어 있고, 물로 둘러 싸여 있는 지역을 섬이라고 하자. 
섬의 개수를 return 하는 함수를 구현하라.

    ● M과 N은 1이상 자연수이다.
    ● 리스트 바깥은 물이라고 가정한다.
    ● 인접해 있다는 것은 상,하,좌,우 네방향 중 한 곳에서 붙어있는 것이고,대각선 방향은 인접해 있는 것이 아니다.
    ● 섬이 아닌 땅은 없다.

예시1)
>>> P5([[1,1,1,1,0], 
        [1,0,0,1,0], 
        [1,1,0,1,0],
        [1,1,0,0,0]]) 
1
"""

from collections import deque

def P4(matrix: list):
    
    Row = len(matrix)
    Col = len(matrix[0])
    # 앞 뒤 양 옆
    directions = [(0,1), (1,0), (0,-1), (-1,0)]
    
    def bfs(row, col):
        q = deque([(row, col)])
        
        while q:
            i, j = q.popleft()
            # direction 별로 돌기
            for dx, dy in directions:
                ni, nj = i+dx, j+dy
                # 섬이면 visit하고 주변 queue에 넣기
                if (0 <= ni < Row) and (0 <= nj < Col) and matrix[ni][nj] == 1:
                    matrix[ni][nj] = 0
                    q.append((ni, nj))
        return 1   # 한 bfs 다 끝나면 한 섬 다 돈 것
    
    tot = 0
    for row in range(Row):
        for col in range(Col):
            if matrix[row][col] == 1:
               tot += bfs(row, col)
    
    return tot