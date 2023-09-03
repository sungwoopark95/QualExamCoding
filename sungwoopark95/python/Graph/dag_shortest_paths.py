class Vertex:
    def __init__(self):
        self.d = float('inf')  # v와 s 사이의 거리를 나타냅니다.
        self.pi = None  # v의 부모 노드를 나타냅니다.

class Graph:
    def __init__(self, V, E, Adj):
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

def topological_sort(G):
    """
    그래프 G의 정점들을 위상 정렬하여 반환합니다.
    
    :param G: 그래프
    :return: 위상 정렬된 정점 리스트
    """
    color = {v: 'white' for v in G.V}  # 각 정점의 색상 (white: 미방문, gray: 방문 중, black: 완료)
    finish_time = {}  # 각 정점의 완료 시간
    time = [0]  # 현재 시간 (리스트로 선언하여 참조로 동작하게 함)
    order = []  # 위상 정렬된 정점 리스트

    def dfs_visit(u):
        time[0] += 1
        color[u] = 'gray'
        for v in G.Adj[u]:
            if color[v] == 'white':
                dfs_visit(v)
        color[u] = 'black'
        time[0] += 1
        finish_time[u] = time[0]
        order.insert(0, u)

    for u in G.V:
        if color[u] == 'white':
            dfs_visit(u)

    return order

def DAG_SHORTEST_PATHS(G, weights, s):
    """
    방향성 비순환 그래프(DAG)에서 주어진 시작 정점 s로부터의 최단 경로를 계산합니다.
    
    :param G: 그래프
    :param weights: 간선의 가중치를 나타내는 딕셔너리
    :param s: 시작 정점
    """
    # 그래프의 정점들을 위상 정렬합니다.
    sorted_vertices = topological_sort(G)
    
    # 시작 정점 s로부터의 거리를 초기화합니다.
    INITIALIZE_SINGLE_SOURCE(G, s)
    
    # 위상 정렬된 순서대로 각 정점에 대해 완화를 수행합니다.
    for u in sorted_vertices:
        for v in G.Adj[u]:
            RELAX(u, v, weights)


if __name__ == "__main__":
    # 그래프 초기화
    v1 = Vertex()
    v2 = Vertex()
    v3 = Vertex()
    v4 = Vertex()

    G = Graph([v1, v2, v3, v4], [(v1, v2), (v1, v3), (v2, v4), (v3, v4)])
    G.Adj = {
        v1: [v2, v3],
        v2: [v4],
        v3: [v4],
        v4: []
    }
    weights = {(v1, v2): 5, (v1, v3): 3, (v2, v4): 2, (v3, v4): 1}

    # 위상 정렬 실행
    sorted_vertices = topological_sort(G)
    print("Topologically sorted vertices:", sorted_vertices)

    # DAG_SHORTEST_PATHS 실행
    DAG_SHORTEST_PATHS(G, weights, v1)

    # 결과 출력
    for vertex in G.V:
        print(f"Distance from {v1} to {vertex}: {vertex.d}")
