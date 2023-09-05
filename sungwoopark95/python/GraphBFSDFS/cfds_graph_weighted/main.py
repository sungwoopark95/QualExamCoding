from weighted_graph import Graph

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
    graph.GenEdge(vertex_u, vertex_v, 1)
    graph.GenEdge(vertex_u, vertex_x, 2)
    graph.GenEdge(vertex_v, vertex_y, 3)
    graph.GenEdge(vertex_w, vertex_y, 4)
    graph.GenEdge(vertex_w, vertex_z, 5)
    graph.GenEdge(vertex_x, vertex_v, 6)
    graph.GenEdge(vertex_y, vertex_x, 7)
    graph.GenEdge(vertex_z, vertex_z, 8)

    # print all vertices and their adjacency lists
    graph.PrintGraph()


if __name__ == "__main__":
    ShowcaseGraph()