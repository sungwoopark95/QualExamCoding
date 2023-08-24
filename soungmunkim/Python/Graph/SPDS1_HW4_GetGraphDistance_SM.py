"""
[BFS를 이용해서 graph 노드간의 distance 얻기]
"""

import collections

class Graph:
    def __init__(self, filename):
        # 그래프를 표현하기 위한 딕셔너리 초기화
        self.graph = collections.defaultdict(list)
        
        # 파일에서 edge 정보를 읽어 그래프를 구성
        with open(filename, 'r') as file:
            for line in file:
                # 각 줄에서 두 노드를 추출
                node1, node2 = map(int, line.strip().split(','))
                
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

    def bfs(self, start, end):
        # BFS 탐색을 위한 큐와 방문 정보 초기화
        queue = collections.deque([(start, 0)])
        visited = set([start])
        
        # BFS 탐색 수행
        while queue:
            current, distance = queue.popleft()
            if current == end:
                return distance
            for neighbor in self.graph[current]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append((neighbor, distance+1))
        
        # 연결되지 않은 경우 -1 반환
        return -1
    
    def get_distance(self, x, y):
        # x 노드에서 y 노드로의 거리를 계산
        return self.bfs(x, y)
