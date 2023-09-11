from collections import defaultdict, deque

class Graph:
    def __init__(self, vertices):
        self.vertices = vertices
        self.graph = defaultdict(list)  # 인접 리스트를 저장하기 위한 딕셔너리

    def create_edge(self, u, v):
        self.graph[u].append(v)  # u의 인접 리스트에 v 추가

    def topological_sort(self):
        indegree_count = [0] * self.vertices  # 모든 정점의 진입차수를 0으로 초기화

        for key in self.graph:
            for item in self.graph[key]:
                indegree_count[item] += 1  # 진입차수 카운트 증가

        Q = deque()

        for i in range(self.vertices):
            if indegree_count[i] == 0:  # 진입차수가 0인 정점을 큐에 넣는다.
                Q.append(i)

        visited_node = 0  # 방문한 정점 수
        order = []  # 위상 순서를 저장할 리스트

        while Q:  # 큐가 비어있지 않으면 반복
            u = Q.popleft()
            order.append(u)  # 결과 리스트에 추가

            for v in self.graph[u]:  # u의 인접 리스트 순회
                indegree_count[v] -= 1  # 진입차수 감소
                if indegree_count[v] == 0:  # 진입차수가 0이면
                    Q.append(v)  # 큐에 추가

            visited_node += 1  # 방문한 정점 수 증가

        if visited_node != self.vertices:  # 모든 정점을 방문하지 않은 경우
            print("There's a cycle present in the Graph.\nGiven graph is not DAG")
            return

        for vertice in order:  # 결과 리스트 출력
            print(vertice, end=" ")

if __name__ == "__main__":
    G = Graph(6)  # 6개의 정점으로 그래프 생성
    G.create_edge(0, 1)  # 간선 추가
    G.create_edge(0, 2)
    G.create_edge(1, 3)
    G.create_edge(1, 5)
    G.create_edge(2, 3)
    G.create_edge(2, 5)
    G.create_edge(3, 4)
    G.create_edge(5, 4)
    G.topological_sort()  # 위상 정렬 실행
