"""
[Graph에서 BFS로 거리 계산 (color로 방문 표시)]
graph를 만들고 방문 전엔 white, 방문 후엔 gray로 하여 BFS을 이용해 거리를 구함


(base) soungmunkim@gimseongmun-ui-MacBookPro Graph % python -i Graph_BFS_withColors.py 
>>> r = GNode("r")
>>> s = GNode("s")
>>> t = GNode("t")
>>> u = GNode("u")
>>> v = GNode("v")
>>> w = GNode("w")
>>> x = GNode("x")
>>> y = GNode("y")
>>> 
>>> G = dict()
>>> G[r] = [s, v]
>>> G[s] = [w, r]
>>> G[t] = [w, x, u]
>>> G[u] = [t, x, y]
>>> G[v] = [r]
>>> G[w] = [s, t, x]
>>> G[x] = [w, t, u, y]
>>> G[y]= [x, u]
>>> 
>>> printGraph(G)
(r, W, -1, None): (s, W, -1, None)(v, W, -1, None)
(s, W, -1, None): (w, W, -1, None)(r, W, -1, None)
(t, W, -1, None): (w, W, -1, None)(x, W, -1, None)(u, W, -1, None)
(u, W, -1, None): (t, W, -1, None)(x, W, -1, None)(y, W, -1, None)
(v, W, -1, None): (r, W, -1, None)
(w, W, -1, None): (s, W, -1, None)(t, W, -1, None)(x, W, -1, None)
(x, W, -1, None): (w, W, -1, None)(t, W, -1, None)(u, W, -1, None)(y, W, -1, None)
(y, W, -1, None): (x, W, -1, None)(u, W, -1, None)
>>> 
>>> bfs(G,s)
=========================================
(r, W, -1, None): (s, G, 0, None)(v, W, -1, None)
(s, G, 0, None): (w, W, -1, None)(r, W, -1, None)
(t, W, -1, None): (w, W, -1, None)(x, W, -1, None)(u, W, -1, None)
(u, W, -1, None): (t, W, -1, None)(x, W, -1, None)(y, W, -1, None)
(v, W, -1, None): (r, W, -1, None)
(w, W, -1, None): (s, G, 0, None)(t, W, -1, None)(x, W, -1, None)
(x, W, -1, None): (w, W, -1, None)(t, W, -1, None)(u, W, -1, None)(y, W, -1, None)
(y, W, -1, None): (x, W, -1, None)(u, W, -1, None)
Q = (s, G, 0, None)
=========================================
(r, G, 1, s): (s, B, 0, None)(v, W, -1, None)
(s, B, 0, None): (w, G, 1, s)(r, G, 1, s)
(t, W, -1, None): (w, G, 1, s)(x, W, -1, None)(u, W, -1, None)
(u, W, -1, None): (t, W, -1, None)(x, W, -1, None)(y, W, -1, None)
(v, W, -1, None): (r, G, 1, s)
(w, G, 1, s): (s, B, 0, None)(t, W, -1, None)(x, W, -1, None)
(x, W, -1, None): (w, G, 1, s)(t, W, -1, None)(u, W, -1, None)(y, W, -1, None)
(y, W, -1, None): (x, W, -1, None)(u, W, -1, None)
Q = (w, G, 1, s)(r, G, 1, s)
=========================================
(r, G, 1, s): (s, B, 0, None)(v, W, -1, None)
(s, B, 0, None): (w, B, 1, s)(r, G, 1, s)
(t, G, 2, w): (w, B, 1, s)(x, G, 2, w)(u, W, -1, None)
(u, W, -1, None): (t, G, 2, w)(x, G, 2, w)(y, W, -1, None)
(v, W, -1, None): (r, G, 1, s)
(w, B, 1, s): (s, B, 0, None)(t, G, 2, w)(x, G, 2, w)
(x, G, 2, w): (w, B, 1, s)(t, G, 2, w)(u, W, -1, None)(y, W, -1, None)
(y, W, -1, None): (x, G, 2, w)(u, W, -1, None)
Q = (r, G, 1, s)(t, G, 2, w)(x, G, 2, w)
=========================================
(r, B, 1, s): (s, B, 0, None)(v, G, 2, r)
(s, B, 0, None): (w, B, 1, s)(r, B, 1, s)
(t, G, 2, w): (w, B, 1, s)(x, G, 2, w)(u, W, -1, None)
(u, W, -1, None): (t, G, 2, w)(x, G, 2, w)(y, W, -1, None)
(v, G, 2, r): (r, B, 1, s)
(w, B, 1, s): (s, B, 0, None)(t, G, 2, w)(x, G, 2, w)
(x, G, 2, w): (w, B, 1, s)(t, G, 2, w)(u, W, -1, None)(y, W, -1, None)
(y, W, -1, None): (x, G, 2, w)(u, W, -1, None)
Q = (t, G, 2, w)(x, G, 2, w)(v, G, 2, r)
=========================================
(r, B, 1, s): (s, B, 0, None)(v, G, 2, r)
(s, B, 0, None): (w, B, 1, s)(r, B, 1, s)
(t, B, 2, w): (w, B, 1, s)(x, G, 2, w)(u, G, 3, t)
(u, G, 3, t): (t, B, 2, w)(x, G, 2, w)(y, W, -1, None)
(v, G, 2, r): (r, B, 1, s)
(w, B, 1, s): (s, B, 0, None)(t, B, 2, w)(x, G, 2, w)
(x, G, 2, w): (w, B, 1, s)(t, B, 2, w)(u, G, 3, t)(y, W, -1, None)
(y, W, -1, None): (x, G, 2, w)(u, G, 3, t)
Q = (x, G, 2, w)(v, G, 2, r)(u, G, 3, t)
=========================================
(r, B, 1, s): (s, B, 0, None)(v, G, 2, r)
(s, B, 0, None): (w, B, 1, s)(r, B, 1, s)
(t, B, 2, w): (w, B, 1, s)(x, B, 2, w)(u, G, 3, t)
(u, G, 3, t): (t, B, 2, w)(x, B, 2, w)(y, G, 3, x)
(v, G, 2, r): (r, B, 1, s)
(w, B, 1, s): (s, B, 0, None)(t, B, 2, w)(x, B, 2, w)
(x, B, 2, w): (w, B, 1, s)(t, B, 2, w)(u, G, 3, t)(y, G, 3, x)
(y, G, 3, x): (x, B, 2, w)(u, G, 3, t)
Q = (v, G, 2, r)(u, G, 3, t)(y, G, 3, x)
=========================================
(r, B, 1, s): (s, B, 0, None)(v, B, 2, r)
(s, B, 0, None): (w, B, 1, s)(r, B, 1, s)
(t, B, 2, w): (w, B, 1, s)(x, B, 2, w)(u, G, 3, t)
(u, G, 3, t): (t, B, 2, w)(x, B, 2, w)(y, G, 3, x)
(v, B, 2, r): (r, B, 1, s)
(w, B, 1, s): (s, B, 0, None)(t, B, 2, w)(x, B, 2, w)
(x, B, 2, w): (w, B, 1, s)(t, B, 2, w)(u, G, 3, t)(y, G, 3, x)
(y, G, 3, x): (x, B, 2, w)(u, G, 3, t)
Q = (u, G, 3, t)(y, G, 3, x)
=========================================
(r, B, 1, s): (s, B, 0, None)(v, B, 2, r)
(s, B, 0, None): (w, B, 1, s)(r, B, 1, s)
(t, B, 2, w): (w, B, 1, s)(x, B, 2, w)(u, B, 3, t)
(u, B, 3, t): (t, B, 2, w)(x, B, 2, w)(y, G, 3, x)
(v, B, 2, r): (r, B, 1, s)
(w, B, 1, s): (s, B, 0, None)(t, B, 2, w)(x, B, 2, w)
(x, B, 2, w): (w, B, 1, s)(t, B, 2, w)(u, B, 3, t)(y, G, 3, x)
(y, G, 3, x): (x, B, 2, w)(u, B, 3, t)
Q = (y, G, 3, x)
=========================================
(r, B, 1, s): (s, B, 0, None)(v, B, 2, r)
(s, B, 0, None): (w, B, 1, s)(r, B, 1, s)
(t, B, 2, w): (w, B, 1, s)(x, B, 2, w)(u, B, 3, t)
(u, B, 3, t): (t, B, 2, w)(x, B, 2, w)(y, B, 3, x)
(v, B, 2, r): (r, B, 1, s)
(w, B, 1, s): (s, B, 0, None)(t, B, 2, w)(x, B, 2, w)
(x, B, 2, w): (w, B, 1, s)(t, B, 2, w)(u, B, 3, t)(y, B, 3, x)
(y, B, 3, x): (x, B, 2, w)(u, B, 3, t)
Q =
"""

