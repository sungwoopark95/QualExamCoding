"""
[Shortest Path tree edges (Bellman-Ford Algorithm)]

Suppose that the vertex 1 is root.
You will need to print out the sequence of the shortest-paths tree edges 
    selected when the Bellman-ford algorithm is run on given graph from source.


    node1.addEdge(node2, 6)
    node1.addEdge(node3, 1)
    node1.addEdge(node4, 4)
    node1.addEdge(node5, 6)
    node3.addEdge(node5, 1)
    node4.addEdge(node2, 2)
    node4.addEdge(node5, 4)
    node5.addEdge(node2, 3)
(5, 2) (1, 3) (1, 4) (3, 5) 
"""

import sys

class Edge:
    def __init__(self, toNode, w):
        self.to = toNode      # 이 간선이 연결하는 노드에 대한 참조
        self.weight = w       # 간선의 가중치

class GNode:
    def __init__(self, id_val, color_val="W", d_val=sys.maxsize, p_val=None):
        self.id = id_val                     # 노드의 고유 ID
        self.color = color_val               # 노드의 색상 (현재 사용하지 않음)
        self.distance = d_val                # 시작 노드로부터의 거리
        self.parent = p_val                  # BFS나 DFS 수행시 부모 노드
        self.edges = []                      # 노드에 연결된 간선들의 목록

    # 노드에 간선을 추가하는 메소드
    def addEdge(self, toNode, w):
        self.edges.append(Edge(toNode, w))

# Bellman-Ford 알고리즘 수행 함수
def bellmanFord(source, graph):
    source.distance = 0  # 시작 노드의 거리를 0으로 초기화

    # 모든 노드와 간선에 대해 relaxation을 수행
    for i in range(1, len(graph)):
        for node in graph:
            for edge in node.edges:
                # relaxation 실행
                if node.distance + edge.weight < edge.to.distance:
                    edge.to.distance = node.distance + edge.weight
                    edge.to.parent = node  # 부모 노드 업데이트

# 최단 경로 트리의 edges 출력하는 함수
def print_shortest_path(source, graph):
    bellmanFord(source, graph)  # 최단 경로 계산

    print("최단 경로 트리의 간선들: ", end="")
    for node in graph:
        if node.parent:  # 부모 노드가 있는 경우 출력
            print(f"({node.parent.id}, {node.id})", end=" ")
    print()

# 예제 코드
if __name__ == "__main__":
    graph = []
    
    node1 = GNode(1)
    node2 = GNode(2)
    node3 = GNode(3)
    node4 = GNode(4)
    node5 = GNode(5)
    
    node1.addEdge(node2, 6)
    node1.addEdge(node3, 1)
    node1.addEdge(node4, 4)
    node1.addEdge(node5, 6)
    node3.addEdge(node5, 1)
    node4.addEdge(node2, 2)
    node4.addEdge(node5, 4)
    node5.addEdge(node2, 3)
    
    graph.extend([node1, node2, node3, node4, node5])
    
    print_shortest_path(node1, graph)
