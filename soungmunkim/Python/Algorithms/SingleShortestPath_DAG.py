"""
[최단 경로 찾기 DAG]
cycle이 없음 (directed graph)

(base) soungmunkim@gimseongmun-ui-MacBookPro Algorithms % python SingleShortestPath_DAG.py 
Distance from 0 to 0 is: 0
Distance from 0 to 1 is: 5
Distance from 0 to 2 is: 3
"""

# 필요한 라이브러리 불러오기
from collections import defaultdict

# 무한대를 표현하기 위한 상수
INF = float('inf')

# 각 노드를 표현하는 클래스
class Node:
    def __init__(self, to, weight):
        self.to = to        # 노드의 목적지를 저장
        self.weight = weight # 해당 노드로 가는 간선의 가중치

# 그래프를 표현하는 클래스
class Graph:
    def __init__(self, V):
        self.V = V                      # 정점의 수
        self.E = 0                      # 간선의 수
        self.adj = defaultdict(list)    # 인접 리스트로 그래프 표현

    # 그래프에 간선을 추가하는 함수
    def addEdge(self, src, dest, weight):
        self.adj[src].append(Node(dest, weight))
        self.E += 1

# 시작 정점에서의 거리를 초기화하는 함수
def Initialize_Single_Source(graph, source):
    distance = [INF] * graph.V
    distance[source] = 0
    return distance

# relax 함수: 시작 노드에서의 거리와 가중치를 고려하여 목적지 노드의 거리를 업데이트
def relax(distance, u, v, weight):
    if distance[u] != INF and distance[u] + weight < distance[v]:
        distance[v] = distance[u] + weight

# 위상 정렬을 위한 DFS 유틸리티 함수
def topologicalSortUtil(graph, v, visited, stack):
    visited[v] = True
    for node in graph.adj[v]:
        if not visited[node.to]:
            topologicalSortUtil(graph, node.to, visited, stack)
    stack.append(v)

# DAG에서의 최단 경로를 찾는 함수
def DAG_shortest_path(graph, source):
    visited = [False] * graph.V
    stack = []

    # 모든 노드에 대해 DFS 수행
    for i in range(graph.V):
        if not visited[i]:
            topologicalSortUtil(graph, i, visited, stack)

    distance = Initialize_Single_Source(graph, source)
    # 위상 정렬된 순서대로 relax 연산 수행
    while stack:
        u = stack.pop()
        for node in graph.adj[u]:
            relax(distance, u, node.to, node.weight)

    return distance

if __name__ == "__main__":
    V = 3  # 예시 그래프의 정점의 개수
    graph = Graph(V)

    # 예시 그래프에 간선 추가
    graph.addEdge(0, 1, 5)
    graph.addEdge(0, 2, 3)

    source = 0  # 시작 정점
    distances = DAG_shortest_path(graph, source)

    # 최단 거리 결과 출력
    for i, d in enumerate(distances):
        if d != INF:
            print(f"Distance from {source} to {i} is: {d}")
        else:
            print(f"Distance from {source} to {i} is: INF")
