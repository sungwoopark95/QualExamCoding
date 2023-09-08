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


class MinHeap:
    def __init__(self) -> None:
        self.heap = []
        
    def __str__(self):
        return str([item.name for item in self.heap])
    
    def __contains__(self, item):
        return item in self.heap
        
    def getSize(self) -> int:
        return len(self.heap)
    
    def isEmpty(self) -> bool:
        return self.getSize() == 0

    def __min_heapify(self, array:List[Vertex], root:int, last:int) -> None:
        # root, last -> index
        # array -> list of vertices
        smallest = root
        left_child = (2 * root) + 1
        right_child = (2 * root) + 2

        # check if there is any child whose value is smaller than the parent
        if left_child < last and array[left_child].key < array[smallest].key:
            smallest = left_child
        if right_child < last and array[right_child].key < array[smallest].key:
            smallest = right_child
        
        # if smaller child exists, change
        if smallest != root:
            array[root], array[smallest] = array[smallest], array[root]
            # recursively modify the affected subtree
            self.__min_heapify(array, smallest, last)

    def build_heap(self) -> None:
        for i in range(self.getSize()//2-1, -1, -1):
            self.__min_heapify(self.heap, i, self.getSize())
    
    def push(self, val):
        self.heap.append(val)
        self.build_heap()
    
    def pop(self):
        if self.isEmpty():
            return None
        # return the minimum value
        value = self.heap.pop(0)
        self.build_heap()
        return value


def initialize_single_source(G:Graph, start:Vertex) -> None:
    for vertex in G.GetVertices():
        vertex.distance = float('inf')
        vertex.parent = None
    start.distance = 0


def relax(u:Vertex, v:Vertex, w:int) -> None:
    if v.distance > u.distance + w:
        v.distance = u.distance + w
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


def dijkstra(G:Graph, start:Vertex) -> Dict[Vertex, List[Vertex]]:
    initialize_single_source(G, start)
    Q = MinHeap()
    for vertex in G.GetVertices():
        Q.push(vertex)
    
    while not Q.isEmpty():
        u = Q.pop()
        for adj in u.GetAdjacencyList():
            relax(u, adj.end, adj.weight)
            Q.build_heap()
            
    shortest_paths = dict()
    for vertex in G.GetVertices():
        shortest_paths[vertex] = construct_path(start, vertex)
            
    return shortest_paths


def dijkstra_mst(G:Graph, start:Vertex) -> List[Tuple[Vertex]]:
    initialize_single_source(G, start)
    Q = MinHeap()
    for vertex in G.GetVertices():
        Q.push(vertex)
    
    while not Q.isEmpty():
        u = Q.pop()
        for adj in u.GetAdjacencyList():
            relax(u, adj.end, adj.weight)
            Q.build_heap()
            
    mst_edges = []
    for vertex in G.GetVertices():
        if vertex.parent:
            edge = (vertex.parent.name, vertex.name)
            mst_edges.append(edge)
            
    return mst_edges


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
    
    start = vertex_1
    shortest_paths = dijkstra(graph, start)
    for key in shortest_paths:
        print(f"Shortest path from {start.name} to {key.name}: ", end='')
        is_start = True
        for item in shortest_paths[key]:
            if not is_start:
                print(" -> ", end='')
            print(item.name, end='')
            is_start = False
        print()
        
    mst_edges = dijkstra_mst(graph, start)
    print(f"Minimum spanning tree of this graph : {mst_edges}")