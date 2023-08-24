"""
어떤 소셜 미디어에는 1번부터 n번까지의 회원이 있고, 친구 관계를 tuple로 표현할 수 있다. 
예를 들어, (1, 2)라는 것은 1번과 2번이 서로 친구라는 것이다(쌍방향). 
즉, 친구 관계는 그래프로 나타낼 수 있다. 
이 때, 친구 관계로 이어진 모든 회원을 하나의 클러스터라고 하자. 
1번 회원이 속한 클러스터의 회원 수를 return하는 함수 P2를 구현하라.

● 회원 수 n과 친구관계를 나타내는 tuple의 리스트 edges를 입력으로 받는다.
● n은 1 이상 자연수이고, edges는 tuple로 이루어진 리스트이다.
■ 리스트 원소의 개수는 0이상
■ 각 tuple은 서로 다른 2개의 수(1이상n이하)로 이루어져있다. (똑같은tuple은 없다.)
● 회원 수에는 1번도 포함시킨다.

TestCase1)
>>>P2(7, [(1, 2), (2,3), (1,5), (5, 2), (5, 6), (4, 7)])
5
"""

from collections import deque
import numpy as np

def P2(n: int, graph: list):
    max_cnt = 0
    
    def bfs(row: int):
        # 현재 회원
        cur_row = row
        # max_cnt는 global 함수로
        nonlocal max_cnt
        # queue에 현재 회원(row)에서 모든 edge(col) 다 보면서 연결된 다른 회원 queue에 넣기
        q = deque([(cur_row, col) for col in range(n) if adj_matrx[cur_row][col] == 1])
        # print(f" queue is {q}")
        nodes = set() # 회원 수를 알아야 하므로 unique 회원
        
        while q:
            val, edge = q.popleft()

            if (0 <= val < n) and (0 <= edge < n) and adj_matrx[val][edge] == 1:
                # print(f"(val, edge) is {(val, edge)}")
                adj_matrx[val][edge] = 0 # visit한 것 체크
                nodes.add(val) # 회원 unique 한지
                nodes.add(edge) # 회원 unique 한지
                # 현재 노드와 연결되면 val, edge -> edge, val로 바뀌므로 순서 바꾸고 모든 회원 봐야하니 for loop돌기
                for i in range(1,n):
                    q.append((edge, val+i))
                    q.append((edge, val-i))
        # 가장 큰 cluster 회원 수 return
        max_cnt = max(max_cnt, len(nodes))
    
    
    # Adj matrix row, col만들기 위해 가장 큰 node val 찾기 (회원 수가 있어서 필요 없음)
    # vals = []
    # edges = []  
    # node_idx = [] 
    # for node in graph:
    #     val, edge = node
    #     vals.append(val)
    #     edges.append(edge)
    #     # node 연결되 index 찾기
    #     node_idx.append([val, edge])
    
    # adj matrix 0으로 구성하기 (회원수가 있어서 max로 볼 필요 없음)
    # Row = max(vals)
    # Col = max(edges) 
    # adj_len = max(Row, Col)
    
    # base case (node 1개만 있을 떄)
    if n == 1:
        return 1
    
    """
    adj matrix를 [회원 수 x 회원 수] 만큼 만들어서 서로 연결 되었으면 1 표시
    """
    
    adj_matrx = np.zeros([n, n])
    
    # node 연결된 위치에 1로 바꾸기 = adj matrix 완성
    # node가 1부터 시작되는데 index는 0부터 시작이니까 -1하기
    for idx in graph:
        i, j = idx
        adj_matrx[i-1][j-1] = 1
    
    # bfs 실행
    # 한 회원이 연결된 회원들 동시에 queue에 넣어야 하므로 row만 돌기
    for row in range(n):
        bfs(row)
    
    return max_cnt