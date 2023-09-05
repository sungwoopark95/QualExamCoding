"""
connected undirected graph G
level_partition(G, s) 구현하기
    that partitions the nodes in the breadth-first tree of G rooted at s,
    list로 각 층마다 nodes들 반환하기 (층 inc order)
    
# TestCase
r, s, t, u, v = GNode('r'), GNode('s'), GNode('t'), GNode('u'), GNode('v')
w, x, y = GNode('w'), GNode('x'), GNode('y')
G = dict()
G[r], G[s], G[t], G[u], G[v] = [s, v], [w, r], [w, x, u], [t, x, y], [r]
G[w], G[x], G[y] = [s, t, x], [w, t, u, y], [x, u]
>>> [['s'], ['r', 'w'], ['t', 'v', 'x'], ['u', 'y']]

bfs(G, s) that performs a BFS algorithm (node s를 root로하여 Undirected graph G 만드는 함수)
level_partition(G, s) that uses bfs(G, s) (이전 함수 이용해서 level마다 node 담은 list 반환)
"""
import collections
# Node definition
class GNode:
    def __init__(self, id, color="W", d=0, p=None):
        self.id = id
        self.color = color
        self.distance = d
        self.parent = p
    
    def __str__(self): # object를 넣었을 때 어떤 걸 프린트할지
        return self.id

# (a) bfs(G,s) that performs a BFS algorithm on a connected undirectd graph G from the source node s
def bfs(G,s):
    # 그래프의 모든 노드 초기화
    for key in G:
        key.color = 'W'
        key.distance = -1
        key.parent = None
    
    # 시작 노드의 색상과 거리 설정
    s.color = "G"
    s.distance = 0
    Q = collections.deque() # BFS를 위한 queue 초기화
    Q.append(s) # source node를 먼저 queue에 넣고 시작
    
    while(len(Q)>0): #queue가 비어있지 않을 동안 계속
        cur = Q.popleft() # queue에서 cur node 꺼내기
        for adj in G[cur]: # 현재 노드의 인접 노드들에대해 돌기
            if adj.color == 'W': # 인접 노드가 방문 되지 않은 거라면 
                adj.color = 'G' # 방문하기 
                adj.distance = cur.distance + 1 # 거리 update
                adj.parent = cur # 인접 노드의 부모는 현재 노드 = 연결
                Q.append(adj) # 인접 노드들을 다시 queue에 넣기
                
        cur.color = 'B' #현재 노드를 검은색으로 바꾸어 완전히 탐색되었음을 표시

# # level_partition(G,s) 각 level마다 []로     
def level_partition(G,s):
    bfs(G, s) # bfs 실행
    distances = []
    for key in G: # 인접 리스트 돌면서 distance 저장하기
        if key.distance not in distances:
            distances.append(key.distance)
    distances.sort() # level order대로 

    ans = []
    while distances:
        partition = []
        cur = distances.pop(0)
        for key in G: # 해당 distance와 같은 distance 가지고 있는 노드들 []에 넣기
            if key.distance == cur:
                partition.append(key.id)
        
        ans.append(partition)
    return ans
        