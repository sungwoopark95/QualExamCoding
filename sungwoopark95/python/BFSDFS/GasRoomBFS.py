"""
`M x N` 사이즈의 방 안에 뿡뿡이 몇 명이 방귀를 뀌었다. 방귀는 1초가 지나면 인접한 공간 (위, 아래, 왼쪽, 오른쪽)으로 퍼진다. 지독한 방귀이기에 한번 퍼지기 시작하면 사라지지 않는다. 몇 초만에 방 전체로 방귀가 퍼지는지 시간을 계산하여 return하는 함수 P1을 구현해야 한다.

* 방에 대한 정보로 `M x N` 리스트인 `rooms`를 함수의 파라미터로 받는다.  
* `M`과 `N`은 1 이상 자연수이다.  
* 리스트는 `0` 또는 `1` 또는 `-1`로 되어있다.  
    - `0`은 방귀가 퍼질 수 있는 빈 공간이다.  
    - `1`은 처음(0초일 때) 뿡뿡이들이 방귀를 뀐 자리이다. 최소 한 곳 이상에 방귀를  뀌었고, 방귀는 동시에 퍼진다.  
    - 방귀는 위, 아래, 왼쪽, 오른쪽으로 퍼질 수 있고, 대각선으로는 퍼질 수 없다.  
    - 1초마다 퍼진다.  
    - `-1`은 벽이어서 방귀가 퍼질 수 없다.  
* 방 전체, 즉 `0`인 곳 모두로 방귀가 퍼질 때까지 걸린 시간을 return해야 한다.  
* 방 전체로 방귀가 퍼질 수 없으면 `-1`을 return한다.  
* 처음(0초)부터 방귀가 꽉 찬 상태면 `0`을 return한다. 
"""
from typing import List

## 그래프에서의 BFS
def P1(rooms:List[List[int]]):
    """
    이 코드는 BFS를 사용하여 방의 각 위치에 도달하는 데 걸리는 최소 시간을 계산합니다. 
    시작 지점에서 방의 모든 위치로 퍼져나가는 데 걸리는 시간을 반환하며, 모든 위치로 퍼져나갈 수 없는 경우 -1을 반환합니다.
    """
    M, N = len(rooms), len(rooms[0])  # 방의 크기를 M, N으로 저장
    # 시작 지점 찾기
    queue = []
    for i in range(M):
        for j in range(N):
            if rooms[i][j] == 1:  # 시작 지점을 큐에 추가
                queue.append((i, j, 1))
                
    # bfs 시작
    visited = [[0 for _ in range(N)] for _ in range(M)]  # 방문 여부를 저장하는 2차원 리스트
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]  # 상하좌우 방향을 나타내는 리스트
    while queue:
        curr_x, curr_y, curr_val = queue.pop(0)

        # 현재 위치가 벽이거나 이미 방문한 곳이거나 값이 1보다 크면 continue
        if rooms[curr_x][curr_y] == -1 or rooms[curr_x][curr_y] > 1 or visited[curr_x][curr_y] == 1:
            continue

        # 현재 보고 있는 구역이 방문되지 않고, 그 값이 -1(벽)이거나 1보다 큰 값이 아닌 경우, 방귀가 이 구역에 도달한 시각을 채워넣음
        rooms[curr_x][curr_y] = curr_val
        visited[curr_x][curr_y] = 1
        
        # 상하좌우 방향으로 이동
        for d in directions:
            dx, dy = d
            nx, ny = curr_x + dx, curr_y + dy
            # 방의 범위를 벗어나면 continue
            if nx < 0 or nx >= M or ny < 0 or ny >= N:
                continue
            
            # 이 부분이 핵심 - 현재 point 주변 상하좌우까지 도달하는 시간은 1이므로, 앞으로 방문할 구역은 현재 값에 1을 더해줘서 enqueue
            queue.append((nx, ny, curr_val+1))
    
    # 방의 상태 출력
    for i in range(M):
        print(rooms[i], end='\n')
    
    time = -1
    for i in range(M):
        for j in range(N):
            if rooms[i][j] == 0:
                # 아직 다 돌지 못한 구역이 남아 있다면 전체로 다 퍼지지 않은 것
                return -1
            # 최대 시간 업데이트
            time = max(time, rooms[i][j])
            
    return time - 1  # 시작 지점의 시간 1을 제외하고 반환

if __name__ == "__main__":
    room1 = [[0,0,0,0,0,0], 
             [0,0,0,0,0,0], 
             [0,0,0,0,0,0], 
             [0,0,0,0,0,1]]
    print(P1(room1))
    
    room2 = [[1,-1,0,0, 0,0], 
             [0,-1,0,0, 0,0], 
             [0, 0,0,0,-1,0], 
             [0, 0,0,0,-1,1]]
    print(P1(room2))
