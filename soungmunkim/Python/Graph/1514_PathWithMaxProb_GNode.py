"""
[undirected graph sorce -> target 까지의 max prob을 반환하기]
DFS + Relaxation 방법으로 품

Input: n = 3, edges = [[0,1],[1,2],[0,2]], 
succProb = [0.5,0.5,0.2], start = 0, end = 2
Output: 0.25000
Explanation: There are two paths from start to end, 
one having a probability of success = 0.2 and the other has 0.5 * 0.5 = 0.25.

Input: n = 3, edges = [[0,1]], 
succProb = [0.5], start = 0, end = 2
Output: 0.00000
Explanation: There is no path between 0 and 2.
"""
from typing import List
class GNode:
    def __init__(self, id, d=1):
        self.id = id
        self.distance = d
        
    def __str__(self):
        return self.id

def shortestPath(graph, s):
    
    # 그래프의 모든 노드 초기화
    for key in graph:
        key.distance = - float('inf')
    
    # for key in graph:
    #     print((key.id, key.distance))    
        
    # 시작 노드 거리 설정 
    s.distance = 1
    stack = []
    stack.append(s)
    
    # dfs + relaxation으로 업뎃하기
    while stack:
        cur = stack.pop()
        
        # weight를 가져와서 GNode dist를 업뎃하기
        # max prob이니까 < 로
        for adj, weight in graph[cur]:
            if adj.distance < cur.distance * weight:
                adj.distance = cur.distance * weight
                stack.append(adj)

def maxProb(n:int, edges:List[List[int]], succProb: List[float], start_node: int, end_node: int) -> float:
    nodes = {}  # 노드 정보를 저장할 딕셔너리
    G = dict() # 빈 그래프 생성 (G adj list dictionary 만들기)
    
    # 그래프 초기화 및 GNode 인스턴스 생성 (숫자 노드용 GNode랑 key 만들기)
    for i in range(0, n): # 노드 0부터 시작하므로 
        nodes[i] = GNode(i)  # 각 노드를 위한 GNode 객체 생성
        G[nodes[i]] = []

    # 그래프에 간선 정보 추가 (양방향 그래프) (G dict 만들기)
    for i in range(len(edges)):
        from_ = nodes[edges[i][0]]
        to = nodes[edges[i][1]]
        
        # 해당 prob(weight) 정보와 함께 저장
        G[from_].append((to, succProb[i]))
        G[to].append((from_, succProb[i]))
        
        # if from_ not in G:
        #     G[from_] = [(to, succProb[i])]
        # else:
        #     G[from_].append((to, succProb[i]))
        # if to not in G:
        #     G[to] = [(from_, succProb[i])]
        # else:
        #     G[to].append((from_, succProb[i]))     
               
    shortestPath(G, nodes[start_node])

    if nodes[end_node].distance == -float('inf'):
        return float(0)
    else:
        return nodes[end_node].distance

if __name__ == "__main__":
    n = 3
    edges = [[0,1],[1,2],[0,2]]
    succProb = [0.5,0.5,0.2]
    start = 0
    end = 2
    print(maxProb(n, edges, succProb, start, end))
    
    n = 3
    edges = [[0,1]]
    succProb = [0.5]
    start = 0
    end = 2
    print(maxProb(n, edges, succProb, start, end))

            