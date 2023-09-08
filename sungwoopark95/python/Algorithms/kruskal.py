from __future__ import annotations
from typing import List

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
        

def make_set(v:Vertex) -> Vertex:
    v.parent = v
    v.key = 0
    return v

def find_set(v:Vertex) -> Vertex:
    if v != v.parent:
        v.parent = find_set(v.parent)
    return v.parent

def union(w:Vertex, v:Vertex):    
    root1 = find_set(w)
    root2 = find_set(v)
    if root1 == root2:
        return
    
    if root1.key < root2.key:
        root1.parent = root2
    elif root1.key > root2.key:
        root2.parent = root1
    else:
        root2.parent = root1
        root1.key += 1

def kruskal(G:Graph) -> List[str]:
    ans = []
    sets = dict()
    for v in G.GetVertices():
        if v not in sets:
            sets[v] = make_set(v)
        
    # create a single list of the edges in G.E
    edges = []
    for v in G.GetVertices():
        adj_edges = v.GetAdjacencyList()
        for edge in adj_edges:
            end = edge.end
            weight = edge.weight
            edges.append((v, end, weight))
    
    # sort the list of edges in increasing order by weight
    sorted_edges = sorted(edges, key=lambda x:x[2])
    
    for edge in sorted_edges:
        u, v, weight = edge
        if find_set(sets[u]) != find_set(sets[v]):
            string_edge = f"(Vertex {u.name}, Vertex {v.name})"
            ans.append(string_edge)
            union(sets[u], sets[v])
    
    return ans

# Example usage:

if __name__ == "__main__":
    graph = Graph()
    
    # generate vertices
    vertex_1 = graph.GenVertex('1')
    vertex_2 = graph.GenVertex('2')
    vertex_3 = graph.GenVertex('3')
    vertex_4 = graph.GenVertex('4')
    vertex_5 = graph.GenVertex('5')
    
    # generate edges for undirected graph by manually adding edges in both directions
    graph.GenEdge(vertex_1, vertex_2, 6)
    graph.GenEdge(vertex_2, vertex_1, 6)
    graph.GenEdge(vertex_1, vertex_3, 1)
    graph.GenEdge(vertex_3, vertex_1, 1)
    graph.GenEdge(vertex_1, vertex_4, 4)
    graph.GenEdge(vertex_4, vertex_1, 4)
    graph.GenEdge(vertex_1, vertex_5, 6)
    graph.GenEdge(vertex_5, vertex_1, 6)
    graph.GenEdge(vertex_3, vertex_5, 1)
    graph.GenEdge(vertex_5, vertex_3, 1)
    graph.GenEdge(vertex_4, vertex_2, 2)
    graph.GenEdge(vertex_2, vertex_4, 2)
    graph.GenEdge(vertex_4, vertex_5, 4)
    graph.GenEdge(vertex_5, vertex_4, 4)
    graph.GenEdge(vertex_5, vertex_2, 3)
    graph.GenEdge(vertex_2, vertex_5, 3)

    # print all vertices and their adjacency lists
    graph.PrintGraph()
    
    edges = []
    for v in graph.GetVertices():
        adj_edges = v.GetAdjacencyList()
        for edge in adj_edges:
            end = edge.end
            weight = edge.weight
            edges.append((v, end, weight))
    
    print("Before Sorting")
    for edge in edges:
        from_, to, weight = edge
        print((from_.name, to.name, weight))
    
    print("After Sorting")
    sorted_edges = sorted(edges, key=lambda x:x[2])
    for edge in sorted_edges:
        from_, to, weight = edge
        print((from_.name, to.name, weight))
        
    print(kruskal(graph))