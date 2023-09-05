/*
connected undirected graph G
level_partition(G, s) 구현하기
    that partitions the nodes in the breadth-first tree of G rooted at s,
    list로 각 층마다 nodes들 반환하기 (층 inc order)
    
# TestCase
r, s, t, u, v = GNode('r'), GNode('s'), GNode('t'), GNode('u'), GNode('v')
w, x, y = GNode('w'), GNode('x'), GNode('y')
G = dict()
G[r], G[s], G[t], G[u], G[v] = [s, v], [w, r], [w, x, u], [t, x, y], [r]
G[w], G[x], G[y] = [s, t, x], [w, t, u, y], [x, u]


bfs(G, s) that performs a BFS algorithm (node s를 root로하여 Undirected graph G 만드는 함수)
level_partition(G, s) that uses bfs(G, s) (이전 함수 이용해서 level마다 node 담은 list 반환)

(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % g++ -std=c++17 2022_1_2_LevelPartition_SM.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test                                               
[s], [w, r], [x, v, t], [y, u]
*/

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
using namespace std;

class GNode {
    public:
    string id;     // 노드의 고유 ID
    char color;         // 노드의 색상 ('W': 흰색, 'G': 회색, 'B': 검은색)
    int distance;       // 시작 노드로부터의 거리
    GNode* parent;      // 부모 노드

    // 생성자: 노드 초기화
    GNode(string id, char c = 'W', int d = -1, GNode* p = nullptr)
        : id(id), color(c), distance(d), parent(p) {}
};

map<GNode*, vector<GNode*>> bfs(map<GNode*, vector<GNode*>>& G, GNode* s){
    // 그래프의 모든 노드를 초기 상태로 설정
    for (auto& pair : G) {
        pair.first->color = 'W';
        pair.first->distance = -1;
        pair.first->parent = nullptr;
    }

    // source node update 후 queue에 넣기
    s->color = 'G';
    s->distance = 0;

    queue<GNode*> Q;
    Q.push(s); // 시작 노드 큐에 넣기

    while(!Q.empty()){
        GNode* cur = Q.front();
        Q.pop();
        for (GNode* adj: G[cur]){
            // 인접한 노드가 방문되지 않은 상태라면
            if (adj->color == 'W'){
                adj->color = 'G'; // 방문 상태로 변경
                adj->distance = cur->distance + 1;
                adj->parent = cur;
                Q.push(adj); // 해당 인접노드도 queue에 넣음
            }
        }
        cur->color = 'B'; // 노드 cur을 처리 완료 상태로 변경
    }
    return G;
}

void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 오름차순 정렬
void bubble_sort(vector<int>& arr, int length) {
    for (int i=0;i<length;i++) {
        for (int j=0;j<length-i-1;j++) {
            if (arr[j] > arr[j+1]) {
                Swap(&arr[j], &arr[j+1]);
            }
        }
    }
}



void levle_partition(map<GNode*, vector<GNode*>>& G, GNode* s){
    bfs(G, s);
    set<int> distances_set; // set<int>를 사용하여 중복을 제거
    vector<vector<string>> result;

    // 그래프의 모든 노드를 순회하면서 distance 값을 distances 벡터에 추가
    for (auto& pair : G){
        GNode* node = pair.first; // key인 GNode
        distances_set.insert(node->distance);
    }

    // set을 vector<int>로 다시 변환
    vector<int> distances(distances_set.begin(), distances_set.end());
    bubble_sort(distances, distances.size()); // 오름차순으로 정렬함
    
    while (!distances.empty()){
        vector<string> partition; // 노드의 ID만 저장
        int cur = distances.front(); // 맨 처음 요소 접근
        distances.erase(distances.begin()); //첫번째 요소 지우기

        for (auto& pair : G){
            GNode* key = pair.first; // GNode인 Key
            if (key->distance == cur) // 그 key의 distance가 현재 level과 같은지 체크
                partition.push_back(key->id);
        }
        result.push_back(partition);
    }

    // 결과를 출력합니다. (필요한 경우 출력 형식을 조정할 수 있습니다.)
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < result[i].size(); ++j) {
            cout << result[i][j];
            if (j != result[i].size() - 1)
                cout << ", ";
        }
        cout << "]";
        if (i != result.size() - 1)
            cout << ", ";
    }
    cout << endl;
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
    std::map<GNode*, std::vector<GNode*>> G;
    G[&r] = {&s, &v};
    G[&s] = {&w, &r};
    G[&t] = {&w, &x, &u};
    G[&u] = {&t, &x, &y};
    G[&v] = {&r};
    G[&w] = {&s, &t, &x};
    G[&x] = {&w, &t, &u, &y};
    G[&y] = {&x, &u};

    levle_partition(G, &s);     // s 노드부터 BFS 수행

    return 0;
}