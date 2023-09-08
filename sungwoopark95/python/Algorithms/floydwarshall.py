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


def relax(u:Vertex, v:Vertex, w:int) -> None:
    if v.key > u.key + w:
        v.key = u.key + w
        v.parent = u
        

def initialize_adj_matrix(G:Graph) -> List[List[int]]:
    W = [[0 for _ in range(G.GetNumVertices())] for _ in range(G.GetNumVertices())]
    for i, u in enumerate(G.GetVertices()):
        for j, v in enumerate(G.GetVertices()):
            if u == v:
                W[i][j] = 0
            else:
                adj_vertices = [edge.end for edge in u.GetAdjacencyList()]
                if v in adj_vertices:
                    idx = adj_vertices.index(v)
                    weight = u.GetAdjacencyList()[idx].weight
                    W[i][j] = weight
                else:
                    W[i][j] = float('inf')
    return W


def floyd_warshall(G:Graph) -> Tuple[List[List[float]], List[List[int]]]:
    n = G.GetNumVertices()
    W = initialize_adj_matrix(G)
    
    d = [[0 for _ in range(n)] for _ in range(n)]
    parents = [[None for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            d[i][j] = W[i][j]
            if i != j and W[i][j] != float('inf'):
                parents[i][j] = i

    # k, i, j => i, j, k
    for k in range(n):
        for i in range(n):
            for j in range(n):
                if d[i][k] + d[k][j] < d[i][j]:
                    d[i][j] = d[i][k] + d[k][j]
                    parents[i][j] = parents[k][j]
    
    return d, parents


def construct_path(pred:List[List[int]], start:int, end:int) -> List[int]:
    path = []
    def recursion(pred, i, j):
        if i == j or pred[i][j] == None:
            # print(i, end=' ')
            path.append(i)
            return
        recursion(pred, i, pred[i][j])
        # print(j, end=' ')
        path.append(j)
    
    recursion(pred, start, end)
    return path


def floyd_warshall_shortest_paths(G:Graph, start:Vertex) -> Dict[Vertex, List[Vertex]]:
    _, predecessors = floyd_warshall(G)
    vertices = G.GetVertices()
    start_idx = vertices.index(start)
    
    shortest_paths = dict()
    for j, v in enumerate(vertices):
        id_paths = construct_path(predecessors, start_idx, j)
        shortest_paths[v] = [vertices[id] for id in id_paths]
    return shortest_paths


if __name__ == "__main__":
    graph = Graph()

    node0 = graph.GenVertex(0)
    node1 = graph.GenVertex(1)
    node2 = graph.GenVertex(2)
    node3 = graph.GenVertex(3)

    graph.GenEdge(node0, node1, 3)
    graph.GenEdge(node1, node2, 1)
    graph.GenEdge(node1, node3, 4)
    graph.GenEdge(node1, node0, 3)
    graph.GenEdge(node2, node1, 1)
    graph.GenEdge(node2, node3, 1)
    graph.GenEdge(node3, node1, 4)
    graph.GenEdge(node3, node2, 1)
    
    # # generate vertices
    # vertex_1 = graph.GenVertex('1')
    # vertex_2 = graph.GenVertex('2')
    # vertex_3 = graph.GenVertex('3')
    # vertex_4 = graph.GenVertex('4')
    # vertex_5 = graph.GenVertex('5')
    
    # # generate edges
    # graph.GenEdge(vertex_1, vertex_2, 6)
    # graph.GenEdge(vertex_1, vertex_3, 1)
    # graph.GenEdge(vertex_1, vertex_4, 4)
    # graph.GenEdge(vertex_1, vertex_5, 6)
    # graph.GenEdge(vertex_3, vertex_5, 1)
    # graph.GenEdge(vertex_4, vertex_2, 2)
    # graph.GenEdge(vertex_4, vertex_5, 4)
    # graph.GenEdge(vertex_5, vertex_2, 3)

    # print all vertices and their adjacency lists
    graph.PrintGraph()
    print(initialize_adj_matrix(graph))
    
    distance, parents = floyd_warshall(graph)
    print(distance)
    print(parents)
    
    for v in graph.GetVertices():
        start = v
        shortest_paths = floyd_warshall_shortest_paths(graph, start)
        for key in shortest_paths:
            print(f"Shortest path from {start.name} to {key.name}: ", end='')
            is_start = True
            for item in shortest_paths[key]:
                if not is_start:
                    print(" -> ", end='')
                print(item.name, end='')
                is_start = False
            print(f" distance: {distance[graph.GetVertices().index(start)][graph.GetVertices().index(key)]}")
        print("================================= DONE =================================")