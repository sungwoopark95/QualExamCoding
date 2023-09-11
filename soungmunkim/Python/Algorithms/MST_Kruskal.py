# Kruskal's algorithm in Python

# 그래프 클래스 정의
class Graph:
    # 초기화 함수
    def __init__(self, vertices):
        self.V = vertices  # 정점의 수
        self.graph = []  # 그래프 정보를 저장할 리스트

    # 그래프에 간선 추가 함수
    def add_edge(self, u, v, w):
        self.graph.append([u, v, w])  # u, v 사이의 가중치 w를 가진 간선 추가

    # 부모 노드를 찾는 함수
    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])

    # 두 노드의 부모를 합치는 함수 (Union 연산)
    def apply_union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)
        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    # 크루스칼 알고리즘을 적용하는 함수
    def kruskal_algo(self):
        result = []  # 최소 스패닝 트리의 간선을 저장할 리스트
        i, e = 0, 0
        # 간선들을 가중치를 기준으로 정렬
        self.graph = sorted(self.graph, key=lambda item: item[2])
        parent = []
        rank = []
        # 모든 노드에 대해 초기 부모와 랭크를 설정
        for node in range(self.V):
            parent.append(node)
            rank.append(0)
        # V-1개의 간선을 선택할 때까지 반복
        while e < self.V - 1:
            u, v, w = self.graph[i]
            i = i + 1
            x = self.find(parent, u)
            y = self.find(parent, v)
            # 선택한 두 노드의 부모가 다른 경우, 최소 스패닝 트리에 간선 추가
            if x != y:
                e = e + 1
                result.append([u, v, w])
                self.apply_union(parent, rank, x, y)
        # 결과 출력
        for u, v, weight in result:
            print("%d - %d: %d" % (u, v, weight))

# 그래프 객체 생성
g = Graph(6)
# 간선 정보 추가
g.add_edge(0, 1, 4)
g.add_edge(0, 2, 4)
g.add_edge(1, 2, 2)
g.add_edge(1, 0, 4)
g.add_edge(2, 0, 4)
g.add_edge(2, 1, 2)
g.add_edge(2, 3, 3)
g.add_edge(2, 5, 2)
g.add_edge(2, 4, 4)
g.add_edge(3, 2, 3)
g.add_edge(3, 4, 3)
g.add_edge(4, 2, 4)
g.add_edge(4, 3, 3)
g.add_edge(5, 2, 2)
g.add_edge(5, 4, 3)
# 크루스칼 알고리즘 실행
g.kruskal_algo()
