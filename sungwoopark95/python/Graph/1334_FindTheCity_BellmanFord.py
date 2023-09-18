"""
[find the city]
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


# bidirectical edges를 담은 graph dictionary 만들기
def graph(edges):
    graph_dct = dict()

    for info in edges:
        from_node1 = info[0]
        if from_node1 not in graph_dct:
            graph_dct[from_node1] = [(info[1], info[2])]
        else:
            graph_dct[from_node1].append((info[1], info[2]))
                
    for info in edges:
        from_node2 = info[1]
        if from_node2 not in graph_dct:
            graph_dct[from_node2] = [(info[0], info[2])]
        else:
            graph_dct[from_node2].append((info[0], info[2]))
    return graph_dct

def bellman_ford(graph, s):
    distances = {}
    predecessor = {}
    
    # 초기 거리를 모두 무한대로 설정
    for key in graph.keys():
        distances[key] = float('inf')
    distances[s] = 0  # 시작점의 거리는 0으로 설정
    
    # Relaxation 작업 (모든 노드에 대해 (n-1)번 반복하여 거리를 업데이트)
    for _ in range(len(graph) - 1):
        for u in graph:
            for v, w in graph[u]:
                # 더 짧은 경로 발견 시 업데이트
                if distances[u] + w < distances[v]:
                    distances[v] = distances[u] + w
                    predecessor[v] = u

    # Negative cycle 확인 (더 짧은 경로가 발견되면 음수 가중치 순환 있음)
    for u in graph:
        for v, w in graph[u]:
            if distances[u] + w < distances[v]:
                raise Exception("Negative weight cycle detected")
    
    return distances, predecessor


def get_shortest_path(predecessor, start, end):
    path = []
    # 종료 노드에서 시작 노드까지 역순으로 경로 생성
    while end != start:
        path.insert(0, end)
        end = predecessor[end]
    path.insert(0, start)
    return path  # 경로 반환


def print_distances_change(distances):
    # 각 노드까지의 거리 출력
    for node, dist in distances.items():
        print(f"Distance to {node}: {dist}")


def findTheCity(n, edges, distanceThreshold):
    dct = graph(edges)
    cities = []
    
    # 각 출발점에 대해 반복
    for source in dct.keys():
        distances, predecessor = bellman_ford(dct, source)
        cnt = 0
        # 각 목적지 노드에 대해 반복
        for node in dct.keys():
            # 자기 자신 제외
            if node != source:
                # distanceThreshold 내의 노드만 카운트
                if distances[node] <= distanceThreshold:
                    cnt += 1
                    # 경로 출력
                    path = get_shortest_path(predecessor, source, node)
                    print(f"Shortest path from {source} to {node}: {path}")
        cities.insert(source, cnt)


if __name__ == '__main__':
    n = 4
    edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]]
    distanceThreshold = 4
    print(findTheCity(n, edges, distanceThreshold))