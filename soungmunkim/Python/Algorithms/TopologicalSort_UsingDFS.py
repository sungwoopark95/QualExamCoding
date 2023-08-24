"""
[DFS을 이용해서 graph를 topological order로 나타내기]

(base) soungmunkim@gimseongmun-ui-MacBookPro Algorithms % python TopologicalSort_UsingDFS.py 
해당 그래프의 위상 정렬 결과:
5 4 2 3 1 0 
"""

from collections import defaultdict

class Graph:
    def __init__(self, vertices):
        # 정점의 개수
        self.V = vertices
        # 인접 리스트로 그래프 표현
        self.graph = defaultdict(list)

    def addEdge(self, v, w):
        """
        간선 추가 함수: v에서 w로의 간선을 그래프에 추가
        """
        self.graph[v].append(w)

    def DFSUtil(self, v, visited, stack):
        """
        DFS를 위한 도우미 함수
        """
        # 현재 노드를 방문 표시
        visited[v] = True

        # v와 인접한 모든 정점들에 대해서
        for i in self.graph[v]:
            if not visited[i]:
                self.DFSUtil(i, visited, stack)

        # 정점 v를 스택에 푸시
        stack.append(v)

    def topologicalSort(self):
        """
        위상 정렬 함수
        """
        stack = []  # 위상 정렬을 저장할 스택
        visited = [False] * self.V  # 모든 정점들을 방문하지 않은 상태로 초기화

        # 모든 정점에 대해서 DFS 수행
        for i in range(self.V):
            if not visited[i]:
                self.DFSUtil(i, visited, stack)

        # 스택의 내용을 역순으로 출력하여 위상 정렬 결과 출력
        print("해당 그래프의 위상 정렬 결과:")
        while stack:
            print(stack.pop(), end=" ")
        print()  # 줄바꿈

if __name__ == "__main__":
    g = Graph(6)
    g.addEdge(5, 2)
    g.addEdge(5, 0)
    g.addEdge(4, 0)
    g.addEdge(4, 1)
    g.addEdge(2, 3)
    g.addEdge(3, 1)

    g.topologicalSort()

