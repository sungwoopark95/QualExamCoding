from typing import List, Dict, Set

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
    return graph

def printGraph(G:dict):
    for key in G:
        print(f"{key.id} : {[node.id for node in G[key]]}")
        
def dfs_cycle(node: GNode, graph: Dict[GNode, List[GNode]], visited: Set[GNode], rec_stack: Set[GNode]) -> bool:
    visited.add(node)
    rec_stack.add(node)
    
    for neighbor in graph[node]:
        if neighbor not in visited:
            if dfs_cycle(neighbor, graph, visited, rec_stack):
                return True
        elif neighbor in rec_stack:
            return True
            
    rec_stack.remove(node)
    return False

def detect_directed_cycle(graph: Dict[GNode, List[GNode]]) -> bool:
    visited = set()
    rec_stack = set()
    
    for node in graph.keys():
        if node not in visited:
            if dfs_cycle(node, graph, visited, rec_stack):
                return True
    return False


if __name__ == "__main__":
    edges = [[1,2], [2,3], [3,4], [4,2]] # this has a cycle
    graph = list_to_gnode_graph(edges)
    printGraph(graph)
    
    print(detect_directed_cycle(graph)) # True