"""
첫 번째 코드 (CompleteComponents 함수를 포함하는 코드)는 
그래프의 모든 정점이 연결되어 있는지 확인하는 것이 목적입니다. 
각 정점에서 시작하여 DFS를 수행하고 모든 정점을 방문할 수 있는지 확인합니다.
"""

def CompleteComponents(self, n: int, edges: List[List[int]]) -> bool:
    # n개의 노드에 대한 빈 인접 리스트 초기화
    graph = [[] for _ in range(n)]

    # 각 엣지에 대해 인접 리스트에 추가
    for (fro, to) in edges:
        graph[fro].append(to)
    print(graph)

    def dfs(graph, node, visited):
        visited[node] = True  # 현재 노드 방문 표시

        # 현재 노드에 인접한 모든 노드에 대해 탐색
        for node2 in graph[node]:
            if not visited[node2]:  # 방문하지 않은 경우에만 탐색
                dfs(graph, node2, visited)

    def isConnected(graph, n):
        for i in range(n):
            # 모든 노드에 대한 방문 여부 초기화
            visited = [False] * n

            # i번째 노드에서 DFS 시작
            dfs(graph, i, visited)

            # 모든 노드를 방문했는지 확인
            for b in visited:
                if not b:
                    return False  # 하나라도 방문하지 않은 노드가 있으면 False 반환
        return True  # 모든 노드를 방문했다면 True 반환

    isConnected(graph, n)

n = 6
edges = [[0, 1], [0, 2], [1, 2], [3, 4]]
CompleteComponents(n, edges)



"""
두 번째 코드는 그래프 내의 강하게 연결된 구성 요소(Strongly Connected Components, 
SCC)를 찾는 것이 목적입니다. 
SCC는 그래프의 하위 세트로서, 이 세트 내의 모든 정점 간에 경로가 존재합니다.
"""

# from collections import defaultdict

# UNVISITED = -1  # 방문하지 않은 상태를 나타내는 상수

# class Graph:
#     global UNVISITED

#     def __init__(self, vertices):
#         self.v = vertices
#         self.g = defaultdict(list)  # 인접 리스트로 그래프 표현
#         self.id = 0  # 각 노드에 고유한 ID를 부여하기 위한 변수

#     def addEdge(self, u, v):
#         self.g[u].append(v)  # 간선 추가

#     def findSCCs(self):
#         ids = [UNVISITED] * self.v  # 각 노드의 ID 초기화
#         low = [UNVISITED] * self.v  # 각 노드의 low-link 값 초기화
#         onStack = [False] * self.v  # 스택에 있는지의 여부
#         stack = []  # DFS를 위한 스택

#         for i in range(self.v):
#             if ids[i] == UNVISITED:  # 방문하지 않은 노드에 대해 DFS 수행
#                 self.dfs(i, low, ids, onStack, stack)

#         return low  # low-link 값 반환. 같은 값끼리 SCC

#     def dfs(self, at, low, ids, onStack, stack):
#         ids[at] = self.id
#         low[at] = self.id
#         self.id += 1  # 현재 노드에 ID 할당
#         onStack[at] = True
#         stack.append(at)

#         for to in self.g[at]:  # 인접한 모든 노드에 대해
#             if ids[to] == UNVISITED:
#                 self.dfs(to, low, ids, onStack, stack)
#                 low[at] = min(low[at], low[to])  # low-link 값 업데이트
#             elif onStack[to]:  # 스택에 있다면
#                 low[at] = min(low[at], ids[to])  # low-link 값 업데이트

#         # SCC를 찾아 출력
#         w = UNVISITED
#         if low[at] == ids[at]:
#             print("Strongly Connected Components: ", end="")
#             while w != at:
#                 w = stack.pop()
#                 print(f"Node {w}", end=" ")
#                 onStack[w] = False
#             print()

#     def __str__(self):
#         return self.print()

#     def print(self):
#         for vertice, edge in self.g.items():
#             print(f"{vertice} ->", *edge)
