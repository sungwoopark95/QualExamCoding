/*
[BFS로 graph 구현하기 = 거리 계산 with colors]
*/

#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

// 그래프 노드를 정의하는 클래스
class GNode {
public:
    string id;     // 노드의 고유 ID
    char color;         // 노드의 색상 ('W': 흰색, 'G': 회색, 'B': 검은색)
    int distance;       // 시작 노드로부터의 거리
    GNode* parent;      // 부모 노드

    // 생성자: 노드 초기화
    GNode(string id, char c = 'W', int d = -1, GNode* p = nullptr)
        : id(id), color(c), distance(d), parent(p) {}

    // 노드의 정보를 문자열로 반환
    string to_string() const {
        if (parent) {
            return "(" + id + ", " + color + ", " + std::to_string(distance) + ", " + parent->id + ")";
        }
        return "(" + id + ", " + color + ", " + std::to_string(distance) + ", None)";
    }
};

// 그래프를 화면에 출력하는 함수
void printGraph(const map<GNode*, vector<GNode*>>& G) {
    for (const auto& pair : G) {
        cout << pair.first->to_string() << ": ";
        for (const auto& u : pair.second) {
            cout << u->to_string();
        }
        cout << endl;
    }
    cout << "=========================================" << endl;
}

// 큐의 내용을 화면에 출력하는 함수
void printQueue(const queue<GNode*>& Q) {
    queue<GNode*> tempQ = Q;
    cout << "Q = ";
    while (!tempQ.empty()) {
        cout << tempQ.front()->to_string();
        tempQ.pop();
    }
    cout << endl;
}

// BFS 알고리즘을 수행하는 함수
void bfs(map<GNode*, vector<GNode*>>& G, GNode* s) {
    // 그래프의 모든 노드를 초기 상태로 설정
    for (auto& pair : G) {
        pair.first->color = 'W';
        pair.first->distance = -1;
        pair.first->parent = nullptr;
    }
    s->color = 'G';
    s->distance = 0;

    queue<GNode*> Q;
    Q.push(s);  // 시작 노드를 큐에 넣음

    printGraph(G);
    printQueue(Q);

    // 큐가 비어 있지 않는 동안
    while (!Q.empty()) {
        GNode* u = Q.front();
        Q.pop();
        for (GNode* v : G[u]) {
            // 인접한 노드 v가 방문되지 않은 상태라면
            if (v->color == 'W') {
                v->color = 'G';  // 방문 상태로 변경
                v->distance = u->distance + 1;
                v->parent = u;
                Q.push(v);      // 노드 v를 큐에 넣음
            }
        }
        u->color = 'B';  // 노드 u를 처리 완료 상태로 변경
        printGraph(G);
        printQueue(Q);
    }
}

int main() {
    // 그래프 노드들을 생성
    GNode r("r");
    GNode s("s");
    GNode t("t");
    GNode u("u");
    GNode v("v");
    GNode w("w");
    GNode x("x");
    GNode y("y");

    // 그래프 구성 (인접 리스트로 표현)
    map<GNode*, vector<GNode*>> G;
    G[&r] = {&s, &v};
    G[&s] = {&w, &r};
    G[&t] = {&w, &x, &u};
    G[&u] = {&t, &x, &y};
    G[&v] = {&r};
    G[&w] = {&s, &t, &x};
    G[&x] = {&w, &t, &u, &y};
    G[&y] = {&x, &u};

    printGraph(G);  // 초기 그래프 상태 출력
    bfs(G, &s);     // s 노드부터 BFS 수행

    return 0;
}
