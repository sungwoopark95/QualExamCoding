from typing import List
from collections import deque
from Graph import Vertex, Graph

def BFS(start:Vertex, distance:dict) -> None:
    # initialization
    Q = [(start, 0)]
    visited = []
    
    # bfs
    while Q:
        curr_node, curr_distance = Q.pop(0)
        if curr_node not in visited:
            visited.append(curr_node)
            distance[curr_node] = curr_distance
            for adj in curr_node.GetAdjacencyList():
                if adj not in visited:
                    Q.append((adj, curr_distance + 1))


def BFS_dict(start:Vertex, distance:dict) -> None:
    # initialization
    Q = [(start, 0)]
    visited = dict()
    
    while Q:
        curr_node, curr_distance = Q.pop(0)
        if curr_node not in visited:
            visited[curr_node] = True
            distance[curr_node] = curr_distance
            for adj in curr_node.GetAdjacencyList():
                if adj not in visited:
                    Q.append((adj, curr_distance + 1))


def DFS_prob1_stack(start:Vertex, distance:dict):
    # initialization
    S = [(start, 0)]  # stack with nodes and their distances
    visited = dict()

    while S:
        curr_node, curr_dist = S.pop()
        if curr_node not in visited:
            visited[curr_node] = True
            distance[curr_node] = curr_dist
            # 현재 노드의 인접 노드 중에서 아직 방문하지 않은 노드만 스택에 추가
            # 순서대로 추가하든, 역순으로 추가하든 DFS는 정상적으로 수행되며, 그 방문 순서에 있어서만 차이가 난다.
            for adj in curr_node.GetAdjacencyList():
            # for adj in reversed(curr_node.GetAdjacencyList()):
                if adj not in visited:
                    S.append((adj, curr_dist + 1))

                
def DFS_prob1_recursion(start:Vertex, distance:dict, visited:dict, curr_dist:int):
    if start in visited and visited[start]:
        return
    visited[start] = True
    distance[start] = curr_dist
    # recursion과 stack dfs의 방문순서까지 똑같기 위해서는,
    # recursion에서 방문하는 순서와 stack에서 방문하는 순서가 반대여야 한다.
    # recursion에서 start.GetAdjacencyList() -> stack에서는 reversed(start.GetAdjacencyList())
    # recursion에서 reversed(start.GetAdjacencyList()) -> stack에서는 start.GetAdjacencyList()
    for adj in start.GetAdjacencyList():
    # for adj in reversed(start.GetAdjacencyList()):
        new_dist = curr_dist + 1
        DFS_prob1_recursion(adj, distance, visited, new_dist)
        

def DFS(vertex:Vertex, timestamp:List[int], discovery_time:dict, finishing_time:dict):
    ## python에서는 &timestamp 형태를 지원하지 않기 때문에 List로 변환
    # increase timestamp for discovery time
    timestamp[0] += 1
    
    # store discovery time fo current vertex
    discovery_time[vertex] = timestamp[0]
    
    # recursively call DFS for vertices in the adjacency list
    for adj in vertex.GetAdjacencyList():
        if adj not in discovery_time:
            DFS(adj, timestamp, discovery_time, finishing_time)
            
    # mark the finishing time when the search is done
    timestamp[0] += 1
    finishing_time[vertex] = timestamp[0]
    

def DFS_prob2_recursion_map(vertex:Vertex, timestamp:List[int], discovery_time:dict, finishing_time:dict, visited:dict):
    timestamp[0] += 1
    discovery_time[vertex] = timestamp[0]
    visited[vertex] = True
    
    for adj in vertex.GetAdjacencyList():
        if (adj not in visited) or (not visited[adj]):
            DFS_prob2_recursion_map(adj, timestamp, discovery_time, finishing_time, visited)
            
    timestamp[0] += 1
    finishing_time[vertex] = timestamp[0]
    

def DFS_prob2_stack(start:Vertex, timestamp:List[int], discovery_time:dict, finishing_time:dict):
    S = deque()  # Using deque as a stack
    visited = []  # To keep track of visited vertices
    
    S.append(start)

    while S:
        # 더 이상 방문할 인접 노드가 없다면 종료시간을 기록하고 pop을 하는 함수
        # 방문이 끝이 아니라, 방문 후 종료시간까지 기록해야 하기 때문에 아래와 같은 구현을 해야 한다.
        vertex = S[-1]  # Peek the top element without popping

        if vertex not in discovery_time:  # If not discovered yet
            timestamp[0] += 1
            discovery_time[vertex] = timestamp[0]
            visited.append(vertex)
            
            # Add unvisited adjacent vertices to the stack
            for adj in reversed(vertex.GetAdjacencyList()):
                if adj not in visited:
                    S.append(adj)
        else:
            S.pop()
            if vertex not in finishing_time:  # If finishing time not marked yet
                timestamp[0] += 1
                finishing_time[vertex] = timestamp[0]