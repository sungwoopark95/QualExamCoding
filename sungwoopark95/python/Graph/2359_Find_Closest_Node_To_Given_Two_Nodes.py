"""
주어진 두 개의 노드로부터 도달할 수 있는 노드를 찾는다.
다만, 이때 도달할 수 있는 노드의 대푯값은 해당 노드까지 도달하는 거리 중 더 큰 값으로 정한다.
이때 최소의 대푯값을 갖는 노드를 찾아라.
만일 최소의 대푯값을 갖는 노드가 두 개 이상인 경우, 그 중 가장 인덱스 값이 작은 노드를 반환한다.

Input: edges = [2,2,3,-1], node1 = 0, node2 = 1
Output: 2
Explanation: The distance from node 0 to node 2 is 1, and the distance from node 1 to node 2 is 1.
The maximum of those two distances is 1. It can be proven that we cannot get a node with a smaller maximum distance than 1, so we return node 2.

Input: edges = [1,2,-1], node1 = 0, node2 = 2
Output: 2
Explanation: The distance from node 0 to node 2 is 2, and the distance from node 2 to itself is 0.
The maximum of those two distances is 2. It can be proven that we cannot get a node with a smaller maximum distance than 2, so we return node 2.
"""

from typing import List

def bellmanFord(G:dict, source:int):
    distance, parents = dict(), dict()
    # initialize
    for node in G.keys():  
        distance[node] = float('inf')
    distance[source] = 0

    # start
    for _ in range(len(G.keys())):
        for u in G.keys():
            for adj in G[u]:
                v, weight = adj
                if distance[u] + weight < distance[v]:
                    distance[v] = distance[u] + weight
                    parents[v] = u

    # check negative cycle
    for u in G.keys():
        for adj in G[u]:
            v, weight = adj
            if distance[u] + weight < distance[v]:
                return {}, {}
    
    return distance, parents

def closestMeetingNode(edges: List[int], node1: int, node2: int) -> int:
    ## construct graph
    graph = {i: [] for i in range(len(edges))}
    for i, to in enumerate(edges):
        if to == -1:
            continue
        graph[i].append((to, 1))

    ## bellman ford
    distances = []
    for source in graph.keys():
        if source in [node1, node2]:
            distance_dict, parents_dict = bellmanFord(graph, source)
            print(f"node : {source}, distance : {distance_dict}")
            if not distance_dict: # cycle이 한 번이라도 발생한다면
                return -1
            distances.append(distance_dict)
    
    if len(distances) == 2:
        distance1, distance2 = distances
        both_destinations = []
        for key in graph.keys():
            if distance1[key] < float('inf') and distance2[key] < float('inf'):
                maxweight = max(distance1[key], distance2[key])
                both_destinations.append((key, maxweight))
        if not both_destinations:
            return -1
        both_destinations = sorted(both_destinations, key=lambda x:(x[1], x[0]))
        return both_destinations[0][0]
    else:
        # when node1 == node2
        dist_dict = distances[0]
        min_dist, min_key = float('inf'), float('inf')
        for key, dist in dist_dict.items():
            if min_dist > dist:
                min_dist = dist
        for key in dist_dict:
            if dist_dict[key] == min_dist:
                if min_key > key:
                    min_key = key
        return min_key
    
if __name__ == "__main__":
    edges = [2,2,3,-1]
    node1 = 0
    node2 = 1
    
    print(closestMeetingNode(edges, node1, node2))
    
    edges = [1,2,-1]
    node1 = 0
    node2 = 2
    
    print(closestMeetingNode(edges, node1, node2))
