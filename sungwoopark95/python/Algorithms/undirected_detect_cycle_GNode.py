from typing import List, Dict

# GNode version
class GNode:
    def __init__(self, id):
        self.id = id
        self.parent = None
        self.distance = 0
    
    def __str__(self):
        return self.id
    
def list_to_gnode_graph(edges:List[List[int]]) -> Dict[GNode, List[GNode]]:
    nodes = []
    for edge in edges:
        from_, to = edge
        if from_ not in nodes:
            nodes.append(from_)
        if to not in nodes:
            nodes.append(to)

    node_dict = dict()
    for node in nodes:
        node_dict[node] = GNode(node)
    
    graph = dict()
    for edge in edges:
        from_, to = edge
        from_node, to_node = node_dict[from_], node_dict[to]
        if from_node in graph:
            graph[from_node].append(to_node)
        else:
            graph[from_node] = [to_node]
        
        if to_node in graph:
            graph[to_node].append(from_node)
        else:
            graph[to_node] = [from_node]
    return graph

def printGraph(G:dict):
    for key in G:
        print(f"{key.id} : {[node.id for node in G[key]]}")
    
def find(x:GNode) -> GNode:
    if x.parent != x:
        x.parent = find(x.parent)
    return x.parent

def union(x:GNode, y:GNode):
    rootX = find(x)
    rootY = find(y)
    if rootX == rootY:
        return False # already connected - cycle
    rootX.parent = rootY
    return True # not connected - can be connected

def detect_undirected_cycle(G:Dict[GNode, List[GNode]]):
    # parent initialization
    for key in G:
        key.parent = key
    
    # cycle detection
    visited_edges =[]  # add this line to track visited edges
    for key in G:
        for adj in G[key]:
            edge = [min(key.id, adj.id), max(key.id, adj.id)]
            if edge in visited_edges:
                continue
            visited_edges.append(edge)
            if not union(key, adj):
                print("Cycle detected!")
                return True
    print("No cycle.")
    return False


if __name__ == "__main__":
    # r, s, t, u, v = GNode('r'), GNode('s'), GNode('t'), GNode('u'), GNode('v')
    # w, x, y = GNode('w'), GNode('x'), GNode('y')

    # G = dict()
    # G[r], G[s], G[t], G[u], G[v] = [s, v], [w, r], [w, x, u], [t, x, y], [r]
    # G[w], G[x], G[y] = [s, t, x], [w, t, u, y], [x, u]
    
    edges = [[1,2],[1,3],[2,3]]
    # edges = [[1,2],[1,3]]
    graph = list_to_gnode_graph(edges)
    # print(graph)
    printGraph(graph)
    
    print(detect_undirected_cycle(graph))