import sys
from Graph import Vertex, Graph
from Search import *

def ShowcaseGraph() -> None:
    graph = Graph()
    
    # generate vertices
    vertex_u = graph.GenVertex('u')
    vertex_v = graph.GenVertex('v')
    vertex_w = graph.GenVertex('w')
    vertex_x = graph.GenVertex('x')
    vertex_y = graph.GenVertex('y')
    vertex_z = graph.GenVertex('z')
    
    # generate edges
    graph.GenEdge(vertex_u, vertex_v)
    graph.GenEdge(vertex_u, vertex_x)
    graph.GenEdge(vertex_v, vertex_y)
    graph.GenEdge(vertex_w, vertex_y)
    graph.GenEdge(vertex_w, vertex_z)
    graph.GenEdge(vertex_x, vertex_v)
    graph.GenEdge(vertex_y, vertex_x)
    graph.GenEdge(vertex_z, vertex_z)

    # print all vertices and their adjacency lists
    graph.PrintGraph()


def ShowcaseBFS() -> None:
    # generate graph instance that manages vertices and edges
    graph = Graph()

    # generate vertices
    vertex_r = graph.GenVertex("r")
    vertex_s = graph.GenVertex("s")
    vertex_t = graph.GenVertex("t")
    vertex_u = graph.GenVertex("u")
    vertex_v = graph.GenVertex("v")
    vertex_w = graph.GenVertex("w")
    vertex_x = graph.GenVertex("x")
    vertex_y = graph.GenVertex("y")

    # generate edges
    graph.GenEdge(vertex_r, vertex_s) 
    graph.GenEdge(vertex_s, vertex_r)
    graph.GenEdge(vertex_r, vertex_v) 
    graph.GenEdge(vertex_v, vertex_r)
    graph.GenEdge(vertex_s, vertex_w) 
    graph.GenEdge(vertex_w, vertex_s)
    graph.GenEdge(vertex_t, vertex_w) 
    graph.GenEdge(vertex_w, vertex_t)
    graph.GenEdge(vertex_t, vertex_x) 
    graph.GenEdge(vertex_x, vertex_t)
    graph.GenEdge(vertex_t, vertex_u) 
    graph.GenEdge(vertex_u, vertex_t)
    graph.GenEdge(vertex_u, vertex_x) 
    graph.GenEdge(vertex_x, vertex_u)
    graph.GenEdge(vertex_u, vertex_y) 
    graph.GenEdge(vertex_y, vertex_u)
    graph.GenEdge(vertex_w, vertex_x) 
    graph.GenEdge(vertex_x, vertex_w)
    graph.GenEdge(vertex_x, vertex_y) 
    graph.GenEdge(vertex_y, vertex_x)

    # print all vertices and its their adjacency lists
    graph.PrintGraph()
    
    # do BFS
    distance = dict()
    visited = dict()
    dist = 0
    
    # BFS(vertex_s, distance)
    # BFS_dict(vertex_s, distance)
    # DFS_prob1_stack(vertex_s, distance)
    DFS_prob1_recursion(vertex_s, distance, visited, 0)
    
    print("=============== BFS Result ===============")
    for vertex in graph.GetVertices():
        print(f"Vertex {vertex.GetName()}, ", end='')
        print(f"Distance: {distance[vertex]}")


def ShowcaseDFS() -> None:
    graph = Graph()
    
    vertex_u = graph.GenVertex("u")
    vertex_v = graph.GenVertex("v")
    vertex_w = graph.GenVertex("w")
    vertex_x = graph.GenVertex("x")
    vertex_y = graph.GenVertex("y")
    vertex_z = graph.GenVertex("z")
    
    graph.GenEdge(vertex_u, vertex_v)
    graph.GenEdge(vertex_u, vertex_x)
    graph.GenEdge(vertex_v, vertex_y)
    graph.GenEdge(vertex_w, vertex_y)
    graph.GenEdge(vertex_w, vertex_z)
    graph.GenEdge(vertex_x, vertex_v)
    graph.GenEdge(vertex_y, vertex_x)
    graph.GenEdge(vertex_z, vertex_z)
    
    graph.PrintGraph()
    
    ## do DFS
    timestamp = [0]
    discovery_time = dict()
    finishing_time = dict()
    visited = dict()
    
    for vertex in graph.GetVertices():
        # if the vertex is not visited yet
        if vertex not in discovery_time:
            # DFS(vertex, timestamp, discovery_time, finishing_time)
            # DFS_prob2_recursion_map(vertex, timestamp, discovery_time, finishing_time, visited)
            DFS_prob2_stack(vertex, timestamp, discovery_time, finishing_time)
            
    print("=============== DFS Result ===============")
    for vertex in graph.GetVertices():
        print(f"Vertex {vertex.GetName()}, Discovery time: {discovery_time[vertex]}, Finishing time: {finishing_time[vertex]}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} [selector]")
        print("Selector 0: Showcase graph")
        print("Selector 1: Showcase Breadth-First Search")
        print("Selector 2: Showcase Depth-First Search")
        sys.exit(1)

    selector = int(sys.argv[1])
    if selector == 0:
        ShowcaseGraph()
    elif selector == 1:
        ShowcaseBFS()
    elif selector == 2:
        ShowcaseDFS()

    sys.exit(0)