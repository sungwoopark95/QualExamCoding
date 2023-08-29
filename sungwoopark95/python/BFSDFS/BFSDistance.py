class Graph:
    def __init__(self, filename):
        # 파일로부터 그래프를 구성합니다.
        self.adj = self.__construct_graph(filename)
    
    def __construct_graph(self, fname):
        # 파일을 열어 각 줄을 읽어와서 엣지 리스트를 생성합니다.
        with open(fname, "r") as f:
            edges = [line.strip() for line in f.readlines()]
        
        # 인접 리스트를 저장할 딕셔너리를 초기화합니다.
        adj = dict()
        
        # 각 엣지에 대해 인접 리스트를 구성합니다.
        for edge in edges:
            x, y = edge.split(',')
            x, y = int(x), int(y)
            
            # x의 인접 리스트에 y를 추가합니다.
            if x in adj:
                adj[x].append(y)
            else:
                adj[x] = [y]
            
            # y의 인접 리스트에 x를 추가합니다.
            if y in adj:
                adj[y].append(x)
            else:
                adj[y] = [x]
        
        return adj
    
    def bfs(self, start):
        # 시작 노드를 큐에 추가합니다.
        queue = [start]
        # 시작 노드를 방문한 노드 리스트에 추가합니다.
        visited = [start]
        # 시작 노드까지의 거리를 0으로 초기화합니다.
        distance = {start: 0}

        # 큐에 노드가 남아있는 동안 반복합니다.
        while queue:
            # 큐의 첫 번째 노드를 꺼냅니다.
            curr = queue.pop(0)

            # 현재 노드까지의 거리를 dist 변수에 저장합니다.
            dist = distance[curr]

            # 현재 노드와 연결된 이웃 노드들을 순회합니다.
            for neighbor in self.adj[curr]:
                # 만약 이웃 노드가 아직 방문되지 않았다면
                if neighbor not in visited:
                    # 해당 노드를 큐와 방문 리스트에 추가합니다.
                    queue.append(neighbor)
                    visited.append(neighbor)
                    # 이웃 노드까지의 거리를 (현재 노드의 거리 + 1)로 설정합니다.
                    distance[neighbor] = dist + 1        
        return distance

    
    def check_distance(self, x, y, max_distance):
        # x에서 시작하는 BFS를 통해 모든 노드까지의 거리를 계산합니다.
        distance_dict = self.bfs(x)
        
        # y가 distance_dict에 없으면 False를 반환합니다.
        if y not in distance_dict:
            return False
        
        # y까지의 거리가 max_distance 이하이면 True를 반환합니다.
        return distance_dict[y] <= max_distance
