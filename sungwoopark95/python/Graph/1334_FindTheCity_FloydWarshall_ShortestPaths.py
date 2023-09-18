##################### Floyd Warshall 알고리즘으로 shortest path 찾고 해당 path 출력 #####################
#################################### Vertex, Graph class 버전 #####################################
from typing import Dict, List, Tuple
import math

class Vertex:
    def __init__(self, id_: int):
        self.id_ = id_  # 정점의 ID
        self.key_ = 0  # 키 (예: 프림 알고리즘에서 사용됨)
        self.adjacency_list_ = {}  # 인접한 정점과 가중치를 담는 목록
        self.previous_ = None  # 알고리즘에서 사용될 이전 정점 참조

    def add_edge(self, vertex, weight):
        self.adjacency_list_[vertex] = weight

    def get_id(self):
        return self.id_

    def set_key(self, key):
        self.key_ = key

    def get_key(self):
        return self.key_

    def get_adjacency_list(self):
        return self.adjacency_list_

    def set_previous(self, prev):
        self.previous_ = prev

    def get_previous(self):
        return self.previous_

class Graph:
    def __init__(self):
        self.vertices_ = []  # 그래프 내의 모든 정점들

    def __del__(self):
        self.vertices_.clear()

    def add_node(self, id_: int) -> Vertex:
        new_vertex = Vertex(id_)
        self.vertices_.append(new_vertex)
        return new_vertex

    def add_edge(self, start: Vertex, end: Vertex, weight: int):
        start.add_edge(end, weight)

    def get_vertices(self):
        return self.vertices_

    def get_num_vertices(self):
        return len(self.vertices_)

##################################### 인접행렬 초기화하는 함수 #####################################
def initialize_adj_matrix(G: Graph) -> List[List[float]]:
    N = G.get_num_vertices()
    vertices = G.get_vertices()
    W = [[math.inf for _ in range(N)] for _ in range(N)]

    for i in range(N):
        for j in range(N):
            u, v = vertices[i], vertices[j]
            if u == v:
                W[i][j] = 0
            elif v in u.get_adjacency_list():
                W[i][j] = u.get_adjacency_list()[v]
    return W

################################## Floyd Warshall 수행하는 함수 ##################################
################################# Distance, Parent Matrix 반환 #################################
def floyd_warshall(G: Graph) -> Tuple[List[List[float]], List[List[float]]]:
    N = G.get_num_vertices()
    W = initialize_adj_matrix(G)
    D = [[0 for _ in range(N)] for _ in range(N)]
    P = [[math.inf for _ in range(N)] for _ in range(N)]
    
    # Initialize D and P matrices
    for i in range(N):
        for j in range(N):
            D[i][j] = W[i][j]
            if i != j and W[i][j] != math.inf:
                P[i][j] = i

    # Update matrices
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
    if start == end or pred[start][end] == math.inf:
        path.extend([start, end])
    else:
        path.extend(construct_path(pred, start, pred[start][end]))
        path.append(end)
    return path

########################### start point에서 각각의 point로 가는 최단 경로 반환 ###########################
def floyd_warshall_shortest_paths(G: Graph, start: Vertex) -> Dict[Vertex, List[Vertex]]:
    _, P = floyd_warshall(G)
    vertices = G.get_vertices()
    start_idx = vertices.index(start)

    shortest_paths = {}
    for j in range(len(vertices)):
        id_path = construct_path(P, start_idx, j)
        vertex_path = [vertices[id_] for id_ in id_path]
        shortest_paths[vertices[j]] = vertex_path

    return shortest_paths

########################### start point에서 각각의 point로 가는 최단 경로 출력 ###########################
def print_shortest_path(G: Graph, start: Vertex, threshold: int):
    vertices = G.get_vertices()
    distance = floyd_warshall(G)[0]
    shortest_paths = floyd_warshall_shortest_paths(G, start)

    start_idx = vertices.index(start)
    
    for to, path in shortest_paths.items():
        if start == to:
            continue
        
        to_idx = vertices.index(to)
        
        if distance[start_idx][to_idx] > threshold:
            continue
        
        path_str = "->".join([str(v.get_id()) for v in path])
        print(f"({start.get_id()}, {to.get_id()}) : [{path_str}]")

