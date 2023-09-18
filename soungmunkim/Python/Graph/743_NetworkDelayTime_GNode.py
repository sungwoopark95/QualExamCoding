"""
[전체노드 visit되는 최소한의 시간 구하기 (Directed graph with weight)]
-> Shortest path 찾는 것처럼 푼 뒤 가장 max인 weight 뽑기 (다 들린 후 min time)

You are given a network of n nodes, labeled from 1 to n. 
You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), 
where ui is the source node, vi is the target node, 
and wi is the time it takes for a signal to travel from source to target.

We will send a signal from a given node k. 
Return the minimum time it takes for all the n nodes to receive the signal. 
If it is impossible for all the n nodes to receive the signal, return -1.

times = [[2,1,1],[2,3,1],[3,4,1]]
n = 4
k = 2
networkDelayTime(times, n, k)
{1: [], 2: [(1, 1), (3, 1)], 3: [(4, 1)], 4: []}
2

times = [[1,2,1]]
n = 2
k = 2
networkDelayTime(times, n, k)
{1: [(2, 1)], 2: []}
-1
"""

from typing import List

class GNode:
    def __init__(self, id, time=float('inf')):
        self.id = id
        self.time = time
        
    def __str__(self):
        return str(self.id)

# DFS와 relaxation을 이용한 최단 경로 탐색
def shortestpath(G, start_node):
    # 시작 노드의 시간을 0으로 설정
    start_node.time = 0
    stack = [start_node]
    
    while stack:
        cur_node = stack.pop()
        
        # 현재 노드에서 연결된 모든 노드와 가중치를 확인
        for to, weight in G[cur_node.id]:
            if nodes[to].time > cur_node.time + weight:
                nodes[to].time = cur_node.time + weight
                stack.append(nodes[to])

    return nodes

def networkDelayTime(times: List[List[int]], n: int, k: int):
    # 모든 노드를 초기화하고 딕셔너리에 저장
    global nodes
    nodes = {i: GNode(i) for i in range(1, n+1)}
    
    # 인접 리스트 G 생성
    G = {i: [] for i in range(1, n+1)}
    for from_, to, weight in times:
        G[from_].append((to, weight))
    
    # DFS를 사용하여 시작 노드에서 다른 노드로의 최단 시간을 계산
    shortestpath(G, nodes[k])
    
    # 모든 노드의 최대 시간을 계산
    max_time = max(node.time for node in nodes.values())

    # 모든 노드에 도달할 수 없는 경우 -1 반환
    if any(node.time == float('inf') for node in nodes.values()):
        return -1
    
    return max_time





#------------------- dijkstra 알고리즘 쓴 구현 ---------------------------#
# import heapq  # 최소 힙 연산을 위한 heapq 라이브러리 불러오기

# class GNode:
#     def __init__(self, id, time=float('inf')):
#         self.id = id  # 노드의 ID
#         self.time = time  # 시작 노드로부터의 거리

#     def __lt__(self, other):  # heapq를 위해 < 연산자를 재정의
#         return self.time < other.time

# def dijkstra(graph, start_node):
#     # 모든 노드를 거리 inf로 초기화하여 distances 딕셔너리 생성
#     distances = {i: GNode(i) for i in range(1, n+1)}
#     distances[start_node.id].time = 0  # 시작 노드의 거리는 0
#     queue = [(0, start_node)]  # 시작 노드와 그 거리를 큐에 추가

#     while queue:
#         current_distance, current_node = heapq.heappop(queue)  # 큐에서 가장 가까운 노드를 꺼내옴

#         # 이미 처리된 노드는 무시
#         if distances[current_node.id].time < current_distance:
#             continue

#         # 현재 노드의 인접 노드들을 순회하며 거리 정보 갱신
#         for adjacent_id, weight in graph[current_node.id]:
#             distance = current_distance + weight  # 현재 노드를 통해 인접 노드로 가는 거리 계산

#             # 기존 거리보다 새로운 거리가 더 짧으면 갱신
#             if distance < distances[adjacent_id].time:
#                 distances[adjacent_id].time = distance
#                 heapq.heappush(queue, (distance, distances[adjacent_id]))

#     return distances  # 모든 노드까지의 최단 거리 반환

# def networkDelayTime(times, n, k):
#     graph = {i: [] for i in range(1, n+1)}  # 그래프 초기화

#     # 주어진 간선 정보를 그래프에 추가
#     for u, v, w in times:
#         graph[u].append((v, w))

#     # 시작 노드로부터의 최단 거리 계산
#     distances = dijkstra(graph, GNode(k))
#     # 모든 노드까지의 최단 거리 중 가장 큰 값을 찾음
#     max_distance = max(node.time for node in distances.values())

#     # 모든 노드로의 신호 전송이 가능하면 최대 시간을, 그렇지 않으면 -1을 반환
#     return max_distance if max_distance < float('inf') else -1
