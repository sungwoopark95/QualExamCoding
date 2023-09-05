from weighted_graph import Vertex, WeightedEdge, Graph
from typing import List

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