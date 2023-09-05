from weighted_graph import Vertex, WeightedEdge, Graph
from typing import List, Dict

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