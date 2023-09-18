"""
[Undirected graph에서 cycle 만드는 edge 찾는 것]
undirected graph (no cycle) 만들 수 있게 중복 edge 찾아서 없애기

중복된 edge return 하기 (여러개일 경우 맨 마지막 거 return)
해당 edge가 없어져도 모든 nodes이 다 연결되는 것
"""

# Cycle이 있는지 검사하고 cycle 경로를 반환하는 함수
"""
1) hasCycle 함수는 5개의 인자를 받습니다: 
    node (현재 노드), parent (현재 노드의 부모 노드), graph (그래프의 연결 정보), visited (노드의 방문 여부), path (현재까지의 경로).

2) 함수 시작 부분에서 현재 노드(node)는 방문된 것으로 표시되며, 경로(path)에 추가됩니다.

3) 그다음 현재 노드와 연결된 이웃 노드들을 순회하기 시작합니다.

4) 만약 이웃 노드가 현재 노드의 부모 노드(parent)와 다르다면, 
    그 이웃 노드에 대해 깊이 우선 탐색을 계속 진행합니다. 
    여기서 neighbor, node의 순서로 인자를 전달하는데, node는 다음 단계에서의 parent가 됩니다. 
    즉, 현재 노드가 다음 단계의 부모 노드로 업데이트되는 것입니다.

5) 만약 이웃 노드가 이미 방문된 상태거나, 
    그 이웃 노드에서 시작하는 깊이 우선 탐색에서 사이클이 발견되면 True를 반환하여 사이클이 존재함을 알립니다.

6) 만약 사이클을 발견하지 못했다면, 경로에서 현재 노드를 제거하고 False를 반환합니다.
"""
# from typing import List

# ### -------------------------- cycle이있는지 치크하는 함수 + path update ----------------------------###
# def hasCycle(node, parent, graph, visited, path):
#     # 현재 노드를 방문 상태로 표시
#     visited[node] = True
#     # 현재 노드를 경로에 추가
#     path.append(node)
    
#     # 현재 노드와 연결된 이웃 노드들을 순회
#     for neighbor in graph[node]:
#         # 이웃 노드가 부모 노드(바로 직전에 방문한 노드)가 아닌 경우만 진행
#         if neighbor != parent:
#             # 이미 방문한 노드를 다시 방문한다면 cycle 존재
#             if visited[neighbor] or hasCycle(neighbor, node, graph, visited, path):
#                 return True
#     # 위의 조건에 해당하지 않는다면 경로에서 현재 노드를 제거
#     path.pop()
#     return False

# ### -------------------------- 모든 edges 돌면서 cycle이 있는지 체크하고 있다면 해당 path 반환 ----------------------------###
# # 주어진 간선들로부터 그래프에 cycle이 있는지 검사하고 cycle 경로를 반환
# def findCycle(edges: List[List[int]]):
    
#     n = len(edges) # 노드 개수 
    
#     # 빈 그래프 생성 (G adj list dictionary 만들기)
#     graph = {}
#     for i in range(1, n+1):
#         graph[i] = []

#     # 주어진 간선 정보를 바탕으로 양방향 그래프 구성 (Undirected graph 정보 담기)
#     for u, v in edges:
#         graph[u].append(v)
#         graph[v].append(u)
        
#     # 노드들의 방문 상태를 저장할 리스트 (node가 1부터 시작이니까)
#     visited = [False] * (n + 1)
#     # cycle 경로를 저장할 리스트
#     path = []

#     # 모든 노드에 대해 cycle이 있는지 검사 (node가 1부터 시작이니까)
#     for i in range(1, n+1):
#         # 먼저 parent는 -1로 설정
#         if not visited[i] and hasCycle(i, -1, graph, visited, path):
#             return path

#     return []

# ### -------------------------- cycle이 있는 path = 주어진 edges 중 redundant edge 뽑기 ----------------------------###
# def findRedundantConnection(edges:List[List[int]]):

#     paths = findCycle(edges)
#     if len(paths) == 0:
#         return []

