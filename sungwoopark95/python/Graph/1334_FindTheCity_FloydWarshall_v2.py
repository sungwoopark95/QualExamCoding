############### Floyd Warshall 알고리즘으로 shortest path 찾고 해당 path 출력, 도시 개수 출력 ###############
#################################### Vertex, Graph class 버전 ######################################
from collections import defaultdict

class Vertex:
    def __init__(self, id_):
        self.id_ = id_
        self.key_ = 0
        self.adjacency_list_ = {}
        self.previous_ = None

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
        self.vertices_ = []

    def add_node(self, id_):
        new_vertex = Vertex(id_)
        self.vertices_.append(new_vertex)
        return new_vertex

    def add_edge(self, start, end, weight):
        start.add_edge(end, weight)

    def get_vertices(self):
        return self.vertices_

    def get_num_vertices(self):
        return len(self.vertices_)

##################################### 인접행렬 초기화하는 함수 #####################################
def initialize_adj_matrix(G):
    N = G.get_num_vertices()
    vertices = G.get_vertices()
    W = [[float('inf')] * N for _ in range(N)]

    for i in range(N):
        for j in range(N):
            u, v = vertices[i], vertices[j]
            if u == v:
                W[i][j] = 0
            else:
                adj = u.get_adjacency_list()
                if v in adj:
                    W[i][j] = adj[v]
    return W

################################## Floyd Warshall 수행하는 함수 ##################################
################################# Distance, Parent Matrix 반환 #################################
def floyd_warshall(G):
    N = G.get_num_vertices()
    W = initialize_adj_matrix(G)
    D = [[w for w in row] for row in W]
    P = [[float('inf') if w == float('inf') else i for w in row] for i, row in enumerate(W)]

    for k in range(N):
        for i in range(N):
            for j in range(N):
                if D[i][k] + D[k][j] < D[i][j]:
                    D[i][j] = D[i][k] + D[k][j]
                    P[i][j] = P[k][j]
    return D, P

##################### Parent Matrix, start index, end index로 경로 만드는 함수 ######################
def construct_path(pred, start, end):
    path = []
    if start == end or pred[start][end] == float('inf'):
        return [start, end] if start != end else [start]
    else:
        temp = construct_path(pred, start, pred[start][end])
        path.extend(temp)
        path.append(end)
    return path

########################### start point에서 각각의 point로 가는 최단 경로 반환 ###########################
def floyd_warshall_shortest_paths(G, start):
    _, predecessors = floyd_warshall(G)
    vertices = G.get_vertices()
    start_idx = vertices.index(start)
    shortest_paths = defaultdict(list)

    for j in range(len(vertices)):
        id_paths = construct_path(predecessors, start_idx, j)
        vertex_path = [vertices[idx] for idx in id_paths]
        shortest_paths[vertices[j]] = vertex_path
    return shortest_paths

################# start point에서 threshold보다 낮은 distance로 도달할 수 있는 도시의 개수 ###################
def num_cities(G, start, threshold):
    N = G.get_num_vertices()
    distances = floyd_warshall(G)[0]
    start_idx = G.get_vertices().index(start)

    cnt = 0
    for i in range(N):
        if start_idx != i and distances[start_idx][i] <= threshold:
            cnt += 1
    return cnt

################ threshold보다 낮은 distance로 도달할 수 있는 도시의 개수가 가장 적은 도시 반환 ###################
def find_the_city(G, threshold):
    max_id = float('-inf')
    min_num = float('inf')

    for vertex in G.get_vertices():
        cities_cnt = num_cities(G, vertex, threshold)
        if cities_cnt <= min_num:
            min_num = cities_cnt
            if vertex.get_id() > max_id:
                max_id = vertex.get_id()
    return max_id

if __name__ == "__main__":
    graph = Graph()
    node0 = graph.add_node(0)
    node1 = graph.add_node(1)
    node2 = graph.add_node(2)
    node3 = graph.add_node(3)

    graph.add_edge(node0, node1, 3)
    graph.add_edge(node1, node2, 1)
    graph.add_edge(node1, node3, 4)
    graph.add_edge(node1, node0, 3)
    graph.add_edge(node2, node1, 1)
    graph.add_edge(node2, node3, 1)
    graph.add_edge(node3, node1, 4)
    graph.add_edge(node3, node2, 1)

    # 최단 경로 찾기
    distances, _ = floyd_warshall(graph)
    N = graph.get_num_vertices()
    print("Floyd Warshall Distances:")
    for i in range(N):
        print(' '.join(map(str, distances[i])))

    # 특정 노드에서 모든 노드로의 최단 경로 출력
    start_node = node0
    shortest_paths = floyd_warshall_shortest_paths(graph, start_node)
    print("\nShortest Paths from Node {}:".format(start_node.get_id()))
    for end_node, path in shortest_paths.items():
        path_str = " -> ".join(str(vertex.get_id()) for vertex in path)
        print(f"{start_node.get_id()} to {end_node.get_id()}: {path_str}")

    # threshold 값보다 짧은 거리에 있는 도시의 수 출력
    threshold = 4
    cities_count = num_cities(graph, start_node, threshold)
    print(f"\nNumber of cities reachable from Node {start_node.get_id()} with threshold {threshold}: {cities_count}")

    # 가장 적은 도시 수로 접근 가능한 노드의 ID를 찾습니다.
    min_city_id = find_the_city(graph, threshold)
    print(f"\nThe city with the fewest reachable cities within threshold {threshold} is Node {min_city_id}.")

