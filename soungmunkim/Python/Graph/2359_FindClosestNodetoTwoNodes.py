"""
[두 노드에서 출발해서 도달하는 smallest path 중 max dist를 뽑아
    해당 max dist중 가장 smallest한 max dist를 가지고 있는 
    노드 반환 (여러개일 경우 가장 Index가 작은)]
You are given a directed graph of n nodes numbered from 0 to n - 1, 
    where each node has at most one outgoing edge.

The graph is represented with a given 0-indexed array edges of size n, 
    indicating that there is a directed edge from node i to node edges[i]. 

If there is no outgoing edge from i, then edges[i] == -1.

You are also given two integers node1 and node2.

Return the index of the node that can be reached 
    from both node1 and node2, such that 
    the maximum between the distance from node1 to that node, 
    and from node2 to that node is minimized. 

If there are multiple answers, 
    return the node with the smallest index, 
    and if no possible answer exists, return -1.

Note that edges may contain cycles.
"""

from typing import List, Tuple, Set

###################### directed cycle 찾는 함수 #######################  
def detect_cycles(graph: dict) -> List[List[int]]:
    """Returns a list of cycles detected in the graph."""
    visited = set()
    stack = []
    cycles = []

    def dfs(node, parent):
        if node in stack:
            cycle_start_idx = stack.index(node)
            cycles.append(stack[cycle_start_idx:])
            return
        if node in visited:
            return
        visited.add(node)
        stack.append(node)
        for neighbor, _ in graph.get(node, []):
            if neighbor != parent:
                dfs(neighbor, node)
        stack.pop()

    for node in graph:
        if node not in visited:
            dfs(node, None)

    return cycles


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
                # raise Exception("Negative weight cycle detected")
                return {}, {}
    
    return distances, predecessor

##### positive cycle은 shortest path에 영향을 주지 않으므로 굳이 제외 안 해도 되지만 혹시 몰라 넣어놓음 #####
    # # Negative cycle 확인 + cycle있는 노드 제외
    # for u in graph:
    #     for v, w in graph[u]:
    #         if v in ignore_nodes:  # 순환에 포함된 노드는 무시
    #             continue
    #         if distances[u] + w < distances[v]:
    #             raise Exception("Negative weight cycle detected")

    # return distances, predecessor


def closestMeetingNodes(edges: List[int], node1: int, node2: int) -> int:
    # edge, weight 정보 담은 graph dict
    G = dict()
    # 0번 노드부터니까
    for i in range(len(edges)):
        G[i] = []
    
    # 정보 입력 
    for i in range(len(edges)):
        from_ = i
        if edges[i] != -1:
            to = edges[i]
            weight = 1
        
            G[from_].append((to, weight))
        
    print("Graph: ", G)

######## directed cycle 찾고 해당 nodes를 set에 넣어놓는 함수 ##########  
    # 순환 경로를 탐지
    cycles = detect_cycles(G)

    # 순환에 포함된 모든 노드들의 세트를 구성
    ignore_nodes = set()
    for cycle in cycles:
        for node in cycle:
            ignore_nodes.add(node)
#################################################################
    
    max_dist = dict()
    
    for source in G.keys():
        if source == node1 or source == node2:
            distances, predecoessor = bellman_ford(G, source)
            
            print("minimum distances: ", distances)
            
            for key, val in distances.items():
                if key not in max_dist:
                    max_dist[key] = [val]
                else:
                    max_dist[key].append(val)
                    
    # 두 노드에서 출발하는 것 중 max distance만 저장하기
    for s, vals in max_dist.items():
        if float('inf') in vals:
            max_dist[s] = []
        else:
            dist = max(vals)
            max_dist[s] = dist
    
    print (max_dist)
    
    # max distances 중 가장 smallest 찾기
    smallest_idxNodes = []
    smallest = 9999999
    for dist in max_dist.values():
        if dist != [] and smallest > dist:
            smallest = dist
    
    # max dist 중 smallest 값인 모든 nodes list에 다 넣고 
    # 맨 처음 node 반환하기
    for k, d in max_dist.items():
        if d == smallest:
            smallest_idxNodes.append(k)
    
    return smallest_idxNodes[0]
            