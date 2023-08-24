"""
필터링된 이미지 속에서 글자(알파벳)가 몇 개인지 알아보는 프로그램을 만들어 보고자 한다. 
해당 필터는 이미지에서 글자인 부분은 1, 글자가 아닌 부분은 0으로 바꾼다고 한다. 
한 개의 글자는 1이 상, 하, 좌, 우, 대각선으로 인접하여 서로 연결되어 있다. 
해당 필터를 적용 하여 만든 이미지가 입력으로 주어졌을 때, 입력 이미지 내의 글자의 개수를 return하는 함 수 P3를 구현하라.

    ● 입력 값은 MxN 사이즈의 리스트이며 M, N은 1 이상 자연수이다. 
    ● 리스트에 숫자 0, 1외의 값은 없다.
    ● 원본 이미지 속 글자는 알파벳 대문자로만 구성되어 있다
"""

from collections import deque
def P3(matrix: list):
    
    Row = len(matrix)
    Col = len(matrix[0])
    
    # 방향들: 오른쪽, 아래쪽, 왼쪽, 위쪽, 대각선 4방향
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0), (1,1), (-1,-1), (1,-1), (-1,1)]
    
    def bfs(row, col):
        q = deque([(row, col)])
        print(f" queue is {q}")
        while q:
            i, j = q.popleft()
            
            for dx, dy in directions:
                ni, nj = i+dx, j+dy
                
                if (0 <= ni < Row) and (0 <= nj < Col) and matrix[ni][nj] == 1:
                    matrix[ni][nj] = 0
                    q.append((ni, nj))
        return 1
                
                
    ch = 0
    for row in range(Row):
        for col in range(Col):
            if matrix[row][col] == 1:
                ch += bfs(row, col)
    return ch
            