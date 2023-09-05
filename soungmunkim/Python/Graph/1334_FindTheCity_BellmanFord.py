"""
[find the city]
** Bellman Ford's algorithm으로 각 source마다 Shortest path 구해서 진행함 **

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


# bidirectical edges를 담은 graph dictionary 만들기
def graph(edges):
    graph_dct = dict()

    for info in edges:
        from_node1 = info[0]
        if from_node1 not in graph_dct:
            graph_dct[from_node1] = [(info[1], info[2])]
        else:
            graph_dct[from_node1].append((info[1], info[2]))
                
    for info in edges:
        from_node2 = info[1]
        if from_node2 not in graph_dct:
            graph_dct[from_node2] = [(info[0], info[2])]
        else:
            graph_dct[from_node2].append((info[0], info[2]))
    return graph_dct
        

def shortestpath(graph, s):
    distances = {}
    # initialize single source (distances dict 초기화 해주기)
    for key in graph.keys():
        if key not in distances:
            distances[key] = float('inf')
    # 처음 source distance를 0으로 초기화
    distances[s] = 0
    stack = [s] # stack에 start node 넣고 시작
    
    # dfs 방식 + relaxation (shortest path)
    while stack:
        cur = stack.pop() # 현재 노드
        for node, weight in graph[cur]: #현재의 주변 노드들과 그들의 weight 돌기
            # print('cur node: ', node, 'distance: ', weight)
            
            # 이전 노드 + 현재 노드로 가는 weight이 해당 노드 weigth보다 작으면 업데이트
            if distances[node] > distances[cur] + weight: 
                distances[node] = distances[cur] + weight
                stack.append(node) # 주변노드 스택에 넣기 (업데이트 안 하면 스택에 안 넣게끔)
    
    # print('stack: ', stack)
    # print('distance: ', distances)
    
    return distances


def findTheCity(n, edges, distanceThreshold):
    dct = graph(edges)
    cities = []
    
    #source마다 shortest path찾기 (Bellman Ford는 한 source의 Shortest path만 알려주므로)
    for source in dct.keys():
        dist_dct = shortestpath(dct, source) # 각 source마다 shortest distance담은 dict 구하기
        cnt = 0
        # 거리가 기준보다 넘지 않은 도시들 개수 센 후 해당 노드source를 index로 해서 list에 넣기
        for val in dist_dct.values():
            if val <= distanceThreshold:
                cnt+=1
        cities.insert(source, cnt)
    # print(cities)
    
    # 각 도시들 개수를 담은 sources list를 돌면서 가장 적은 도시들 중 큰 도시 source 찾기
    max_city = -1
    for s, num in enumerate(cities):
        if num == min(cities):
            if max_city < s:
                max_city = s
    return max_city  