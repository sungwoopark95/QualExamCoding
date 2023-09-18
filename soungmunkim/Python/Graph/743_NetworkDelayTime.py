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

# DFS + Relaxation
def shortestpath(G, s):
    times = dict()
    
    for key in G.keys():
        if key not in times:
            times[key] = float('inf')
            
    times[s] = 0
    stack = [s]
    
    while stack:
        cur = stack.pop()
        for node, weight in G[cur]:
            if times[node] > times[cur] + weight:
                times[node] = times[cur] + weight
                stack.append(node)
    return times
        
def networkDelayTime(times: List[List[int]], n: int, k: int):
    # edge, weight 정보 담은 graph dict
    G = dict()
    # 1번 노드부터니까
    for i in range(1, n+1):
        G[i] = []
    
    # 정보 입력 
    for i in range(len(times)):
        from_ = times[i][0]
        to = times[i][1]
        weight = times[i][2]
        
        G[from_].append((to, weight))
    # print("Graph: ", G)
    
    paths = shortestpath(G, k)
    # print("Shortest path: ", paths)
    
    # 모든 노드가 시그널을 받는 데 필요한 시간을 찾아야 합니다.
    # shortest path 각 time 중 제일 max time(weight) 고르기
    max_time = -1
    for time in paths.values():
        if time == float('inf'):
            return -1
        max_time = max(max_time, time)
    
    return max_time

#------------------- dijkstra 알고리즘 쓴 구현 ---------------------------#
# import heapq  # 우선순위 큐를 위한 heapq 모듈을 가져옵니다.

# def dijkstra(graph, start):
#     distances = {node: float('inf') for node in graph}  # 각 노드까지의 거리를 무한대로 초기화합니다.
#     distances[start] = 0  # 시작 노드까지의 거리는 0입니다.
#     queue = [(0, start)]  # 시작 노드를 큐에 추가합니다. (거리, 노드) 형태로 저장됩니다.

#     while queue:
#         current_distance, current_node = heapq.heappop(queue)  # 큐에서 가장 거리가 짧은 노드를 꺼냅니다.

#         # 이미 처리된 노드는 무시
#         if distances[current_node] < current_distance:
#             continue

#         for adjacent, weight in graph[current_node]:  # 현재 노드의 인접 노드들을 확인합니다.
#             distance = current_distance + weight  # 현재 노드를 거쳐서 인접 노드로 가는 거리를 계산합니다.

#             # 최단 거리를 발견한 경우 업데이트
#             if distance < distances[adjacent]:
#                 distances[adjacent] = distance
#                 heapq.heappush(queue, (distance, adjacent))  # 최단 거리가 갱신된 인접 노드를 큐에 추가합니다.

#     return distances  # 모든 노드까지의 최단 거리를 반환합니다.

# def networkDelayTime(times, n, k):
#     graph = {i: [] for i in range(1, n+1)}  # 빈 그래프를 생성합니다.

#     for u, v, w in times:  # 주어진 간선 정보를 그래프에 추가합니다.
#         graph[u].append((v, w))

#     distances = dijkstra(graph, k)  # 시작 노드로부터의 최단 거리를 계산합니다.
#     max_distance = max(distances.values())  # 모든 노드까지의 최단 거리 중 가장 큰 값을 찾습니다.

#     return max_distance if max_distance < float('inf') else -1  # 모든 노드로의 신호 전송이 가능하면 최대 시간을, 그렇지 않으면 -1을 반환합니다.
