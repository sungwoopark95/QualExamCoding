from __future__ import annotations
from typing import List, Dict, Tuple

class WeightedEdge:
    def __init__(self, end:Vertex, weight:int) -> None:
        self.end = end
        self.weight = weight


class Vertex:
    def __init__(self, name:str) -> None:
        self.name = name
        self.key = 0
        self.parent = None
        self.adjacency_list = []
    
    def GetAdjacencyList(self) -> List[WeightedEdge]:
        return self.adjacency_list
    
    def AddToAdjacentList(self, vertex:Vertex, weight:int) -> None:
        edge = WeightedEdge(end=vertex, weight=weight)
        self.adjacency_list.append(edge)
        
        
class Graph:
    def __init__(self) -> None:
        self.vertices = []
    
    def GenVertex(self, name) -> Vertex:
        v = Vertex(name)
        self.vertices.append(v)
        return v
    
    def GenEdge(self, start:Vertex, end:Vertex, weight:int) -> None:
        start.AddToAdjacentList(vertex=end, weight=weight)
        
    def GetEdge(self) -> List[WeightedEdge]:
        edges = []
        for v in self.vertices:
            for adj in v.GetAdjacencyList():
                edges.append((v, adj.end, adj.weight))
        return edges
    
    def GetVertices(self) -> List[Vertex]:
        return self.vertices
    
    def GetNumVertices(self) -> int:
        return len(self.vertices)
    
    def PrintGraph(self) -> None:
        print("============== Defined Graph ==============")
        for vertex in self.vertices:
            print(f"Vertex {vertex.name}, Adjacency List: ", end='')
            is_first = True
            for adj in vertex.GetAdjacencyList():
                # adj : WeightedEdge object
                if not is_first:
                    print(", ", end='')
                print(f"(Vertex {adj.end.name}, Weight {adj.weight})", end='')
                is_first = False
            print()
    
    def __del__(self) -> None:
        ## unnecessary for python
        for v in self.vertices:
            del v
        del self.vertices


def initialize_single_source(G:Graph, start:Vertex) -> None:
    for vertex in G.GetVertices():
        vertex.key = float('inf')
        vertex.parent = None
    start.key = 0


def relax(u:Vertex, v:Vertex, w:int) -> None:
    if v.key > u.key + w:
        v.key = u.key + w
        v.parent = u


def construct_path(u:Vertex, v:Vertex) -> List[Vertex]:
    """u에서 v까지의 경로를 반환합니다."""
    path = []
    while v != u and v is not None:
        path.insert(0, v)
        v = v.parent
    if v == u:
        path.insert(0, u)
    return path


def topological_sort(G:Graph) -> List[Vertex]:
    def dfs(v:Vertex, visited:List[Vertex], stack:List[Vertex]):
        visited.append(v) # mark v as visited
        for adj in v.GetAdjacencyList():
            if adj.end not in visited:
                dfs(adj.end, visited, stack)
        stack.append(v)
    
    result = []  # an empty list to store the sorted elements
    visited = [] # set to keep track of visited nodes
    S = []   # an empty stack to store the topological order
    
    for vertex in G.GetVertices():
        if vertex not in visited:
            dfs(vertex, visited, S)
    
    while S:
        curr = S.pop(-1)
        result.append(curr)
        
    return result


def dag_shortest_path(G:Graph, start:Vertex) -> Dict[Vertex, List[Vertex]]:
    # initialize first
    initialize_single_source(G, start)
    # sort the vertices
    sorted_vertex = topological_sort(G)
    
    for vertex in sorted_vertex:
        for adj in vertex.GetAdjacencyList():
            relax(vertex, adj.end, adj.weight)
        
    shortest_paths = dict()    
    for v in G.GetVertices():
        shortest_paths[v] = construct_path(start, v)
    return shortest_paths


if __name__ == "__main__":
    graph = Graph()
    
    # generate vertices
    vertex_1 = graph.GenVertex('1')
    vertex_2 = graph.GenVertex('2')
    vertex_3 = graph.GenVertex('3')
    vertex_4 = graph.GenVertex('4')
    vertex_5 = graph.GenVertex('5')
    
    # generate edges
    graph.GenEdge(vertex_1, vertex_2, 6)
    graph.GenEdge(vertex_1, vertex_3, 1)
    graph.GenEdge(vertex_1, vertex_4, 4)
    graph.GenEdge(vertex_1, vertex_5, 6)
    graph.GenEdge(vertex_3, vertex_5, 1)
    graph.GenEdge(vertex_4, vertex_2, 2)
    graph.GenEdge(vertex_4, vertex_5, 4)
    graph.GenEdge(vertex_5, vertex_2, 3)

    # print all vertices and their adjacency lists
    graph.PrintGraph()
    
    print("Topological order of this graph:")
    sorted_vertex = topological_sort(graph)
    is_first = True
    for v in sorted_vertex:
        if not is_first:
            print(" -> ", end='')
        print(v.name, end='')
        is_first = False
    print()
    
    start = vertex_1
    shortest_paths = dag_shortest_path(graph, start)
    for key in shortest_paths:
        print(f"Shortest path from {start.name} to {key.name}: ", end='')
        is_start = True
        for item in shortest_paths[key]:
            if not is_start:
                print(" -> ", end='')
            print(item.name, end='')
            is_start = False
        print()