"""
graph 자체를 복사하는 방식 (노드들을 복사해서 adj list 내보내기)
"""

from collections import deque

class Node:
    def __init__(self, val=0, neighbors=None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []
        
# list를 graph 형식으로 (Node object) 만드는 함수 
def list_to_graph(adj_list):
    if not adj_list:
        return None

    # 값으로 Node 객체를 저장하는 사전을 만듭니다.
    node_dict = {}
    for val in range(1, len(adj_list) + 1):
        node_dict[val] = Node(val)

    for idx, neighbors in enumerate(adj_list, start=1):
        for neighbor_val in neighbors:
            node_dict[idx].neighbors.append(node_dict[neighbor_val])

    # 첫 번째 노드를 반환합니다.
    return node_dict[1]

# Node object를 담은 adj list를 print 하는 함수
def printGraph(node: 'Node'):
    # 방문한 노드를 기록하기 위한 집합 초기화
    visited = set()
    
    # 시작 노드를 큐에 넣기
    queue = deque([node])
    
    output = []
    # 큐에 노드가 있을 동안 반복
    while queue:
        # 큐의 가장 앞쪽에 있는 노드를 가져옴
        current = queue.popleft()
        
        # 현재 노드가 아직 방문되지 않았다면
        if current not in visited:
            # 현재 노드를 방문한 것으로 표시
            visited.add(current)
            
            # 현재 노드의 이웃들의 값을 저장할 리스트 초기화
            neighbors_vals = []

            # 현재 노드의 모든 이웃에 대하여
            for neighbor in current.neighbors:
                # 이웃의 값을 neighbors_vals 리스트에 추가
                neighbors_vals.append(neighbor.val)

            # 결과 리스트에 현재 노드의 이웃들의 값을 추가
            output.append(neighbors_vals)
            
            # # 현재 노드의 값과 이웃들의 값을 인접 리스트 형태로 출력 (1: 2, 4와 같은 형식)
            # print(f"{current.val}: {', '.join(map(str, neighbors_vals))}")

            # 현재 노드의 모든 이웃 노드에 대해서
            for neighbor in current.neighbors:
                # 만약 해당 이웃 노드가 아직 방문되지 않았다면
                if neighbor not in visited:
                    # 큐에 추가
                    queue.append(neighbor)
                    
    # 전체 결과를 인접 리스트 형태로 출력
    print(output)

"""
BFS 탐색을 할 때, 현재 노드의 모든 이웃 노드들을 살펴보고, 
    그 이웃 노드들이 이미 복제되었는지 mapping 사전을 통해 확인합니다. 
    
만약 복제되지 않았다면 새롭게 복제하고 큐에 추가합니다. 
    그러나 해당 이웃 노드가 이미 복제된 경우에는 큐에 다시 추가하지 않습니다.

이 방식 덕분에 순환 구조에서도 각 노드를 단 한 번만 방문하게 됩니다. 
    그래서 큐는 결국 비게 되고, BFS 탐색이 종료됩니다.
"""

def cloneGraph(node: 'Node') -> 'Node':
    if not node:
        return node

    # 원래 노드와 복제된 노드를 매핑할 사전을 만듭니다.
    mapping = {}

    # 시작 노드의 복제본을 만듭니다.
    mapping[node] = Node(node.val)

    # BFS 탐색을 위한 큐를 만듭니다.
    queue = deque([node])

    while queue:
        current = queue.popleft()
        
        for neighbor in current.neighbors:
            # 이웃 노드가 아직 복제되지 않았다면 복제하고 큐에 추가합니다.
            # 이를통해 cycle이어도 노드 한번만 체크하게 되는 것
            if neighbor not in mapping:
                mapping[neighbor] = Node(neighbor.val)
                queue.append(neighbor)

            # 현재 노드의 복제본의 이웃 리스트에 이웃 노드의 복제본을 추가합니다.
            mapping[current].neighbors.append(mapping[neighbor])

    # 복제된 그래프의 시작 노드로 그래프를 출력합니다.
    printGraph(mapping[node])

    # 시작 노드의 복제본을 반환합니다.
    return mapping[node]


if __name__ == "__main__":
    adjList = [[2,4],[1,3],[2,4],[1,3]]
    graph = list_to_graph(adjList)
    cloned_graph = cloneGraph(graph)    