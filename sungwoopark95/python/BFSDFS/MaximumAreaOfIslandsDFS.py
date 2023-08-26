from typing import List
from collections import deque

## 가장 영역이 넓은 섬의 넓이를 구하는 방법
def P5_DFS_Recursion(world:List[List[int]]):
    """
    이 코드는 주어진 2차원 그리드에서 값이 1인 연결된 영역(섬)의 넓이 중에서 가장 큰 넓이를 계산하는 함수입니다. 
    DFS를 사용하여 그리드의 각 위치를 방문하며 연결된 영역의 넓이를 계산합니다.
    """
    # 깊이 우선 탐색 (DFS) 함수 정의
    def dfs(grid, visited, m, n, i, j):
        area = 0  # 현재 섬의 넓이를 저장할 변수
        # 현재 위치가 그리드 범위를 벗어나거나 이미 방문한 곳이거나 값이 0이면 0 반환
        if i < 0 or i >= m or j < 0 or j >= n or visited[i][j] == 1 or grid[i][j] == 0:
            return 0
        visited[i][j] = 1  # 현재 위치를 방문한 것으로 표시
        area += 1  # 현재 위치의 넓이를 1 증가
        # 상하좌우 방향으로 DFS 수행하며 해당 방향의 섬의 넓이를 현재 넓이에 더함
        area += dfs(grid, visited, m, n, i+1, j)
        area += dfs(grid, visited, m, n, i-1, j)
        area += dfs(grid, visited, m, n, i, j+1)
        area += dfs(grid, visited, m, n, i, j-1)
        return area  # 현재 섬의 총 넓이 반환
        
    M, N = len(world), len(world[0])  # 그리드의 크기를 M, N으로 저장
    visited = [[0 for _ in range(N)] for _ in range(M)]  # 방문 여부를 저장하는 2차원 리스트
    max_area = 0  # 가장 큰 섬의 넓이를 저장할 변수
    for i in range(M):
        for j in range(N):
            # 현재 위치의 값이 1이고 아직 방문하지 않았다면
            if world[i][j] == 1 and visited[i][j] == 0:
                area = dfs(world, visited, M, N, i, j)  # DFS 수행하여 해당 섬의 넓이를 계산
                max_area = max(max_area, area)  # 최대 넓이 업데이트
                print(f"시작 지점 : ({i}, {j}) 그리고 해당 섬의 넓이 : {area}")
    return max_area  # 가장 큰 섬의 넓이 반환

def P5_DFS_Stack(world:List[List[int]]):
    """
    이 코드는 주어진 2차원 그리드에서 값이 1인 연결된 영역(섬)의 넓이 중에서 가장 큰 넓이를 계산하는 함수입니다. 
    DFS를 사용하여 그리드의 각 위치를 방문하며 연결된 영역의 넓이를 계산합니다.
    """
    # 너비 우선 탐색 (BFS) 함수 정의
    def dfs(grid, visited, m, n, i, j):
        area = 0 # 현재 섬의 넓이를 저장할 변수
        stack = [(i, j)]
        while stack:
            x, y = stack.pop(-1)
            for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] == 1 and visited[nx][ny] == 0:
                    visited[nx][ny] = 1
                    area += 1
                    stack.append((nx, ny))
        if area == 0:
            # edge case - 1이 한 개만 존재하는 경우
            return 1
        return area
        
    M, N = len(world), len(world[0])  # 그리드의 크기를 M, N으로 저장
    visited = [[0 for _ in range(N)] for _ in range(M)]  # 방문 여부를 저장하는 2차원 리스트
    max_area = 0  # 가장 큰 섬의 넓이를 저장할 변수
    for i in range(M):
        for j in range(N):
            # 현재 위치의 값이 1이고 아직 방문하지 않았다면
            if world[i][j] == 1 and visited[i][j] == 0:
                area = dfs(world, visited, M, N, i, j)  # BFS 수행하여 해당 섬의 넓이를 계산
                max_area = max(max_area, area)  # 최대 넓이 업데이트
                print(f"시작 지점 : ({i}, {j}) 그리고 해당 섬의 넓이 : {area}")
    return max_area  # 가장 큰 섬의 넓이 반환

def P5_BFS(world:List[List[int]]):
    """
    이 코드는 주어진 2차원 그리드에서 값이 1인 연결된 영역(섬)의 넓이 중에서 가장 큰 넓이를 계산하는 함수입니다. 
    BFS를 사용하여 그리드의 각 위치를 방문하며 연결된 영역의 넓이를 계산합니다.
    """
    # 너비 우선 탐색 (BFS) 함수 정의
    def bfs(grid, visited, m, n, i, j):
        area = 0  # 현재 섬의 넓이를 저장할 변수
        queue = deque([(i, j)])
        while queue:
            x, y = queue.popleft()
            for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] == 1 and visited[nx][ny] == 0:
                    visited[nx][ny] = 1
                    area += 1
                    queue.append((nx, ny))
        if area == 0:
            # edge case - 1이 한 개만 존재하는 경우
            return 1
        return area
        
    M, N = len(world), len(world[0])  # 그리드의 크기를 M, N으로 저장
    visited = [[0 for _ in range(N)] for _ in range(M)]  # 방문 여부를 저장하는 2차원 리스트
    max_area = 0  # 가장 큰 섬의 넓이를 저장할 변수
    for i in range(M):
        for j in range(N):
            # 현재 위치의 값이 1이고 아직 방문하지 않았다면
            if world[i][j] == 1 and visited[i][j] == 0:
                area = bfs(world, visited, M, N, i, j)  # BFS 수행하여 해당 섬의 넓이를 계산
                max_area = max(max_area, area)  # 최대 넓이 업데이트
                print(f"시작 지점 : ({i}, {j}) 그리고 해당 섬의 넓이 : {area}")
    return max_area  # 가장 큰 섬의 넓이 반환

if __name__ == "__main__":
    world = [[1,1,1,1,0],  
             [1,0,0,1,0],  
             [1,1,0,1,0],
             [1,1,0,0,0]]
    
    print(P5_DFS_Stack(world))