#     i = 0
#     redundant = []
#     while (i != len(edges)):
#         true_cnt = 0
#         for idx in range(len(paths)):
#             if paths[idx] in edges[i]:
#                 true_cnt += 1
        
#         # edge (두 노드) 모두 cycle에 포함이면 cycle 만드는 edge
#         if true_cnt == 2: 
#             redundant.append(edges[i])
#             # print(redundant) # [[1, 2], [2, 3], [3, 4], [1, 4]]
#         i += 1
        
#     return redundant[-1]
            
            

# if __name__ == "__main__":
#     edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
#     print(findRedundantConnection(edges))  # 출력: [1, 4]
#     # print(findCycle(edges)) # [1, 2, 3, 4]
    
    
    
####### ------------------------- GNode class로 구현한 것 ---------------------- #####
from typing import List

# 그래프의 노드를 표현하는 클래스
class GNode:
    def __init__(self, id, color="W", p=None):
        self.id = id  # 노드의 아이디. 예: 1, 2, 3, ...
        self.color = color  # 노드의 방문 상태. W(White): 미방문, G(Grey): 방문 중, B(Black): 완전 방문
        self.parent = p  # 이 노드의 부모 노드

# cycle이 있는지 확인하고 있으면 path 업데이트
def hasCycle(node, graph, nodes, path):
    
    nodes[node].color = "G"  # 현재 노드를 방문 중(Grey) 상태로 변경
    path.append(node)  # 경로에 현재 노드 추가
    
    for neighbor in graph[node]:  # 현재 노드의 이웃 노드들을 탐색
        if nodes[neighbor].color == "W":  # 이웃 노드가 미방문 상태라면
            nodes[neighbor].parent = node  # 이웃 노드의 부모를 현재 노드로 설정
            
            if hasCycle(neighbor, graph, nodes, path):  # 이웃 노드에서 순환을 찾는다
                return True
            
        # 이미 방문 중인 이웃 노드를 만나고 그 이웃이 현재 노드의 부모 노드가 아니라면 순환이 있는 것으로 판단
        elif nodes[neighbor].color == "G" and nodes[node].parent != neighbor:
            return True
        
    path.pop()  # 경로에서 현재 노드 제거
    nodes[node].color = "B"  # 현재 노드를 완전 방문 상태로 변경
    
    return False

# 그래프에서 순환 경로 찾기
def findCycle(edges: List[List[int]]):
    
    n = len(edges)  # 간선의 개수
    graph = {}  # 그래프를 저장할 딕셔너리
    nodes = {}  # 노드 정보를 저장할 딕셔너리

    # 그래프 초기화 및 GNode 인스턴스 생성 (숫자 노드용 GNode랑 key 만들기)
    for i in range(1, n + 1): # 노드가 1부터 이므로 
        graph[i] = []
        nodes[i] = GNode(i)  # 각 노드를 위한 GNode 객체 생성
    
    # 그래프에 간선 정보 추가 (양방향 그래프) (G dict 만들기)
    for u, v in edges:
        graph[u].append(v)
        graph[v].append(u)
    
    path = []  # 순환 경로를 저장할 리스트
    for i in range(1, n + 1):  # 모든 노드에 대하여
        # 노드가 미방문 상태라면 순환 경로 탐색 시작
        if nodes[i].color == "W" and hasCycle(i, graph, nodes, path):
            return path
    return []

# 순환 경로에 포함된 간선 중 마지막에 추가된 간선(불필요한 연결) 찾기
def findRedundantConnection(edges: List[List[int]]) -> List[int]:
    paths = findCycle(edges)  # 순환 경로 찾기
    if len(paths) == 0:
        return []

    redundant = []  # 불필요한 연결을 저장할 리스트
    for edge in edges:
        # 간선의 양 끝 노드가 순환 경로에 포함된 경우 저장
        if edge[0] in paths and edge[1] in paths:
            redundant.append(edge)

    return redundant[-1]  # 리스트의 마지막 간선 반환

if __name__ == "__main__":
    edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
    print(findRedundantConnection(edges))  # 출력: [1, 4]
