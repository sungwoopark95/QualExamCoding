from __future__ import annotations

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