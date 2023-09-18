"""
[find the city] GNode class 사용
** Bellman Ford's algorithm으로 각 source마다 Shortest path 구해서 진행함 **

최소한의 거리를 구했을 때 distance threshold를 넘지 않는 경로 중에서 (at most = 이하)
방문할 수 있는 city 개수가 가장 적은 애들 중 node id(city number)가 가장 큰 것

!! shortest path 구할 때는 visites 체크 하면 안 됨! !!
최대한 적은 weight인 path를 찾아야 하므로!


n = 4
edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]]
distanceThreshold = 4
findTheCity(n, edges, distanceThreshold)
>>> 3

The neighboring cities at a distanceThreshold = 4 for each city are:
City 0 -> [City 1, City 2]
City 1 -> [City 0, City 2, City 3] City 2 -> [City 0, City 1, City 3] City 3 -> [City 1, City 2]
Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, 
but we have to return city 3 since it has the greatest number.


(base) soungmunkim@gimseongmun-ui-MacBookPro String % python /Users/soungmunkim/Desktop/Coding/QualExamCoding/soungmunkim/Python/Graph/1334_FindTheCity_BellmanFord.py
Shortest path from 0 to 1: [0, 1]
Shortest path from 0 to 2: [0, 1, 2]
Shortest path from 1 to 0: [1, 0]
Shortest path from 1 to 2: [1, 2]
Shortest path from 1 to 3: [1, 2, 3]
Shortest path from 2 to 0: [2, 1, 0]
Shortest path from 2 to 1: [2, 1]
Shortest path from 2 to 3: [2, 3]
Shortest path from 3 to 1: [3, 2, 1]
Shortest path from 3 to 2: [3, 2]
3
"""

import collections

# Node 정의
class GNode:
    def __init__(self, id, color="W", d=0, p=None):
        self.id = id  # 노드 ID
        self.color = color  # 노드의 색상 (기본값은 흰색 'W')
        self.distance = d  # 노드까지의 거리
        self.parent = p  # 부모 노드
    
    def __str__(self):  # 객체를 문자열로 변환할 때 출력할 내용
        return str(self.id)

# 양방향 edge를 포함한 그래프 사전 만들기
def graph(edges):
    graph_dct = collections.defaultdict(list)  # 노드 별로 인접 리스트 저장

    for u, v, w in edges:
        if u not in graph_dct:
            graph_dct[u] = GNode(u)
        if v not in graph_dct:
            graph_dct[v] = GNode(v)
        
        # u에서 v로, v에서 u로 가는 edge를 각각 추가
        graph_dct[u].append((graph_dct[v], w))
        graph_dct[v].append((graph_dct[u], w))

    return graph_dct

def bellman_ford(graph, s):
    distances = {node: float('inf') for node in graph}  # 거리를 무한대로 초기화
    distances[s] = 0  # 시작 노드의 거리는 0
    
    # Relaxation 작업
    for _ in range(len(graph) - 1):
        for u in graph:
            for v, w in graph[u]:
                # 더 짧은 경로 발견 시 업데이트
                if distances[u] + w < distances[v.id]:
                    distances[v.id] = distances[u] + w
                    v.parent = graph[u]

    # Negative cycle 확인
    for u in graph:
        for v, w in graph[u]:
            if distances[u] + w < distances[v.id]:
                raise Exception("Negative weight cycle detected")
    
    return distances, {v.id: v.parent.id for v in graph if v.parent}

def get_shortest_path(predecessor, start, end):
    path = [end]  # 경로의 시작을 end로 설정
    # 종료 노드에서 시작 노드까지 역순으로 경로 생성
    while path[-1] != start:
        path.append(predecessor[path[-1]])
    return path[::-1]  # 경로를 올바른 순서로 반환

def print_distances_change(distances):
    # 각 노드까지의 거리 출력
    for node, dist in distances.items():
        print(f"Distance to {node}: {dist}")

def findTheCity(n, edges, distanceThreshold):
    dct = graph(edges)  # 그래프 생성
    cities = []
    
    for source in dct.keys():
        distances, predecessor = bellman_ford(dct, source)  # 각 출발점에 대해 최단 거리 및 경로 계산
        cnt = 0
        for node in dct.keys():
            if node != source:
                # distanceThreshold 내의 노드만 카운트
                if distances[node] <= distanceThreshold:
                    cnt += 1
                    # 경로 출력
                    path = get_shortest_path(predecessor, source, node)
                    print(f"Shortest path from {source} to {node}: {path}")
        cities.append(cnt)  # 각 도시별로 해당 거리 내의 도시 수를 리스트에 추가

    min_count = min(cities)  # 가장 적은 도시 수 찾기
    candidates = [i for i, cnt in enumerate(cities) if cnt == min_count]  # 해당 도시 수를 갖는 모든 도시 찾기
    return max(candidates)  # 그 중 가장 큰 ID 값을 반환

if __name__ == '__main__':
    n = 4
    edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]]
    distanceThreshold = 4
    print(findTheCity(n, edges, distanceThreshold))

