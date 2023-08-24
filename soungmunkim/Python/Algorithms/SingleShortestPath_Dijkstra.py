"""
[Dijkstra algorithm 구현하기]

negative weight cycle 없다는 가정
"""

import heapq  # 우선순위 큐를 위한 heapq 모듈을 사용합니다.

class Vertex:
    def __init__(self, name):
        self.name = name
        self.d = float('inf')  # v와 s 사이의 거리를 나타냅니다.
        self.pi = None  # v의 부모 노드를 나타냅니다.

    def __lt__(self, other):
        return self.d < other.d
    
    def __str__(self):
        return self.name


class Graph:
    def __init__(self, V, E, Adj=None):
        self.V = V  # 정점의 집합
        self.E = E  # 간선의 집합
        self.Adj = Adj  # 인접 리스트

def INITIALIZE_SINGLE_SOURCE(G, s):
    for v in G.V:
        v.d = float('inf')  # v와 s 사이의 거리를 무한대로 설정합니다.
        v.pi = None  # v의 부모 노드를 None으로 설정합니다.
    s.d = 0  # 시작 정점 s와 s 사이의 거리는 0입니다.

def RELAX(u, v, weights):
    if (u, v) in weights:
        if v.d > u.d + weights[(u, v)]:
            v.d = u.d + weights[(u, v)]
            v.pi = u

def DIJKSTRA(G, weights, s):
    """
    그래프 G에서 주어진 시작 정점 s로부터의 최단 경로를 계산합니다.
    
    :param G: 그래프
    :param weights: 간선의 가중치를 나타내는 딕셔너리
    :param s: 시작 정점
    """
    INITIALIZE_SINGLE_SOURCE(G, s)
    S = set()  # 경로를 저장하는 컨테이너
    Q = [(v.d, v) for v in G.V]  # (거리, 정점) 형태의 튜플로 우선순위 큐를 초기화합니다.
    heapq.heapify(Q)  # Min-priority queue로 만듭니다.

    while Q:
        _, u = heapq.heappop(Q)  # s와의 거리가 최소인 정점 u를 추출합니다.
        S.add(u)  # u를 S에 추가합니다.
        for v in G.Adj[u]:
            old_distance = v.d
            RELAX(u, v, weights)
            # RELAX 호출로 인해 v.d가 감소한 경우, 우선순위 큐에서 v의 키를 갱신합니다.
            if v.d < old_distance:
                # Q를 리스트로 처리하므로, v의 위치를 찾아서 갱신해야 합니다.
                # 실제 응용에서는 더 효율적인 자료구조를 사용해야 합니다.
                for i, (d, vertex) in enumerate(Q):
                    if vertex == v:
                        Q[i] = (v.d, v)
                        break
                heapq.heapify(Q)  # 힙 속성을 유지하기 위해 다시 heapify 합니다.

if __name__ == "__main__":
    # 그래프 초기화
    v1 = Vertex("v1")
    v2 = Vertex("v2")
    v3 = Vertex("v3")
    v4 = Vertex("v4")

    G = Graph([v1, v2, v3, v4], [(v1, v2), (v1, v3), (v2, v4), (v3, v4)])
    G.Adj = {
        v1: [v2, v3],
        v2: [v4],
        v3: [v4],
        v4: []
    }
    weights = {(v1, v2): 5, (v1, v3): 3, (v2, v4): 2, (v3, v4): 1}

    # DIJKSTRA 실행
    DIJKSTRA(G, weights, v1)

    # 결과 출력
    for vertex in G.V:
        print(f"Distance from {v1} to {vertex}: {vertex.d}")