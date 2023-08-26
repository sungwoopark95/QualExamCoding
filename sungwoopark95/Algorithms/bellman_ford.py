class Vertex:
    def __init__(self):
        self.d = float('inf')  # v와 s 사이의 거리를 나타냅니다.
        self.pi = None  # v의 부모 노드를 나타냅니다.

class Graph:
    def __init__(self, V, E):
        self.V = V  # 정점의 집합
        self.E = E  # 간선의 집합

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

## 그래프 내의 모든 간선에 대해 완화를 시도하며, 마지막에 음의 순환(음의 가중치를 가진 순환 경로)이 있는지 확인하는 코드
def BELLMAN_FORD_FIND_CYCLE(G, weights, s):
    INITIALIZE_SINGLE_SOURCE(G, s)
    
    # 정점의 수만큼 반복합니다.
    for _ in range(len(G.V) - 1):
        # 모든 간선에 대해 완화를 시도합니다.
        for (u, v) in G.E:
            RELAX(u, v, weights)
    
    # 음의 순환을 확인합니다.
    for (u, v) in G.E:
        if v.d > u.d + weights[(u, v)]:
            return False  # 음의 순환이 있으면 False를 반환합니다.
    
    return True  # 그렇지 않으면 True를 반환합니다.

## 이 코드에서 construct_path 함수는 시작 정점 s에서 주어진 정점 v까지의 경로를 반환합니다. 
# BELLMAN_FORD 함수는 음의 순환을 발견하면 None을 반환하고, 그렇지 않으면 시작 정점 s에서 각 정점 v까지의 최단 경로를 담은 딕셔너리를 반환합니다.
def construct_path(s, v):
    """s에서 v까지의 경로를 반환합니다."""
    path = []
    while v != s and v is not None:
        path.insert(0, v)
        v = v.pi
    if v == s:
        path.insert(0, s)
    return path

def BELLMAN_FORD_FIND_SHORTEST_PATH(G, weights, s):
    INITIALIZE_SINGLE_SOURCE(G, s)
    
    for _ in range(len(G.V) - 1):
        for (u, v) in G.E:
            RELAX(u, v, weights)
    
    for (u, v) in G.E:
        if v.d > u.d + weights[(u, v)]:
            return None  # 음의 순환이 있으면 None을 반환합니다.
    
    # s에서 각 정점 v까지의 최단 경로를 담은 딕셔너리를 생성합니다.
    shortest_paths = {}
    for v in G.V:
        shortest_paths[v] = construct_path(s, v)
    
    return shortest_paths


if __name__ == "__main__":
    # 그래프 초기화
    v1 = Vertex()
    v2 = Vertex()
    v3 = Vertex()

    G = Graph([v1, v2, v3], [(v1, v2), (v2, v3)])
    weights = {(v1, v2): 5, (v2, v3): 3}

    # 알고리즘 실행
    paths = BELLMAN_FORD_FIND_SHORTEST_PATH(G, weights, v1)

    # 결과 출력
    for vertex, path in paths.items():
        print(f"Path to vertex {vertex}: {[v for v in path]}")
