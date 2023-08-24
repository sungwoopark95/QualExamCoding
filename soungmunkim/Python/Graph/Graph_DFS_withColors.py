"""
[dfs로 graph 구현하기]

(base) soungmunkim@gimseongmun-ui-MacBookPro Graph % python -i Graph_DFS_withColors.py
>>> u, v, w = GNode("u"), GNode("v"), GNode("w")
>>> x, y, z = GNode("x"), GNode("y"), GNode("z")
>>> G = dict()
>>> G[u], G[v], G[w], G[x], G[y], G[z] = [v,x], [y], [y,z], [v], [x], [z]
>>> printGraph(G)
(u, W, (-1, -1), None): (v, W, (-1, -1), None)(x, W, (-1, -1), None)
(v, W, (-1, -1), None): (y, W, (-1, -1), None)
(w, W, (-1, -1), None): (y, W, (-1, -1), None)(z, W, (-1, -1), None)
(x, W, (-1, -1), None): (v, W, (-1, -1), None)
(y, W, (-1, -1), None): (x, W, (-1, -1), None)
(z, W, (-1, -1), None): (z, W, (-1, -1), None)
>>> 
>>> dfs(G)
=========================================
(u, W, (-1, -1), None): (v, W, (-1, -1), None)(x, W, (-1, -1), None)
(v, W, (-1, -1), None): (y, W, (-1, -1), None)
(w, W, (-1, -1), None): (y, W, (-1, -1), None)(z, W, (-1, -1), None)
(x, W, (-1, -1), None): (v, W, (-1, -1), None)
(y, W, (-1, -1), None): (x, W, (-1, -1), None)
(z, W, (-1, -1), None): (z, W, (-1, -1), None)
=========================================
(u, G, (1, -1), None): (v, W, (-1, -1), None)(x, W, (-1, -1), None)
(v, W, (-1, -1), None): (y, W, (-1, -1), None)
(w, W, (-1, -1), None): (y, W, (-1, -1), None)(z, W, (-1, -1), None)
(x, W, (-1, -1), None): (v, W, (-1, -1), None)
(y, W, (-1, -1), None): (x, W, (-1, -1), None)
(z, W, (-1, -1), None): (z, W, (-1, -1), None)
=========================================
(u, G, (1, -1), None): (v, G, (2, -1), u)(x, W, (-1, -1), None)
(v, G, (2, -1), u): (y, W, (-1, -1), None)
(w, W, (-1, -1), None): (y, W, (-1, -1), None)(z, W, (-1, -1), None)
(x, W, (-1, -1), None): (v, G, (2, -1), u)
(y, W, (-1, -1), None): (x, W, (-1, -1), None)
(z, W, (-1, -1), None): (z, W, (-1, -1), None)
=========================================
(u, G, (1, -1), None): (v, G, (2, -1), u)(x, W, (-1, -1), None)
(v, G, (2, -1), u): (y, G, (3, -1), v)
(w, W, (-1, -1), None): (y, G, (3, -1), v)(z, W, (-1, -1), None)
(x, W, (-1, -1), None): (v, G, (2, -1), u)
(y, G, (3, -1), v): (x, W, (-1, -1), None)
(z, W, (-1, -1), None): (z, W, (-1, -1), None)
=========================================
(u, G, (1, -1), None): (v, G, (2, -1), u)(x, G, (4, -1), y)
(v, G, (2, -1), u): (y, G, (3, -1), v)
(w, W, (-1, -1), None): (y, G, (3, -1), v)(z, W, (-1, -1), None)
(x, G, (4, -1), y): (v, G, (2, -1), u)
(y, G, (3, -1), v): (x, G, (4, -1), y)
(z, W, (-1, -1), None): (z, W, (-1, -1), None)
=========================================
(u, G, (1, -1), None): (v, G, (2, -1), u)(x, B, (4, 5), y)
(v, G, (2, -1), u): (y, G, (3, -1), v)
(w, W, (-1, -1), None): (y, G, (3, -1), v)(z, W, (-1, -1), None)
(x, B, (4, 5), y): (v, G, (2, -1), u)
(y, G, (3, -1), v): (x, B, (4, 5), y)
(z, W, (-1, -1), None): (z, W, (-1, -1), None)
=========================================
(u, G, (1, -1), None): (v, G, (2, -1), u)(x, B, (4, 5), y)
(v, G, (2, -1), u): (y, B, (3, 6), v)
(w, W, (-1, -1), None): (y, B, (3, 6), v)(z, W, (-1, -1), None)
(x, B, (4, 5), y): (v, G, (2, -1), u)
(y, B, (3, 6), v): (x, B, (4, 5), y)
(z, W, (-1, -1), None): (z, W, (-1, -1), None)
=========================================
(u, G, (1, -1), None): (v, B, (2, 7), u)(x, B, (4, 5), y)
(v, B, (2, 7), u): (y, B, (3, 6), v)
(w, W, (-1, -1), None): (y, B, (3, 6), v)(z, W, (-1, -1), None)
(x, B, (4, 5), y): (v, B, (2, 7), u)
(y, B, (3, 6), v): (x, B, (4, 5), y)
(z, W, (-1, -1), None): (z, W, (-1, -1), None)
=========================================
(u, B, (1, 8), None): (v, B, (2, 7), u)(x, B, (4, 5), y)
(v, B, (2, 7), u): (y, B, (3, 6), v)
(w, W, (-1, -1), None): (y, B, (3, 6), v)(z, W, (-1, -1), None)
(x, B, (4, 5), y): (v, B, (2, 7), u)
(y, B, (3, 6), v): (x, B, (4, 5), y)
(z, W, (-1, -1), None): (z, W, (-1, -1), None)
=========================================
(u, B, (1, 8), None): (v, B, (2, 7), u)(x, B, (4, 5), y)
(v, B, (2, 7), u): (y, B, (3, 6), v)
(w, G, (9, -1), None): (y, B, (3, 6), v)(z, W, (-1, -1), None)
(x, B, (4, 5), y): (v, B, (2, 7), u)
(y, B, (3, 6), v): (x, B, (4, 5), y)
(z, W, (-1, -1), None): (z, W, (-1, -1), None)
=========================================
(u, B, (1, 8), None): (v, B, (2, 7), u)(x, B, (4, 5), y)
(v, B, (2, 7), u): (y, B, (3, 6), v)
(w, G, (9, -1), None): (y, B, (3, 6), v)(z, G, (10, -1), w)
(x, B, (4, 5), y): (v, B, (2, 7), u)
(y, B, (3, 6), v): (x, B, (4, 5), y)
(z, G, (10, -1), w): (z, G, (10, -1), w)
=========================================
(u, B, (1, 8), None): (v, B, (2, 7), u)(x, B, (4, 5), y)
(v, B, (2, 7), u): (y, B, (3, 6), v)
(w, G, (9, -1), None): (y, B, (3, 6), v)(z, B, (10, 11), w)
(x, B, (4, 5), y): (v, B, (2, 7), u)
(y, B, (3, 6), v): (x, B, (4, 5), y)
(z, B, (10, 11), w): (z, B, (10, 11), w)
=========================================
(u, B, (1, 8), None): (v, B, (2, 7), u)(x, B, (4, 5), y)
(v, B, (2, 7), u): (y, B, (3, 6), v)
(w, B, (9, 12), None): (y, B, (3, 6), v)(z, B, (10, 11), w)
(x, B, (4, 5), y): (v, B, (2, 7), u)
(y, B, (3, 6), v): (x, B, (4, 5), y)
(z, B, (10, 11), w): (z, B, (10, 11), w)
"""