import collections

class GNode:
    def __init__(self, id, c = 'W', d = -1, p = None):
        # 그래프 노드의 초기화
        self.id = id         # 노드의 고유 ID
        self.color = c       # 노드의 색상 ('W': 흰색, 'G': 회색, 'B': 검은색)
        self.distance = d    # 시작 노드로부터의 거리
        self.parent = p      # 부모 노드

    def __str__(self):
        # 노드의 문자열 표현을 반환
        if (self.parent != None):
            return "(" + self.id + ", " + self.color + ", " + str(self.distance) + ", " + self.parent.id + ")"
        else:
            return "(" + self.id + ", " + self.color + ", " + str(self.distance) + ", None)"

def printGraph(g):
    # 그래프를 화면에 출력
    for key, val in g.items():
        print(str(key) + ": ", end="")
        for u in val:
            print(str(u), end="")
        print("")

def bfs(G, s):
    def printG(d):
        # 그래프 출력용 도우미 함수
        print("=========================================")
        for key, val in d.items():
            print(str(key) + ": ", end="")
            for u in val:
                print(str(u), end="")
            print("")

    def printQ(q):
        # 큐 출력용 도우미 함수
        print("Q = ", end="")
        for u in q:
            print(u, end="")
        print("")

    # 그래프의 모든 노드를 초기화
    for key in G:
        key.color = 'W'
        key.distance = -1
        key.parent = None

    # 시작 노드의 색상과 거리를 설정
    s.color = "G"
    s.distance = 0 
    Q = collections.deque()  # BFS를 위한 큐 초기화
    Q.append(s)               # 시작 노드를 큐에 추가

    printG(G)
    printQ(Q)

    while(len(Q) > 0):       # 큐가 비어 있지 않은 동안 실행
        u = Q.popleft()      # 큐에서 노드를 하나 제거
        for v in G[u]:       # 현재 노드 u의 인접 노드들에 대해
            if v.color == 'W':   # 노드 v가 방문되지 않았다면
                v.color = 'G'       # 노드 v를 회색으로 바꾸고
                v.distance = u.distance + 1   # 거리를 갱신하고
                v.parent = u                  # 부모를 설정하고
                Q.append(v)                   # 큐에 노드 v를 추가
        u.color = 'B'   # 현재 노드 u를 검은색으로 바꾸어 완전히 탐색되었음을 표시
        printG(G)
        printQ(Q)
