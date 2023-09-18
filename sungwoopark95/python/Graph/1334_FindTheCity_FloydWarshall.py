############### Floyd Warshall 알고리즘으로 shortest path 찾고 해당 path 출력, 도시 개수 반환 ##############
########################################### GNode 버전 ############################################
from typing import List, Tuple, Dict, Union
import math

class GNode:
    def __init__(self, _id: int):
        self.id = _id
        self.edges = []

    def add_edge(self, to_node, w: int):
        self.edges.append((to_node, w))

##################################### 인접행렬 초기화하는 함수 #####################################
def initialize_adj_matrix(G: List[GNode]) -> List[List[float]]:
    N = len(G)
    W = [[math.inf] * N for _ in range(N)]
    for i in range(N):
        for j in range(N):
            u = G[i]
            v = G[j]
            if i == j:
                W[i][j] = 0
            else:
                for adj, weight in u.edges:
                    if adj == v:
                        W[i][j] = weight
                        break
    return W

################################## Floyd Warshall 수행하는 함수 ##################################
################################# Distance, Parent Matrix 반환 #################################
def floyd_warshall(G: List[GNode]) -> Tuple[List[List[float]], List[List[float]]]:
    N = len(G)
    W = initialize_adj_matrix(G)
    D = [[0] * N for _ in range(N)]
    P = [[math.inf] * N for _ in range(N)]
    
    for i in range(N):
        for j in range(N):
            D[i][j] = W[i][j]
            if i != j and W[i][j] != math.inf:
                P[i][j] = i

    for k in range(N):
        for i in range(N):
            for j in range(N):
                if D[i][k] + D[k][j] < D[i][j]:
                    D[i][j] = D[i][k] + D[k][j]
                    P[i][j] = P[k][j]

    return D, P

##################### Parent Matrix, start index, end index로 경로 만드는 함수 ######################
def construct_path(pred: List[List[float]], start: int, end: int) -> List[int]:
    path = []
    if start == end or pred[start][end] == -1:
        path.append(start)
        if start != end:
            path.append(end)
    else:
        temp = construct_path(pred, start, int(pred[start][end]))
        path.extend(temp)
        path.append(end)
    return path

########################### start point에서 각각의 point로 가는 최단 경로 반환 ###########################
def floyd_warshall_shortest_paths(G: List[GNode], start: GNode) -> Dict[GNode, List[GNode]]:
    _, predecessors = floyd_warshall(G)
    start_idx = G.index(start)
    shortest_paths = {}
    for j in range(len(G)):
        id_paths = construct_path(predecessors, start_idx, j)
        vertex_path = [G[id] for id in id_paths]
        shortest_paths[G[j]] = vertex_path
    return shortest_paths

################# start point에서 threshold보다 낮은 distance로 도달할 수 있는 도시의 개수 ###################
def num_cities(G: List[GNode], start: GNode, threshold: int) -> int:
    N = len(G)
    distances = floyd_warshall(G)[0]
    cnt = 0
    start_idx = G.index(start)
    for i in range(N):
        if start_idx == i or distances[start_idx][i] > threshold:
            continue
        cnt += 1
    return cnt

################ threshold보다 낮은 distance로 도달할 수 있는 도시의 개수가 가장 적은 도시 반환 ###################
def find_the_city(G: List[GNode], threshold: int) -> int:
    max_val = -math.inf
    min_val = math.inf
    for v in G:
        num = num_cities(G, v, threshold)
        if num <= min_val:
            min_val = num
            if v.id > max_val:
                max_val = v.id
    return max_val

########################### start point에서 각각의 point로 가는 최단 경로 출력 ###########################
def print_shortest_path(G: List[GNode], start: GNode, threshold: int):
    distance = floyd_warshall(G)[0]
    shortest_paths = floyd_warshall_shortest_paths(G, start)

    start_idx = G.index(start)
    
    for to, path in shortest_paths.items():
        if start == to:
            continue
        
        to_idx = G.index(to)
        
        if distance[start_idx][to_idx] > threshold:
            continue
        
        path_str = " -> ".join([str(v.id) for v in path])
        print(f"({start.id}, {to.id}) : [{path_str}]")


if __name__ == "__main__":
    graph = []

    node0 = GNode(0)
    node1 = GNode(1)
    node2 = GNode(2)
    node3 = GNode(3)

    node0.add_edge(node1, 3)
    node1.add_edge(node2, 1)
    node1.add_edge(node3, 4)
    node1.add_edge(node0, 3)
    node2.add_edge(node1, 1)
    node2.add_edge(node3, 1)
    node3.add_edge(node1, 4)
    node3.add_edge(node2, 1)

    graph.extend([node0, node1, node2, node3])

    N = len(graph)
    distance, _ = floyd_warshall(graph)
    for i in range(N):
        print(' '.join(map(str, distance[i])))

    start = node0
    shortest_paths = floyd_warshall_shortest_paths(graph, start)
    for adj, path in shortest_paths.items():
        print(f"Shortest path from {start.id} to {adj.id}: {' -> '.join(str(node.id) for node in path)}")

    threshold = 4
    print(find_the_city(graph, threshold))
    
    print_shortest_path(graph, node0, 4)
