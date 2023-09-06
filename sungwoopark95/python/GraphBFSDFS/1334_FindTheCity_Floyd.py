"""
[find the city]
** Floyd-Warshall 알고리즘으로 Shortest path 구해서 진행함 **
** shortest path 프린트하고 싶으면 주석 + shortest path print 함수 참고! **

최소한의 거리를 구했을 때 distance threshold를 넘지 않는 경로 중에서 (at most = 이하)
방문할 수 있는 city 개수가 가장 적은 애들 중 node id(city number)가 가장 큰 것

!! shortest path 구할 때는 visites 체크 하면 안 됨! !!
최대한 적은 weight인 path를 찾아야 하므로!


n = 4
edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]]
distanceThreshold = 4
findTheCity(n, edges, distanceThreshold)
>>> 3

The neighboring cities at a distanceThreshold = 4 for each city are:
City 0 -> [City 1, City 2]
City 1 -> [City 0, City 2, City 3] City 2 -> [City 0, City 1, City 3] City 3 -> [City 1, City 2]
Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, 
but we have to return city 3 since it has the greatest number.
"""

import sys
import numpy as np

# 연결되지 않은 path의 weight
INF = sys.maxsize

#--------------------- Floyd warhshall 알고리즘 구현 (모든 source node에 대해 shortest path -----------------------
# Floyd-Warshall Algorithm
# input - adj(인접행렬), n(vertex의 수)
# output - dist : 최소 i->j의 path를 기록한 matrix (shortest path distance 기록)
# output - pred : i->j의 path에서 j 직전에 거치는 node를 기록한 matrix. (shortest path node기록)
def Floyd_warshall(adj,n):
    # 거리 기록할 배열 초기화
    dist = adj

    # predecessor 기록할 배열 초기화
    pred = [['NIL']*n for i in range(n)]
    for i in range(n):
        for j in range(n):
            if i != j and adj[i][j] != INF:
                pred[i][j] = i

    # intermediate node 'k'를 하나씩 추가하며, 해당 경우의 최단 거리 계산
    for k in range(n):
        for i in range(n):   # i: 출발노드
            for j in range(n):   # j: 도착노드

                # k를 추가함으로써 이전보다 더 빠른 길이 생기는 경우의 처리
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
                    pred[i][j] = pred[k][j]
    return dist, pred
#---------------------------------------------------------------------------------------------------------

# shortest path list에 담아 출력하기
def print_shortest_path(pred, i, j):
    path = []
    def recursion(pred, i, j):
        if i == j:
            # print(i, end=' ')
            path.append(i)
            return
        recursion(pred, i, pred[i][j])
        # print(j, end=' ')
        path.append(j)   
    
    recursion(pred, i, j)
    return path
    

def findTheCity(n, edges, distanceThreshold):
    # Row, Col = len(edges), len(edges)
    adj = np.zeros((n, n))
    
    #--------------------- bidirectical adj.matrix 만들기-----------------------
    for i in range(n): # 한 방향
        for j in range(n):
            # 먼저 같은 노드가 아니면 INf.로 initialize 하기
            if i != j:
                adj[i][j] = float('inf')
            
            from_node = edges[i][0]
            to_node = edges[i][1]
            dist = edges[i][2]
            adj[from_node][to_node] = dist
            
    for i in range(n): # 다른 한 방향
        for j in range(n):
            if i != j:
    
                from_node = edges[i][1]
                to_node = edges[i][0]
                dist = edges[i][2]
                adj[from_node][to_node] = dist
    #----------------------------------------------------------------------------             
            
    # print("adj. matrix: \n", adj) # 완성된 bidrectical adj.matrix
    
    distance, pred = Floyd_warshall(adj, n)  # 여기서 Path는 프린트 할 필요 없음 (pred 사용 안 함)
    # print("distance matrix: \n", distance)  
    
    shortestpaths = dict()
    # allpaths = []
    for i in range(len(distance)):
        for j in range(len(distance[0])):
            # i -> j까지의 최단 거리이므로
        
            if i != j and distance[i][j] <= distanceThreshold:
                # shortest path에 각 Source마다 shortest distance가 4이하인 도착점 넣기
                print((i,j), end='\t')
                if i not in shortestpaths:
                    shortestpaths[i] = [j]
                else:
                    shortestpaths[i].append(j)
                print(print_shortest_path(pred, i, j))
                # allpaths.append(print_shortest_path(pred, i, j))
                
                    
    # print("all paths: ", allpaths)
    
    min_num = 100
    max_city = -1
    # print("shortestpath: \n", shortestpaths)
    
    # 가장 적은 number of cities중 가장 큰 Source node return 하기
    for city, adj in shortestpaths.items():
        if len(adj) <= min_num:
            min_num = len(adj)
            if city > max_city:
                max_city = city
    
    return max_city     

if __name__ == "__main__":
    n = 4
    edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]]
    distanceThreshold = 4
    findTheCity(n, edges, distanceThreshold)
