"""
[Single Source Shortest Paths - Bellman Ford Algorithm]
그래프의 최단 경로 (minimum weight)를 찾는 알고리즘
negative weights 포함 가능하며 negative cycle 찾을 수 있음

True/False 로 반환하는 코드지만 path 반환 코드도 넣어놓음

"""

class Edge:
    def __init__(self, u, v, weight):
        self.u = u
        self.v = v
        self.weight = weight

class Graph:
    def __init__(self, V, E):
        self.V = V
        self.E = E
        self.edges = []

    # 그래프에 에지를 추가하는 함수
    def addEdge(self, u, v, weight):
        self.edges.append(Edge(u, v, weight))

# 시작 정점에서의 거리와 선행 정점을 초기화하는 함수
def Initialize_Single_Source(g, source):
    distance = [float('inf')] * g.V
    predecessor = [-1] * g.V
    distance[source] = 0
    return distance, predecessor

# 에지에 대한 Relax 연산을 수행하는 함수
def Relax(u, v, weight, distance, predecessor):
    if distance[v] > distance[u] + weight:
        distance[v] = distance[u] + weight
        predecessor[v] = u

# Bellman-Ford 알고리즘을 수행하는 함수
def Bellman_Ford(g, source, weights):
    distance, predecessor = Initialize_Single_Source(g, source)

    for _ in range(g.V - 1):
        for edge in g.edges:
            Relax(edge.u, edge.v, weights[(edge.u, edge.v)], distance, predecessor)

    for edge in g.edges:
        if distance[edge.v] > distance[edge.u] + weights[(edge.u, edge.v)]:
            return False, distance, predecessor

    return True, distance, predecessor

# 특정 목적지까지의 최단 경로를 반환하는 함수
def GetShortestPath(source, destination, predecessor):
    path = []
    while destination != -1:
        path.append(destination)
        destination = predecessor[destination]
    path.reverse()
    return path

def main():
    V = 5
    E = 8
    g = Graph(V, E)

    g.addEdge(0, 1, -1)
    g.addEdge(0, 2, 4)
    g.addEdge(1, 2, 3)
    g.addEdge(1, 3, 2)
    g.addEdge(1, 4, 2)
    g.addEdge(3, 2, 5)
    g.addEdge(3, 1, 1)
    g.addEdge(4, 3, -3)

    # 가중치를 딕셔너리 형태로 정의
    weights = {
        (0, 1): -1,
        (0, 2): 4,
        (1, 2): 3,
        (1, 3): 2,
        (1, 4): 2,
        (3, 2): 5,
        (3, 1): 1,
        (4, 3): -3
    }

    success, distance, predecessor = Bellman_Ford(g, 0, weights)

    if success:
        print("최단 경로가 성공적으로 계산되었습니다!")
        for i in range(V):
            path = GetShortestPath(0, i, predecessor)
            print(f"0 -> {i} (distance: {distance[i]}): {' -> '.join(map(str, path))}")
            # print(f"0 -> {i}: {' -> '.join(map(str, path))}") # shortest path만 반환하고 싶을 때
    else:
        print("그래프에 음수 가중치의 사이클이 존재합니다!")

if __name__ == "__main__":
    main()
