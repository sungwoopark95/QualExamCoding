from __future__ import annotations
from typing import List
# from prim import MinHeap

class WeightedEdge:
    def __init__(self, end:Vertex, weight:int) -> None:
        self.end = end
        self.weight = weight


class Vertex:
    def __init__(self, name:str) -> None:
        self.name = name
        self.key = 0
        self.parent = None
        self.distance = 0
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
