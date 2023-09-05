"""
[Acyclic Directed Graph paths 구하기]
paths(G, s, t)를 구현해라
acyclic directed graph G에서 주어진 nodes간의 가능한 paths들을 다 [] 형태로 반환하기

!! DFS 방법으로 풀기 !!!
a, b, c, d = GNode('a'), GNode('b'), GNode('c'), GNode('d')
G = dict()
G[a], G[b], G[c], G[d] = [b,c], [d], [], [c]
paths(G,a,c)
>>> [['a', 'c'], ['a', 'b', 'd', 'c']]
"""

class GNode:
    def __init__(self, id):
        self.id = id # id is a string
    def __str__(self):
        return self.id
# acyclic한 path를 찾아야 하므로 dfs로 품!

def paths(G, node1, node2):
    stack = [(node1, [node1.id])]  # 각 노드와 해당 노드까지의 경로를 함께 저장합니다.
    allpaths = []

    while stack:
        cur, path = stack.pop()  # 현재 노드와 해당 노드까지의 경로를 함께 가져옵니다.

        # 만약 현재 노드가 도착할 노드라면 해당 path를 allpaths에 추가합니다.
        if cur.id == node2.id:
            allpaths.append(path)
            continue

        # 주변 노드 돌면서 path에 없는 노드라면 stack에 넣기
        for adj in G[cur]:
            if adj.id not in path:
                stack.append((adj, path + [adj.id]))  # 새로운 경로를 만들어서 추가합니다.
                           
    return allpaths



###### 틀린 구현이지만 답은 맞게 나옴 ㅋㅋㅋ #########
# class GNode:
#     def __init__(self, id):
#         self.id = id # id is a string
#     def __str__(self):
#         return self.id
# # acyclic한 path를 찾아야 하므로 dfs로 품!

# def paths(G, node1, node2):
#     path = []
#     stack = [node1] # stack에 source 노드 넣으면서 초기화
#     # visited = [node1] # visited에 source 노드 넣으면서 초기화
#     allpaths = []
    
#     # stack에 연결 노드 있는 동안 돌기
#     while stack:
#         cur = stack.pop() # 현재 노드 꺼내기
#         path.append(cur.id) # 현재 노드를 path에 넣기
        
#         # 만약 현재 노드가 도착할 노드라면 해당 path []로 묶어 넣기
#         if cur.id == node2.id: 
#             allpaths.append(path)
#             path = [node1.id] # 다시 path를 source노드로 초기화

#         # 주변 노드 돌면서 visited 안 됐으면 stack에 넣기
#         for adj in G[cur]:
#             # if adj not in visited:
#                 # print('cur: ', cur, 'adj: ', adj)
#             stack.append(adj)
#                 # visited.append(adj)
                           
#     return(allpaths)
    