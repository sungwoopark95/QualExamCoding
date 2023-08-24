"""
[Node간 거리 확인 true or false]
class Graph(filename)
filename 파일에 적힌 edge 정보를 읽어와 undirected graph를 구성한다. 
Graph의 각 node를 표현하기 위해 0 이상의 정수가 한 개 씩 ID로 배정 되며, 
    filename 파일에는 graph의 모든 edge 정보가 적혀 있다.
    
check_distance(x, y, max_distance)
x를 ID로 가지는 node와 y를 ID로 가지는 node 사이의 거리가 max distance 보다 작거나 같은지의 여부를 확인하여 반환한다. 
x에서 y로 가는 path가 없 으면 max distance값과 상관 없이 False를 반환
"""

import collections

class Graph:
    def __init__(self, filename):
        # 그래프를 표현하기 위한 딕셔너리 초기화 (list형태로 value)
        self.graph = collections.defaultdict(list)
        
        # 파일에서 edge 정보를 읽어 그래프를 구성
        with open(filename, 'r') as file:
            for line in file:
                # 각 줄에서 두 노드를 추출
                line_elements = line.strip().split(',')
                node1 = int(line_elements[0])
                node2 = int(line_elements[1])
                
                # 양방향 그래프이므로 두 노드 모두에 edge 정보 추가
                self.graph[node1].append(node2)
                self.graph[node2].append(node1)
    
    # [(node1, node2), (node1, nod2)] 이런 리스트 형태로 edge를 input 형태 받았을때
    # def __init__(self, edges):
    #     # 그래프를 표현하기 위한 딕셔너리 초기화
    # self.graph = collections.defaultdict(list)
    
    # # 주어진 edge 정보를 바탕으로 그래프를 구성
    # for node1, node2 in edges:
    #     # 양방향 그래프이므로 두 노드 모두에 edge 정보 추가
    #     self.graph[node1].append(node2)
    #     self.graph[node2].append(node1)

    def bfs(self, start):
        # BFS 탐색을 위한 큐와 방문 정보 초기화
        queue = collections.deque([start])
        visited = set([start])
        # 초기에는 모든 노드의 거리를 무한대(float('inf'))로 설정
        distances = {node: float('inf') for node in self.graph} 
        # 시작노드 distance는 0으로 초기화
        distances[start] = 0
        
        # BFS 탐색 수행
        while queue:
            current = queue.popleft()
            for neighbor in self.graph[current]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)
                    distances[neighbor] = distances[current] + 1
        
        # 최종적으로 각 노드까지의 거리를 반환
        return distances
    
    def check_distance(self, x, y, max_distance):
        # x 노드에서 시작하는 BFS를 통해 거리 정보를 얻음
        distances = self.bfs(x)
        
        # y 노드의 거리가 max_distance 이하이면 True 반환, 그렇지 않으면 False 반환
        return distances[y] <= max_distance
