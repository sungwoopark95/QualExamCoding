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


def bellman_ford_check_cycle(G:Graph, start:Vertex) -> bool:
    initialize_single_source(G, start)
    
    for _ in range(1, G.GetNumVertices()):
        for edge in G.GetEdge():
            u, v, w = edge
            relax(u, v, w)
    
    # check negative cycle
    for edge in G.GetEdge():
        u, v, w = edge
        if v.key > u.key + w:
            return False
    return True


def bellman_ford_mst(G:Graph, start:Vertex) -> List[Tuple[Vertex]]:
    initialize_single_source(G, start)

    for _ in range(1, G.GetNumVertices()):
        for edge in G.GetEdge():
            u, v, w = edge
            relax(u, v, w)
    
    mst = []
    for v in G.GetVertices():
        if v.parent:
            edge = (v.parent.name, v.name)
            mst.append(edge)
    return mst


def bellman_ford_shortest_paths(G:Graph, start:Vertex) -> Dict[Vertex, List[Vertex]]:
    shortest_paths = dict()
    initialize_single_source(G, start)
    for _ in range(1, G.GetNumVertices()):
        for edge in G.GetEdge():
            u, v, w = edge
            relax(u, v, w)
    
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
    
    # check if there exists any negative cycle in the graph
    print(f"Is this graph acyclic? : {bellman_ford_check_cycle(graph, vertex_1)}")
    
    start = vertex_1
    print(f"Minimum spanning tree of this graph : {bellman_ford_mst(graph, start)}")
    shortest_paths = bellman_ford_shortest_paths(graph, start)
    for key in shortest_paths:
        print(f"Shortest path from {start.name} to {key.name}: ", end='')
        is_start = True
        for item in shortest_paths[key]:
            if not is_start:
                print(" -> ", end='')
            print(item.name, end='')
            is_start = False
        print()
            