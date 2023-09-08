from __future__ import annotations
import sys
from typing import List
from collections import deque

class Vertex:
    def __init__(self, name) -> None:
        self.name = name
        self.adjacency_list = []
    
    def GetName(self) -> str:
        return self.name
    
    def GetAdjacencyList(self) -> list:
        return self.adjacency_list
    
    def AddToAdjacentList(self, vertex:Vertex) -> None:
        self.adjacency_list.append(vertex)


class Graph:
    def __init__(self) -> None:
        self.vertices = []
    
    def GenVertex(self, name) -> Vertex:
        v = Vertex(name)
        self.vertices.append(v)
        return v
    
    def GenEdge(self, start:Vertex, end:Vertex) -> None:
        start.AddToAdjacentList(end)
    
    def GetVertices(self) -> list:
        return self.vertices
    
    def GetNumVertices(self) -> int:
        return len(self.vertices)
    
    def PrintGraph(self) -> None:
        print("============== Defined Graph ==============")
        for vertex in self.vertices:
            print(f"Vertex {vertex.GetName()}, Adjacency List: ", end='')
            is_first = True
            for adj in vertex.GetAdjacencyList():
                if not is_first:
                    print(", ", end='')
                print(f"Vertex {adj.GetName()}", end='')
                is_first = False
            print()
    
    def __del__(self) -> None:
        ## unnecessary for python
        for v in self.vertices:
            del v
        del self.vertices


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


if __name__ == "__main__":
    def ShowcaseGraph() -> None:
        graph = Graph()
        
        # generate vertices
        vertex_u = graph.GenVertex('u')
        vertex_v = graph.GenVertex('v')
        vertex_w = graph.GenVertex('w')
        vertex_x = graph.GenVertex('x')
        vertex_y = graph.GenVertex('y')
        vertex_z = graph.GenVertex('z')
        
        # generate edges
        graph.GenEdge(vertex_u, vertex_v)
        graph.GenEdge(vertex_u, vertex_x)
        graph.GenEdge(vertex_v, vertex_y)
        graph.GenEdge(vertex_w, vertex_y)
        graph.GenEdge(vertex_w, vertex_z)
        graph.GenEdge(vertex_x, vertex_v)
        graph.GenEdge(vertex_y, vertex_x)
        graph.GenEdge(vertex_z, vertex_z)

        # print all vertices and their adjacency lists
        graph.PrintGraph()


    def ShowcaseBFS() -> None:
        # generate graph instance that manages vertices and edges
        graph = Graph()

        # generate vertices
        vertex_r = graph.GenVertex("r")
        vertex_s = graph.GenVertex("s")
        vertex_t = graph.GenVertex("t")
        vertex_u = graph.GenVertex("u")
        vertex_v = graph.GenVertex("v")
        vertex_w = graph.GenVertex("w")
        vertex_x = graph.GenVertex("x")
        vertex_y = graph.GenVertex("y")

        # generate edges
        graph.GenEdge(vertex_r, vertex_s) 
        graph.GenEdge(vertex_s, vertex_r)
        graph.GenEdge(vertex_r, vertex_v) 
        graph.GenEdge(vertex_v, vertex_r)
        graph.GenEdge(vertex_s, vertex_w) 
        graph.GenEdge(vertex_w, vertex_s)
        graph.GenEdge(vertex_t, vertex_w) 
        graph.GenEdge(vertex_w, vertex_t)
        graph.GenEdge(vertex_t, vertex_x) 
        graph.GenEdge(vertex_x, vertex_t)
        graph.GenEdge(vertex_t, vertex_u) 
        graph.GenEdge(vertex_u, vertex_t)
        graph.GenEdge(vertex_u, vertex_x) 
        graph.GenEdge(vertex_x, vertex_u)
        graph.GenEdge(vertex_u, vertex_y) 
        graph.GenEdge(vertex_y, vertex_u)
        graph.GenEdge(vertex_w, vertex_x) 
        graph.GenEdge(vertex_x, vertex_w)
        graph.GenEdge(vertex_x, vertex_y) 
        graph.GenEdge(vertex_y, vertex_x)

        # print all vertices and its their adjacency lists
        graph.PrintGraph()
        
        # do BFS
        distance = dict()
        visited = dict()
        dist = 0
        
        # BFS(vertex_s, distance)
        # BFS_dict(vertex_s, distance)
        # DFS_prob1_stack(vertex_s, distance)
        DFS_prob1_recursion(vertex_s, distance, visited, 0)
        
        print("=============== BFS Result ===============")
        for vertex in graph.GetVertices():
            print(f"Vertex {vertex.GetName()}, ", end='')
            print(f"Distance: {distance[vertex]}")


    def ShowcaseDFS() -> None:
        graph = Graph()
        
        vertex_u = graph.GenVertex("u")
        vertex_v = graph.GenVertex("v")
        vertex_w = graph.GenVertex("w")
        vertex_x = graph.GenVertex("x")
        vertex_y = graph.GenVertex("y")
        vertex_z = graph.GenVertex("z")
        
        graph.GenEdge(vertex_u, vertex_v)
        graph.GenEdge(vertex_u, vertex_x)
        graph.GenEdge(vertex_v, vertex_y)
        graph.GenEdge(vertex_w, vertex_y)
        graph.GenEdge(vertex_w, vertex_z)
        graph.GenEdge(vertex_x, vertex_v)
        graph.GenEdge(vertex_y, vertex_x)
        graph.GenEdge(vertex_z, vertex_z)
        
        graph.PrintGraph()
        
        ## do DFS
        timestamp = [0]
        discovery_time = dict()
        finishing_time = dict()
        visited = dict()
        
        for vertex in graph.GetVertices():
            # if the vertex is not visited yet
            if vertex not in discovery_time:
                # DFS(vertex, timestamp, discovery_time, finishing_time)
                # DFS_prob2_recursion_map(vertex, timestamp, discovery_time, finishing_time, visited)
                DFS_prob2_stack(vertex, timestamp, discovery_time, finishing_time)
                
        print("=============== DFS Result ===============")
        for vertex in graph.GetVertices():
            print(f"Vertex {vertex.GetName()}, Discovery time: {discovery_time[vertex]}, Finishing time: {finishing_time[vertex]}")

    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} [selector]")
        print("Selector 0: Showcase graph")
        print("Selector 1: Showcase Breadth-First Search")
        print("Selector 2: Showcase Depth-First Search")
        sys.exit(1)

    selector = int(sys.argv[1])
    if selector == 0:
        ShowcaseGraph()
    elif selector == 1:
        ShowcaseBFS()
    elif selector == 2:
        ShowcaseDFS()

    sys.exit(0)