"""
[directed graph 순서 나열하기 (topological order)]

There are a total of numCourses courses you have to take, 
    labeled from 0 to numCourses - 1. 
You are given an array prerequisites 
    where prerequisites[i] = [ai, bi] indicates that 
    you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 
you have to first take course 1. (directed graph)
Return the ordering of courses you should take to finish all courses. 
If there are many valid answers, return any of them. 
If it is impossible to finish all courses, return an empty array.


Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So the correct course order is [0,1].

numCourses = 4
prerequisites = [[1,0],[2,0],[3,1],[3,2]]
findOrder(numCourses, prerequisites)
[0, 1, 2, 3]

numCourses = 1
prerequisites = []
findOrder(numCourses, prerequisites)
[0]
"""

from typing import List
def findOrder(numCourses: int, prerequisites: List[List[int]]) -> List[int]:
    G = dict()
    # number of courses만큼 graph adj list 만들기
    for i in range(numCourses):
        G[i] = []
        
    # 각 edge들 정보 추가하기 (directed)
    for i in range(len(prerequisites)):
        want = prerequisites[i][0]
        pre = prerequisites[i][1]
        
        G[pre].append(want)
        
    # topological sort 
    indegree = [0] * len(G) # 모든 노드의 진입차수를 0으로 초기화
    
    # 각 노드의 진입 차수 계산함
    """
    indegree 리스트는 각 노드의 초기 진입 차수를 저장하는 데 사용
    prerequisites = [[1,0],[2,0],[3,1],[3,2]]
    numCourses = 4

    이를 그래프로 나타내면 다음과 같습니다:
    0 -> 1
    0 -> 2
    1 -> 3
    2 -> 3

    따라서 진입 차수는 다음과 같습니다.
    0: 0
    1: 1
    2: 1
    3: 2
    """
    # 얼마나 들어오는 edges가 많은지
    for key in G:
        for neighbor in G[key]:
            indegree[neighbor] += 1
            
    Q = []
    for i in range(len(G)):
        if indegree[i] == 0:  # 진입차수가 0인 node를 큐에 넣는다.
            Q.append(i)
    
    order = [] # 위상 순서를 저장할 리스트

    while Q: # 큐가 비어있지 않으면 반복
        cur = Q.pop(0)
        order.append(cur) # 현재 node 리스트에 추가
        
        for adj in G[cur]: # 인접 노드 돌기
            indegree[adj] -= 1 # 인접 노드의 진입 차수 감소
            if indegree[adj] == 0: # 진입차수가 0이면 Q 추가
                Q.append(adj)
        

    # 모든 정점을 방문하지 않은 경우 (cycle 존재함)
    # 사이클을 형성하는 노드들 중 
    # 어느 노드도 진입 차수가 0이 되지 않기 때문에 큐에 들어가지 않게 됩니다.
    if len(order) != len(G):
        return []
    else:
        return order
    

## ------------------ GNode class 버전으로 구현 -------------------- ##
# from typing import List

# class GNode:
#     def __init__(self, id):
#         self.id = id                 # 노드의 ID 혹은 번호
#         self.out_nodes = []          # 이 노드로부터 나가는 간선의 목록
#         self.in_degree = 0           # 이 노드로 들어오는 간선의 개수 (진입차수)

# def findOrder(numCourses: int, prerequisites: List[List[int]]) -> List[int]:
#     # 각 번호를 가진 GNode 객체로 그래프 초기화
#     graph = {i: GNode(i) for i in range(numCourses)}

#     # 그래프 구성하기
#     for pair in prerequisites:
#         next_course, prev_course = pair
#         graph[prev_course].out_nodes.append(next_course)   # 나가는 간선 정보 추가
#         graph[next_course].in_degree += 1                  # 진입차수 증가

#     # 진입차수가 0인 노드들로 큐 초기화
#     queue = [k for k in graph if graph[k].in_degree == 0]

#     order = []  # 위상 정렬 결과를 저장할 리스트

#     # 큐를 이용한 위상 정렬 수행
#     while queue:
#         node = queue.pop(0)  # 큐의 앞에서 노드 추출
#         order.append(node)   # 결과 리스트에 노드 추가

#         # 현재 노드의 나가는 간선에 연결된 노드들의 진입차수 감소
#         for next_node in graph[node].out_nodes:
#             graph[next_node].in_degree -= 1
#             # 진입차수가 0이 된 노드는 큐에 추가
#             if graph[next_node].in_degree == 0:
#                 queue.append(next_node)

#     # 모든 과목을 수강할 수 있는지 확인. 만약 가능하다면 위상 정렬 결과 반환, 그렇지 않다면 빈 리스트 반환
#     return order if len(order) == numCourses else []
