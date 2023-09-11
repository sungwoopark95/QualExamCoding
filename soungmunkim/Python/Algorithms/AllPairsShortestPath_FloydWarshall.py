import sys

# 연결되지 않은 path의 weight
INF = sys.maxsize

# Floyd-Warshall Algorithm
# input - adj(인접행렬), n(vertex의 수)
# output - dist : 최소 i->j의 path를 기록한 matrix
# output - pred : i->j의 path에서 j 직전에 거치는 node를 기록한 matrix.
def Floyd_warshall(adj,n):
    # 거리 기록할 배열 초기화
    dist = adj

    # predecessor 기록할 배열 초기화
    pred = [['NIL']*n for i in range(n)]
    for i in range(n):
        for j in range(n):
            if i != j and adj[i][j] != INF:
                pred[i][j] = i

    # intermediate node 'k'를 하나씩 추가하며, 해당 경우의 최단 거리 계산
    for k in range(n):
        for i in range(n):   # i: 출발노드
            for j in range(n):   # j: 도착노드

                # k를 추가함으로써 이전보다 더 빠른 길이 생기는 경우의 처리
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
                    pred[i][j] = pred[k][j]
    return dist, pred


# 최단 경로를 출력하는 함수
def print_shortest_path(pred, i, j):
    if i == j:
        print(i, end=' ')
    else:
        print_shortest_path(pred, i, pred[i-1][j-1])
        print(j, end=' ')


# # 예제)
# n = 5  # n: 노드의 수
# adj = [[0, 3, 8, INF, -4],   # adj: 노드간의 거리를 기록한 인접행렬
#        [INF, 0, INF, 1, 7],
# 			 [INF, 4, 0, INF, INF],
#        [2, INF, -5, 0, INF],
#        [INF, INF, INF, 6, 0]]

# dist, pred = Floyd_warshall(adj, n)

# # answer_dist) 
# [[0, 1, -3, 2, -4], 
# [3, 0, -4, 1, -1], 
# [7, 4, 0, 5, 3], 
# [2, -1, -5, 0, -2], 
# [8, 5, 1, 6, 0]]
# # answer_pred) 
# [['NIL', 3, 4, 5, 1], 
# [4, 'NIL', 4, 2, 1], 
# [4, 3, 'NIL', 2, 1], 
# [4, 3, 4, 'NIL', 1], 
# [4, 3, 4, 5, 'NIL']]

# # 경로 추출 예제
# print_shortest_path(p, 1, 2)
# # answer_path)
# # 1 5 4 3 2 


######################## c++ 변환 코드 #############################
# # 파이썬에서는 특별한 라이브러리나 네임스페이스를 사용하지 않아도 기본적인 입출력 및 기능을 사용할 수 있습니다.

# NIL = -1       # NIL을 -1로 정의합니다.
# MAX = 101      # MAX를 101로 정의합니다.

# dist = [[MAX for _ in range(MAX)] for _ in range(MAX)]  # 모든 노드 쌍 간의 최단 거리를 저장할 2차원 배열입니다.
# pred = [[NIL for _ in range(MAX)] for _ in range(MAX)]  # 최단 경로를 따라 각 노드의 전 노드를 저장할 2차원 배열입니다.

# def floyd(n):
#     # 플로이드-워셜 알고리즘 함수
#     for mid in range(1, n+1):  # 중간 노드로서 모든 노드들을 고려합니다.
#         for start in range(1, n+1):  # 시작 노드로서 모든 노드들을 고려합니다.
#             for end in range(1, n+1):  # 종료 노드로서 모든 노드들을 고려합니다.
#                 # mid 노드를 거쳐가는 것이 직접 가는 것보다 짧은 경우, 거리를 갱신합니다.
#                 if dist[start][end] > dist[start][mid] + dist[mid][end]:
#                     dist[start][end] = dist[start][mid] + dist[mid][end]
#                     pred[start][end] = pred[mid][end]

# def print_shortest_path(i, j):
#     # i에서 j까지의 최단 경로를 재귀적으로 출력하는 함수
#     if i == j:
#         print(i, end=" ")
#     else:
#         print_shortest_path(i, pred[i][j])
#         print(j, end=" ")

# # main 함수에 해당하는 코드
# n = int(input("vertex의 개수를 입력하세요:\n"))  # n은 노드(정점)의 수입니다.

# for i in range(1, n+1):
#     dist[i][i] = 0  # 노드에서 자신까지의 거리는 0입니다.
#     for j in range(1, n+1):
#         if i != j:
#             d = int(input(f"{i}->{j}의 거리를 입력하세요:"))
#             dist[i][j] = d  # 입력받은 거리를 dist 배열에 저장합니다.
#             pred[i][j] = i  # 시작 노드 i를 전 노드로 설정합니다.

# print("초기값")  # 초기 인접 행렬과 전 노드 행렬을 출력합니다.
# for row in dist[1:n+1]:
#     print(*row[1:n+1], sep="\t")
# print()

# for row in pred[1:n+1]:
#     print(*row[1:n+1], sep="\t")
# print()

# floyd(n)  # 플로이드-워셜 알고리즘을 사용하여 최단 거리를 계산합니다.

# print("최종값")  # 계산된 최단 거리와 전 노드 행렬을 출력합니다.
# for row in dist[1:n+1]:
#     print(*row[1:n+1], sep="\t")
# print()

# for row in pred[1:n+1]:
#     print(*row[1:n+1], sep="\t")
