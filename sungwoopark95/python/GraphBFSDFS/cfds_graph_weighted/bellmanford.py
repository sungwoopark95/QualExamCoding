from weighted_graph import WeightedEdge, Vertex, Graph
from typing import List, Dict, Tuple

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


def bellman_ford_check_cycle(G:Graph, start:Vertex) -> bool:
    initialize_single_source(G, start)
    
    for _ in range(1, G.GetNumVertices()):
        for edge in G.GetEdge():
            u, v, w = edge
            relax(u, v, w)
    
    # check negative cycle
    for edge in G.GetEdge():
        u, v, w = edge
        if v.distance > u.distance + w:
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
            