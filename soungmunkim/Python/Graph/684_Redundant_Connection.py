from typing import List

# `find` 함수는 노드 x의 대표 노드(루트 노드)를 찾습니다.
def find(parent: List[int], x: int) -> int:
    # x의 부모가 자기 자신이 아니라면, 대표 노드를 찾기 위한 재귀 호출을 합니다.
    if parent[x] != x:
        parent[x] = find(parent, parent[x])
    # x의 대표 노드를 반환합니다.
    return parent[x]

# `union` 함수는 두 노드 x, y를 같은 집합에 속하도록 합치는 역할을 합니다.
def union(parent: List[int], x: int, y: int) -> bool:
    # x의 대표 노드를 찾습니다.
    rootX = find(parent, x)
    # y의 대표 노드를 찾습니다.
    rootY = find(parent, y)
    # 만약 x와 y의 대표 노드가 동일하다면, 이미 같은 집합에 속해 있음을 의미합니다.
    print(f"x:{x}, y:{y}, parent x:{rootX}, parent y:{rootY}")
    if rootX == rootY:
        return False  # x와 y는 이미 연결되어 있습니다.
    # x의 대표 노드의 부모를 y의 대표 노드로 설정합니다.
    parent[rootX] = rootY
    return True

# 이 함수는 주어진 그래프에서 불필요한 간선(이미 연결된 노드들을 연결하는 간선)을 찾습니다.
def findRedundantConnection(edges: List[List[int]]) -> List[int]:
    # 노드의 개수를 저장합니다.
    nodes = set()
    for edge in edges:
        nodes.add(edge[0])
        nodes.add(edge[1])
    n = len(nodes)
    
    # 초기화: 각 노드의 부모를 자기 자신으로 설정합니다.
    parent = [i for i in range(n + 1)]
    
    # 모든 간선에 대해 순회합니다.
    for edge in edges:
        # print(f"From {edge[0]} to {edge[1]} - {union(parent, edge[0], edge[1])}")
        print(f"After union - parent : {parent}")
        # 간선의 두 노드를 연결하려고 시도합니다.
        if not union(parent, edge[0], edge[1]):
            # 만약 edge[0]과 edge[1]이 이미 연결되어 있다면, 해당 간선이 불필요한 간선임을 의미합니다.
            print(f"Cycle detected at {edge}")
            return True
    print("No cycle")
    return False
    
        
if __name__ == "__main__":
    edges1 = [[1,2],[1,3],[2,3]]
    # edges1 = [[1,2],[1,3]]
    findRedundantConnection(edges1)
    
    # edges2 = [[1,2],[2,3],[3,4],[1,4],[1,5]]
    # print(findRedundantConnection(edges2))