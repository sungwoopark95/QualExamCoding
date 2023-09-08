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


def prim(graph:Graph, start:Vertex) -> List[str]:
    # 모든 정점의 key 값을 무한대로 설정하고, parent를 None으로 초기화
    for vertex in graph.GetVertices():
        vertex.key = float('inf')
        vertex.parent = None

    # 시작 정점의 key 값을 0으로 설정
    start.key = 0

    # MinHeap에 모든 정점을 추가
    min_heap = MinHeap()
    for vertex in graph.GetVertices():
        min_heap.push(vertex)

    mst_edges = []

    while not min_heap.isEmpty():
        # 현재 최소 key 값을 가진 정점을 추출
        current_vertex = min_heap.pop()

        # 해당 정점의 parent가 설정되어 있다면 MST에 간선 추가
        if current_vertex.parent:
            # edge = (f"Vertex {current_vertex.parent.name}", f"Vertex {current_vertex.name}", f"Weight {current_vertex.key}")
            edge = (f"Vertex {current_vertex.parent.name}", f"Vertex {current_vertex.name}")
            mst_edges.append(edge)

        # 현재 정점의 인접 리스트를 순회
        for weighted_edge in current_vertex.GetAdjacencyList():
            adjacent_vertex = weighted_edge.end
            weight = weighted_edge.weight

            # 인접 정점이 MinHeap에 있고, 가중치가 해당 정점의 현재 key 값보다 작으면 key 값을 업데이트
            if adjacent_vertex in min_heap and weight < adjacent_vertex.key:
                adjacent_vertex.parent = current_vertex
                adjacent_vertex.key = weight
                min_heap.build_heap()  # key 값이 변경되었으므로 heap을 재구성

    return mst_edges


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
    
    print(prim(graph, vertex_1))
