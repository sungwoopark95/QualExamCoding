"""
M x N 사이즈의 방 안에 뿡뿡이 몇 명이 방귀를 뀌었다. 
방귀는 1초가 지나면 인접한 공간 (위, 아래, 왼쪽, 오른쪽)으로 퍼진다. 
지독한 방귀이기에 한번 퍼지기 시작하면 사라지지 않는다. 
몇 초 만에 방 전체로 방귀가 퍼지는지 시간을 계산하여 return 

● M과 N은 1 이상 자연수이다.
● 리스트는0또는1또는-1로되어있다.
    ■ 0은방귀가퍼질수있는빈공간이다.
    ■ 1은처음(0초일때)뿡뿡이들이방귀를뀐자리이다.최소한곳이상에방귀를 뀌었고, 방귀는 동시에 퍼진다.
    ■ 방귀는위,아래,왼쪽,오른쪽으로퍼질수있고,대각선으로는퍼질수없다.
    ■ 1초마다 퍼진다.
    ■ -1은 벽이어서 방귀가 퍼질 수 없다.
● 방전체,즉 0인 곳 모두로 방귀가 퍼질때까지 걸린 시간을 return 해야한다.
    ■ 방 전체로 방귀가 퍼질 수 없으면 -1을 return한다.
● 처음(0초)부터 방귀가 꽉 찬 상태면 0을 return한다.

TestCase1) 
>>> P1([[-1, 1], 
        [1, -1]])
0
설명: 처음부터 방귀가 꽉 차 있으므로 0을 return
TestCase2)
>>> P1([[1, 0]]) 
1
"""

from collections import deque

def P1(room):
    # 방의 크기(행과 열)를 구합니다.
    row = len(room)
    col = len(room[0])

    # 방향들: 오른쪽, 아래쪽, 왼쪽, 위쪽
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    # 방 전체가 방귀로 꽉 차있는지 검사, 만약 꽉 차있으면 0을 반환합니다.
    if all(val != 0 for r in room for val in r):
        return 0

    # BFS를 통해 방귀를 확산하는 함수
    def bfs():
        # 방귀가 처음 시작된 모든 위치를 queue에 넣습니다. (중요!)
        q = deque([(i, j, 0) for i in range(row) for j in range(col) if room[i][j] == 1])

        max_time = 0

        # 큐가 빌 때까지 BFS 실행
        while q:
            i, j, t = q.popleft()
            
            # 현재 위치에서 네 방향을 검사합니다.
            for dx, dy in directions:
                ni, nj = i + dx, j + dy

                # 새로운 위치가 방 내부에 있고 방귀가 아직 확산되지 않았다면
                if 0 <= ni < row and 0 <= nj < col and room[ni][nj] == 0:
                    room[ni][nj] = 1  # 방귀 확산
                    q.append((ni, nj, t + 1))  # 새로운 위치와 시간을 큐에 추가
                    max_time = max(max_time, t + 1)  # 최대 시간 업데이트

        return max_time

    # BFS를 수행하여 방귀 확산에 필요한 최대 시간을 얻습니다.
    max_time = bfs()

    # 방귀가 확산되지 않은 위치가 있으면 -1을 반환합니다.
    for i in range(row):
        for j in range(col):
            if room[i][j] == 0:
                return -1

    return max_time