import collections

class GNode:
    def __init__(self, id, c = 'W', start = -1, finish = -1, p = None):
        # 그래프 노드의 초기화
        self.id = id         # 노드의 고유 ID
        self.color = c       # 노드의 색상 ('W': 흰색, 'G': 회색, 'B': 검은색)
        self.start = start    # 시작 노드로부터의 시작 시간
        self.finish = finish           # 노드의 종료 시간
        self.parent = p      # 부모 노드

    def __str__(self):
        # 노드의 문자열 표현을 반환
        if (self.parent != None):
            return "(" + self.id + ", " + self.color + ", (" \
                + str(self.start) + ", " + str(self.finish) + "), " + self.parent.id + ")"
        else:
            return "(" + self.id + ", " + self.color + ", (" \
                + str(self.start) + ", " + str(self.finish) + "), None)"

def printGraph(g):
    # 그래프를 화면에 출력
    for key, val in g.items():
        print(str(key) + ": ", end="")
        for u in val:
            print(str(u), end="")
        print("")

def dfs(G):
    time = 0  # 탐색 시간을 나타내는 변수

    def printG(d):
        # 그래프 출력용 도우미 함수
        print("=========================================")
        for key, val in d.items():
            print(str(key) + ": ", end="")
            for u in val:
                print(str(u), end="")
            print("")

    def dfs_visit(G, u):
        nonlocal time   # 외부 함수의 변수를 참조
        time = time + 1
        u.start = time  # 시작 시간 설정
        u.color = "G"      # 노드의 색상을 회색으로 변경
        printG(G)
        
        for v in G[u]:  # u의 인접 노드들에 대해
            if (v.color == "W"):  # 만약 노드 v가 방문되지 않았다면
                v.parent = u     # 부모 설정
                dfs_visit(G, v)  # 재귀적으로 탐색
        u.color = "B"  # 모든 인접 노드를 방문한 후, 노드의 색상을 검은색으로 변경
        time = time + 1
        u.finish = time  # 종료 시간 설정
        printG(G)
        
    for key in G:
        key.color = "W"  # 모든 노드를 흰색으로 초기화
        key.start = -1
        key.finish = -1
        key.parent = None
    printG(G)
    
    for u in G:  # 모든 노드에 대해
        if (u.color == "W"):  # 방문되지 않은 노드라면
            dfs_visit(G, u)  # 깊이 우선 탐색 시작

            