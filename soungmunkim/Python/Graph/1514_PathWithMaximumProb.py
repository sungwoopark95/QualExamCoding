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

def maxProbability(n: int, edges: List[List[int]], succProb: List[float], start_node: int, end_node: int) -> float:

    # n = len(edges) # 노드 개수 (연결 안 된 node도 있어서 주어진 node 수 사용해야함)

    # 빈 그래프 생성 (G adj list dictionary 만들기)
    G = dict()
    # 노드 0부터 시작하므로 
    for i in range(0, n):
        G[i] = []
    
    
    # 주어진 간선 정보를 바탕으로 양방향 그래프 구성 (Undirected graph 정보 담기)   
    for i in range(len(edges)):
        from_ = edges[i][0] 
        to = edges[i][1] 
        # 해당 prob(weight) 정보와 함께 저장
        G[from_].append((to, succProb[i]))
        G[to].append((from_, succProb[i]))
    
    # shorteset path 찾는 함수 
    def shortestpath(G, s):
        # shortest distance 업뎃 정보 저장할 곳
        distances = dict()

        # distances 초기화 (max 곱하기 찾아야해서 -inf로)
        for key in G.keys():
            if key not in distances:
                distances[key] = -float('inf')
                
        # 곱하기여서 1로 초기화
        distances[s] = 1
        stack = [s]
        
        while stack:
            cur = stack.pop()
            # 주변 노드돌면서 해당 weight곱했을 때 더 크면 update하기 (relaxation)
            for node, weight in G[cur]:
                if distances[node] < distances[cur] * weight:
                    distances[node] = distances[cur] * weight
                    stack.append(node)
        
        return distances
    
    dist = shortestpath(G, start_node)
    # end node가 업뎃 안 된거라면 연결 안 된 노드이므로 0 return
    if dist[end_node] == - float('inf'):
        return 0
    else:
        # 업뎃 된 최종적으로 큰 확률을 내보내기
        return dist[end_node]   