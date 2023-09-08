from collections import deque
from typing import List

def P4_DFS_Recursion(world:List[List[int]]):
    """
    이 코드는 주어진 2차원 그리드에서 값이 1인 연결된 영역의 개수를 계산하는 함수입니다. 
    DFS를 사용하여 그리드의 각 위치를 방문하며 연결된 영역을 탐색합니다.
    """
    # 깊이 우선 탐색 (DFS) 함수 정의
    def dfs(grid, visited, m, n, i, j):
        # 현재 위치가 그리드 범위를 벗어나거나 이미 방문한 곳이거나 값이 0이면 종료
        if i < 0 or i >= m or j < 0 or j >= n or visited[i][j] == 1 or grid[i][j] == 0:
            return
        # 현재 위치를 방문한 것으로 표시
        visited[i][j] = 1
        # 상하좌우 방향으로 DFS 수행
        dfs(grid, visited, m, n, i+1, j)
        dfs(grid, visited, m, n, i-1, j)
        dfs(grid, visited, m, n, i, j+1)
        dfs(grid, visited, m, n, i, j-1)
        
    M, N = len(world), len(world[0])  # 그리드의 크기를 M, N으로 저장
    area = 0  # 연결된 영역의 개수를 저장할 변수
    visited = [[0 for _ in range(N)] for _ in range(M)]  # 방문 여부를 저장하는 2차원 리스트
    for i in range(M):
        for j in range(N):
            # 현재 위치의 값이 1이고 아직 방문하지 않았다면
            if world[i][j] == 1 and visited[i][j] == 0:
                dfs(world, visited, M, N, i, j)  # DFS 수행
                area += 1  # 연결된 영역의 개수 증가
                
    return area  # 연결된 영역의 개수 반환


## Stack을 사용한 DFS
def P4_DFS_Stack(world:List[List[int]]):
    """
    이 코드는 주어진 2차원 그리드에서 값이 1인 연결된 영역의 개수를 계산하는 함수입니다. 
    스택을 사용한 DFS를 사용하여 그리드의 각 위치를 방문하며 연결된 영역을 탐색합니다.
    """
    # 스택을 사용한 깊이 우선 탐색 (DFS) 함수 정의
    def dfs(grid, visited, m, n, i, j):
        stack = [(i, j)]
        while stack:
            x, y = stack.pop()
            for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] == 1 and visited[nx][ny] == 0:
                    visited[nx][ny] = 1
                    stack.append((nx, ny))
        
    M, N = len(world), len(world[0])  # 그리드의 크기를 M, N으로 저장
    area = 0  # 연결된 영역의 개수를 저장할 변수
    visited = [[0 for _ in range(N)] for _ in range(M)]  # 방문 여부를 저장하는 2차원 리스트
    for i in range(M):
        for j in range(N):
            # 현재 위치의 값이 1이고 아직 방문하지 않았다면
            if world[i][j] == 1 and visited[i][j] == 0:
                dfs(world, visited, M, N, i, j)  # DFS 수행
                area += 1  # 연결된 영역의 개수 증가
                
    return area  # 연결된 영역의 개수 반환


def P4_BFS(world:List[List[int]]):
    """
    이 코드는 주어진 2차원 그리드에서 값이 1인 연결된 영역의 개수를 계산하는 함수입니다. 
    BFS를 사용하여 그리드의 각 위치를 방문하며 연결된 영역을 탐색합니다.
    """
    # 너비 우선 탐색 (BFS) 함수 정의
    def bfs(grid, visited, m, n, i, j):
        queue = deque([(i, j)])
        while queue:
            x, y = queue.popleft()
            for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] == 1 and visited[nx][ny] == 0:
                    visited[nx][ny] = 1
                    queue.append((nx, ny))
        
    M, N = len(world), len(world[0])  # 그리드의 크기를 M, N으로 저장
    area = 0  # 연결된 영역의 개수를 저장할 변수
    visited = [[0 for _ in range(N)] for _ in range(M)]  # 방문 여부를 저장하는 2차원 리스트
    for i in range(M):
        for j in range(N):
            # 현재 위치의 값이 1이고 아직 방문하지 않았다면
            if world[i][j] == 1 and visited[i][j] == 0:
                bfs(world, visited, M, N, i, j)  # BFS 수행
                area += 1  # 연결된 영역의 개수 증가
                
    return area  # 연결된 영역의 개수 반환

if __name__ == "__main__":
    print(P4_BFS([[1,1,1,1,0], 
                  [1,0,0,1,0], 
                  [1,1,0,1,0], 
                  [1,1,0,0,0]]))
    
    world = [[1,0,0,0,1], 
             [1,1,0,0,0], 
             [0,0,0,1,1], 
             [0,1,0,1,0]]
    
    print(P4_DFS_Recursion(world))
    
    