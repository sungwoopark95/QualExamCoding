"""
[All paths From Source to Target]
DAG사용해서 풀기 (Directed Acyclic graph)

there is a directed edge from node i to node graph[i][j]

Input: graph = [[1,2],[3],[3],[]]
Output: [[0,1,3],[0,2,3]]
Explanation: There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.

Input: graph = [[4,3,1],[3,2,4],[3],[4],[]]
Output: [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]
"""
# 0부터 모든 노드까지 가능한 Paths 반환하기
def allPathsSourceTarget(graph):
    
    # graph 정보 있는 Dictionary 만들기
    G = dict()
    for i in range(len(graph)):
            G[i] = graph[i]
    # print(G)
    
    # 각 노드와 해당 노드까지의 경로 저장
    stack = [(0, [0])]
    allpaths = []
    # Acyclic path 찾아야 하므로 DFS 이용
    while stack:
        cur, path = stack.pop()
        
        # 더이상 갈 노드가 없다면 (목적지라면)
        if len(G[cur]) == 0:
            # print('stack: ', stack)
            allpaths.append(path)
            continue
    
        for adj in G[cur]:
            if adj not in path:
                stack.append((adj, path+[adj]))
    return allpaths
