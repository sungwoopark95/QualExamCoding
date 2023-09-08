"""
어떤 소셜 미디어에는 1번부터 n번까지의 회원이 있고, 친구 관계를 `tuple`로 표현할 수 있다. 예를 들어, `(1, 2)`라는 것은 1번과 2번이 서로 친구라는 것이다(쌍방향). 즉, 친구 관계는 그래프로 나타낼 수 있다. 이때, 친구 관계로 이어진 모든 회원을 하나의 클러스터라고 하자. 1번 회원이 속한 클러스터의 회원 수를 return하는 함수 P2를 구현하라. 

* 회원 수 `n`과 친구 관계를 나타내는 `tuple`의 리스트 `edges`를 입력으로 받는다.  
* `n`은 1 이상 자연수이고, `edges`는 `tuple`로 이루어진 리스트이다.
    - 리스트 원소의 개수는 0 이상
    - 각 tuple은 서로 다른 2개의 수(1 이상 n 이하)로 이루어져 있다. 똑같은 `tuple` 은 없다.
* 회원 수에는 1번도 포함시킨다.
"""

from typing import List, Tuple

def P2(n:int, edges:List[Tuple[int]]):
    """
    이 코드는 주어진 간선들을 통해 인접 리스트를 생성하고, BFS 탐색을 통해 노드 1과 연결된 노드들의 수를 반환합니다.
    """
    
    # 인접 리스트를 위한 딕셔너리 초기화
    adj = dict()
    # 주어진 간선들을 통해 인접 리스트 생성
    for edge in edges:
        key, val = edge
        # 이미 key가 인접 리스트에 있으면, val을 해당 key의 리스트에 추가
        if key in adj:
            adj[key].append(val)
        # key가 인접 리스트에 없으면, 새로운 리스트를 생성하고 val을 추가
        else:
            adj[key] = [val]
    
    # 생성된 인접 리스트 출력
    print(adj)
    # 인접 리스트가 비어있으면 1 반환 (노드 1만 존재)
    if not adj:
        return 1
    
    # BFS 탐색을 위한 큐 초기화 (1과 연결된 노드들로 시작)
    queue = [val for val in adj[1]]
    # 방문한 노드를 저장하기 위한 리스트 초기화
    visited = [val for val in adj[1]]
    # BFS 탐색 시작
    while queue:
        # 큐에서 노드 하나를 꺼냄
        curr = queue.pop(0)
        # 현재 노드가 인접 리스트에 있으면
        if curr in adj:
            # 현재 노드와 연결된 노드들을 확인
            for val in adj[curr]:
                # 아직 방문하지 않은 노드이며, 노드 1이 아닌 경우
                if val not in visited and val != 1:
                    # 방문 리스트에 추가
                    visited.append(val)
                    # 큐에 추가
                    queue.append(val)
    
    # 방문한 노드의 수 + 1(노드 1)을 반환
    return len(visited) + 1

if __name__ == "__main__":
    print(P2(7, [(1, 2), (2,3), (1,5), (5, 2), (5, 6), (4, 7)]))
