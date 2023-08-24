/*
[dfs로 graph 구현하기 with colors]
*/

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

// 그래프 노드를 표현하는 클래스
class GNode {
public:
    string id;       // 노드의 고유 ID
    char color;      // 노드의 색상 ('W': 흰색, 'G': 회색, 'B': 검은색)
    int start, finish; // DFS 탐색에서의 시작 시간과 종료 시간
    GNode* parent;   // 부모 노드

    // 생성자
    GNode(string id, char c = 'W', int s = -1, int f = -1, GNode* p = nullptr)
        : id(id), color(c), start(s), finish(f), parent(p) {}

    // 노드 정보를 출력하는 함수
    void print() {
        cout << "(" << id << ", " << color << ", (" << start << ", " << finish << "), ";
        if(parent) cout << parent->id; // 부모 노드가 있으면 ID 출력
        else cout << "None";           // 부모 노드가 없으면 'None' 출력
        cout << ")";
    }
};

// 그래프를 표현하는 자료구조. 각 노드와 그에 연결된 노드들의 목록을 저장한다.
map<GNode*, vector<GNode*>> G;

// DFS 탐색에서의 전체 시간을 계산하는 변수
int time_count = 0;

// 그래프를 화면에 출력하는 함수
void printGraph(const map<GNode*, vector<GNode*>>& g) {
    for(auto& entry : g) {
        entry.first->print();
        cout << ": ";
        for(GNode* u : entry.second) {
            u->print();
        }
        cout << "\n";
    }
}

// 깊이 우선 탐색(DFS)를 수행하는 함수
void dfs_visit(GNode* u) {
    time_count++;
    u->start = time_count;
    u->color = 'G';

    printGraph(G);

    // 인접 노드들에 대한 탐색
    for(GNode* v : G[u]) {
        if(v->color == 'W') {
            v->parent = u;
            dfs_visit(v);
        }
    }

    u->color = 'B';
    time_count++;
    u->finish = time_count;

    printGraph(G);
}

// 모든 노드에 대해 깊이 우선 탐색을 시작하는 함수
void dfs() {
    for(auto& entry : G) {
        GNode* node = entry.first;
        node->color = 'W';
        node->start = -1;
        node->finish = -1;
        node->parent = nullptr;
    }

    printGraph(G);

    for(auto& entry : G) {
        GNode* u = entry.first;
        if(u->color == 'W') {
            dfs_visit(u);
        }
    }
}

int main() {
    GNode u("u"), v("v"), w("w"), x("x"), y("y"), z("z");

    // 그래프의 구조를 설정
    G[&u] = {&v, &x};
    G[&v] = {&y};
    G[&w] = {&y, &z};
    G[&x] = {&v};
    G[&y] = {&x};
    G[&z] = {&z};

    // 그래프 출력 후 DFS 시작
    printGraph(G);
    dfs();

    return 0;
}
