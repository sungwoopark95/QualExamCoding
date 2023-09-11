# Prim's Algorithm in Python

# 무한대 값을 9999999로 설정합니다.
INF = 9999999
# 그래프의 정점 수
V = 5
# 5x5 크기의 2차원 배열을 생성하여 그래프를 나타내는 인접 행렬로 사용합니다.
G = [[0, 9, 75, 0, 0],
     [9, 0, 95, 19, 42],
     [75, 95, 0, 51, 66],
     [0, 19, 51, 0, 31],
     [0, 42, 66, 31, 0]]
# 선택된 정점을 추적하기 위한 배열을 생성합니다.
# 선택된 경우 True, 그렇지 않으면 False입니다.
selected = [0, 0, 0, 0, 0]
# 간선의 수를 0으로 설정합니다.
no_edge = 0
# 최소 신장 트리의 간선 수는 항상 (V - 1)보다 작거나 같습니다. 
# 여기서 V는 그래프의 정점 수입니다.
# 0번 정점을 선택하고 True로 설정합니다.
selected[0] = True
# 간선과 가중치를 출력합니다.
print("Edge : Weight\n")
while (no_edge < V - 1):
    # 집합 S에 있는 모든 정점에 대해 모든 인접 정점을 찾아
    # 1단계에서 선택된 정점에서의 거리를 계산합니다.
    # 정점이 이미 집합 S에 있으면 그것을 버리고, 그렇지 않으면
    # 1단계에서 선택된 정점에 가장 가까운 다른 정점을 선택합니다.
    minimum = INF
    x = 0
    y = 0
    for i in range(V):
        if selected[i]:
            for j in range(V):
                if ((not selected[j]) and G[i][j]):  
                    # 선택되지 않았고 간선이 있는 경우
                    if minimum > G[i][j]:
                        minimum = G[i][j]
                        x = i
                        y = j
    print(str(x) + "-" + str(y) + ":" + str(G[x][y]))
    selected[y] = True
    no_edge += 1
