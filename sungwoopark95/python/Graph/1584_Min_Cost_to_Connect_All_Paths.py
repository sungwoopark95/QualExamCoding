from typing import List, Dict, Tuple

########### 두 개의 정수 리스트를 입력받아 둘 사이의 Manhattan 거리를 계산하는 함수 ###########
def get_weight(p1:List[int], p2:List[int]) -> int:
    p1_x, p1_y = p1
    p2_x, p2_y = p2
    return abs(p1_x - p2_x) + abs(p1_y - p2_y)
#################################################################################

################ List of int list를 받아 adjacency list를 만드는 함수 ################
def build_graph(points:List[List[int]]) -> Dict[int, Tuple[int]]:
    points = [tuple(point) for point in points]
    graph = dict()
    for from_ in points:
        for to in points:
            if from_ == to: continue
            weight = get_weight(from_, to)
            if from_ in graph:
                graph[from_].append((to, weight))
            else:
                graph[from_] = [(to, weight)]
            
            if to in graph:
                graph[to].append((from_, weight))
            else:
                graph[to] = [(from_, weight)]
    return graph
#################################################################################

###################### kruskal을 수행하기 위해 필요한 helper 함수 ######################
#################### 각 node의 parent와 distance를 초기화하는 함수 ####################
def make_set(v:int, parents:Dict[int, int], distance:Dict[int, int]) -> None:
    parents[v] = v
    distance[v] = 0
#################################################################################

######################### 각 node가 시작된 origin을 찾는 함수 #########################
def find_set(v:int, parents:Dict[int, int]) -> int:
    # 만약 v의 부모가 자기 자신이 아니라면, v는 대표 원소 (루트)가 아닙니다.
    if v != parents[v]:
        # v의 부모를 찾기 위해 재귀적으로 find_set 함수를 호출합니다.
        # 이 과정을 통해 v의 부모를 찾을 수 있습니다.
        # 경로 압축 기법을 사용하여 v의 부모를 그 대표 원소 (루트)로 직접 연결합니다.
        # 이렇게 하면 다음 번 find_set 호출 시 더 빠르게 루트를 찾을 수 있습니다.
        parents[v] = find_set(parents[v], parents)
    # v의 대표 원소 (루트)를 반환합니다.
    return parents[v]
#################################################################################

############################ 두 node를 서로 연결하는 함수 #############################
def union(v1:int, v2:int, parents:Dict[int, int], distance:Dict[int, int]) -> None:
    # v1과 v2의 대표 원소 (루트)를 찾습니다.
    root1, root2 = find_set(v1, parents), find_set(v2, parents)
    
    # 만약 v1과 v2가 동일한 집합에 속해 있다면 (즉, 루트가 동일하다면) 아무런 작업을 수행하지 않습니다.
    if root1 == root2:
        return

    # root1의 트리 높이 (혹은 거리)가 root2의 트리 높이보다 작은 경우
    if distance[root1] < distance[root2]:
        # root1의 부모를 root2로 설정하여, root1의 트리를 root2의 트리 아래에 연결합니다.
        parents[root1] = root2
    
    # root1의 트리 높이가 root2의 트리 높이보다 큰 경우
    elif distance[root1] > distance[root2]:
        # root2의 부모를 root1로 설정하여, root2의 트리를 root1의 트리 아래에 연결합니다.
        parents[root2] = root1
    
    # 두 트리의 높이가 동일한 경우
    else:
        # root2의 부모를 root1로 설정하여, root2의 트리를 root1의 트리 아래에 연결합니다.
        parents[root2] = root1
        # root1의 트리 높이를 1 증가시킵니다. 
        # (두 트리의 높이가 동일했기 때문에 병합 후 root1의 트리 높이가 1 증가하게 됩니다.)
        distance[root1] += 1
#################################################################################

############### kruskal을 수행하고 minimum spanning tree를 반환하는 함수 ##############
def kruskalMST(graph:Dict[int, Tuple[int]]) -> List[List[int]]:
    # 결과로 반환될 MST의 간선들을 저장하는 리스트 초기화
    ans = []
    
    # 각 노드의 부모와 트리의 깊이를 저장할 딕셔너리 초기화
    parents, distance = dict(), dict()

    # graph 내의 모든 포인트에 대해, 각 포인트를 독립된 집합으로 만듭니다.
    for point in graph:
        make_set(point, parents, distance)

    # 그래프 내의 모든 간선들을 저장할 리스트 초기화
    edges = []
    for point in graph:
        for adj in graph[point]:
            to, weight = adj  # 인접 노드와 가중치 분리
            edges.append((point, to, weight))  # 간선 정보 저장
    
    # 간선들을 가중치를 기준으로 정렬
    sorted_edges = sorted(edges, key=lambda x:x[2])

    # 정렬된 간선들을 순회하며 MST를 구성
    for edge in sorted_edges:
        u, v, weight = edge  # 간선의 두 노드와 가중치 분리
        # 만약 u와 v가 서로 다른 집합에 속해 있다면, (즉, 연결되어 있지 않다면)
        if find_set(u, parents) != find_set(v, parents):
            ans.append(edge)  # 해당 간선을 결과 리스트에 추가
            union(u, v, parents, distance)  # u와 v를 동일한 집합으로 합칩니다.
    
    # 최종적으로 구성된 MST의 간선들을 반환
    return ans
#################################################################################

############ kruskal을 수행하고 minimum spanning tree의 cost를 반환하는 함수 ###########
def kruskalCost(graph:Dict[int, Tuple[int]]) -> int:
    # 결과로 반환될 MST의 간선들을 저장하는 리스트 초기화
    ans = []

    # 각 노드의 부모와 트리의 깊이를 저장할 딕셔너리 초기화
    parents, distance = dict(), dict()

    # graph 내의 모든 포인트에 대해, 각 포인트를 독립된 집합으로 만듭니다.
    for point in graph:
        make_set(point, parents, distance)

    # 그래프 내의 모든 간선들을 저장할 리스트 초기화
    edges = []
    for point in graph:
        for adj in graph[point]:
            to, weight = adj  # 인접 노드와 가중치 분리
            edges.append((point, to, weight))  # 간선 정보 저장
    
    # 간선들을 가중치를 기준으로 정렬
    sorted_edges = sorted(edges, key=lambda x:x[2])

    # 정렬된 간선들을 순회하며 MST를 구성
    for edge in sorted_edges:
        u, v, weight = edge  # 간선의 두 노드와 가중치 분리
        # 만약 u와 v가 서로 다른 집합에 속해 있다면, (즉, 연결되어 있지 않다면)
        if find_set(u, parents) != find_set(v, parents):
            ans.append(edge)  # 해당 간선을 결과 리스트에 추가
            union(u, v, parents, distance)  # u와 v를 동일한 집합으로 합칩니다.
    
    # MST의 총 가중치를 저장할 변수 초기화
    cost = 0
    # ans에 저장된 간선들의 가중치를 모두 더함
    for edge in ans:
        cost += edge[-1]

    # 최종적으로 구한 MST의 총 가중치 반환
    return cost
#################################################################################

def minCostConnectPoints(Points:List[List[int]]) -> int:
    graph = build_graph(Points)
    return kruskalCost(graph)

if __name__ == "__main__":
    points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
    print(minCostConnectPoints(points))
    
    points2 = [[3,12],[-2,5],[-4,1]]
    print(minCostConnectPoints(points2))