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

from typing import List, Tuple, Dict

# Node 정의
class GNode:
    def __init__(self, id, color="W", d=0, p=None):
        self.id = id  # 노드 ID
        self.color = color  # 노드의 색상 (기본값은 흰색 'W')
        self.distance = d  # 노드까지의 거리
        self.parent = p  # 부모 노드

    def __str__(self):  # 객체를 문자열로 변환할 때 출력할 내용
        return str(self.id)


def detect_cycles(graph: Dict[int, List[Tuple[GNode, int]]]) -> List[List[GNode]]:
    """그래프에서 순환 경로들을 탐지하는 함수"""
    cycles = []
    stack = []

    def dfs(node: GNode):
        if node.color == "G":  # 현재 노드가 회색이면 순환 경로에 있다.
            idx = stack.index(node)
            cycles.append(stack[idx:])
            return
        if node.color == "B":  # 현재 노드가 검정색이면 이미 방문 및 탐색이 완료된 노드.
            return

        stack.append(node)  # 스택에 현재 노드 추가
        node.color = "G"  # 현재 노드를 회색으로 표시 (방문 중)

        for neighbor, _ in graph.get(node.id, []):
            dfs(neighbor)

        node.color = "B"  # 현재 노드 탐색 완료 (검정색으로 표시)
        stack.pop()

    for node in graph.values():
        if node[0].color == "W":
            dfs(node[0])

    return cycles


def bellman_ford(graph: Dict[int, List[Tuple[GNode, int]]], s: GNode) -> Tuple[Dict[GNode, int], Dict[GNode, GNode]]:
    distances = {}
    predecessor = {}

    # 초기 거리를 모두 무한대로 설정
    for node_list in graph.values():
        node = node_list[0]
        distances[node] = float('inf')
    distances[s] = 0  # 시작 노드의 거리는 0으로 설정

    # 모든 노드에 대한 Relaxation
    for _ in range(len(graph) - 1):
        for u, edges in graph.items():
            for v, w in edges:
                if distances[u] + w < distances[v]:
                    distances[v] = distances[u] + w
                    predecessor[v] = u

    # 음수 순환 체크
    for u, edges in graph.items():
        for v, w in edges:
            if distances[u] + w < distances[v]:
                return {}, {}  # 음수 순환이 발견되면 빈 딕셔너리 반환

    return distances, predecessor


def closestMeetingNodes(edges: List[int], node1: int, node2: int) -> int:
    G = {i: [GNode(i)] for i in range(len(edges))}

    # 그래프 구성
    for i, edge in enumerate(edges):
        if edge != -1:
            G[i].append((G[edge], 1))

    # 순환 경로 탐지
    cycles = detect_cycles(G)
    
    
    # 순환 경로에 포함된 모든 노드들을 집합에 추가
    cycle_nodes = set()
    for cycle in cycles:
        for node in cycle:
            cycle_nodes.add(node.id)

    # return list(cycle_nodes)

    # Bellman-Ford 알고리즘을 위한 초기 설정
    max_distances = {}
    for node_list in G.values():
        node = node_list[0]
        max_distances[node] = 0

    # 두 개의 노드에 대해 각각 Bellman-Ford 알고리즘 수행
    for source in [node1, node2]:
        distances, _ = bellman_ford(G, G[source][0])
        for node, distance in distances.items():
            max_distances[node] = max(max_distances[node], distance)

    # 최대 거리 중에서 가장 작은 값을 가진 노드 찾기
    distances_list = list(max_distances.values())
    min_max_distance = distances_list[0]

    for distance in distances_list:
        if distance < min_max_distance:
            min_max_distance = distance

    for node, distance in max_distances.items():
        if distance == min_max_distance:
            return node.id
