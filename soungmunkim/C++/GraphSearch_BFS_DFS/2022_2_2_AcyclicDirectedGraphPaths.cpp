/*
[Acyclic Directed Graph paths 구하기]
paths(G, s, t)를 구현해라
acyclic directed graph G에서 주어진 nodes간의 가능한 paths들을 다 [] 형태로 반환하기

!! DFS 방법으로 풀기 !!!
< 그냥 vector들을 프린트할 때 이런식으로 프린트 시키는 것>
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % g++ -std=c++17 2022_2_2_AcyclicDirectedGraphPaths.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test                                                       
["a", "c"], ["a", "b", "d", "c"]
*/
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <algorithm> // find 함수를 사용하기 위해 추가
#include <stdbool.h>

using namespace std;

class GNode {
public:
    string id;  // 노드의 고유 ID

    // 생성자: 노드를 초기화하면서 ID 값을 설정
    GNode(string id): id(id) {}
};

// 주어진 경로를 출력하는 함수
void printPath(const vector<string>& path, bool lastPath = false) {
    cout << "[";
    for (size_t i = 0; i < path.size(); i++) {
        cout << "\"" << path[i] << "\"";
        if (i != path.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]";
    if (!lastPath) cout << ", ";  // 마지막 경로가 아닌 경우에만 쉼표를 추가
}

// 시작 노드에서 종료 노드까지의 모든 경로를 출력하는 함수
void paths(map<GNode*, vector<GNode*>>& G, GNode* start, GNode* end) {
    // 스택을 사용하여 현재 노드와 그 노드까지의 경로를 함께 저장
    stack<pair<GNode*, vector<string>>> S;  
    S.push({start, {start->id}});

    vector<vector<string>> allPaths;

    // 스택이 비어있지 않는 동안 탐색 계속
    while (!S.empty()) {
        GNode* cur = S.top().first;  // 현재 노드
        vector<string> currentPath = S.top().second;  // 현재 노드까지의 경로
        S.pop();

        // 현재 노드가 목표 노드와 같다면 경로 출력
        if (cur->id == end->id) {
            allPaths.push_back(currentPath);
            continue;
        }

        // 현재 노드와 인접한 노드들에 대해 탐색
        for (GNode* adj : G[cur]) {
            // currentPath 내에 adj->id 값이 존재하는지 확인하여 순환 경로 방지
            if (find(currentPath.begin(), currentPath.end(), adj->id) == currentPath.end()) {
                // 현재 경로를 새로운 벡터 newPath에 복사
                /*
                find 함수는 특정 범위 내에서 원하는 값을 찾습니다.
                currentPath 내에서 adj->id 값을 찾아보고, 그 값이 없다면 find는 currentPath.end()를 반환합니다.
                따라서, 이 조건은 "현재 경로에 인접 노드가 아직 포함되어 있지 않은 경우"를 나타냅니다.

                현재 경로를 새로운 벡터 newPath에 복사합니다.
                이렇게 복사하는 이유는 현재 경로를 변경하지 않고, 새로운 경로를 구성하기 위함입니다.
                */
                vector<string> newPath = currentPath;

                // newPath에 인접 노드의 ID 추가
                // 이로써 newPath는 현재 노드부터 인접 노드까지의 새로운 경로를 표현하게 됩니다.
                newPath.push_back(adj->id);

                // 스택에 인접 노드와 새로운 경로 함께 저장
                /*
                DFS 탐색은 스택을 사용하여 미방문 노드들과 해당 노드까지의 경로를 저장합니다.
                스택의 최상단 노드를 계속해서 탐색하는 방식으로 DFS 탐색을 수행합니다.
                */
                S.push({adj, newPath});
            }
        }
    } // 마지막 , 프린트 처리
    for (size_t i = 0; i < allPaths.size(); i++) {
    bool isLast = (i == allPaths.size() - 1);
    printPath(allPaths[i], isLast);
    }

    cout << endl;  // 최종 출력 후 줄바꿈
}

int main() {
    // 그래프의 노드들 생성
    GNode a("a");
    GNode b("b");
    GNode c("c");
    GNode d("d");

    // 그래프 구성 (인접 리스트로 표현)
    map<GNode*, vector<GNode*>> G;
    G[&a] = {&b, &c};
    G[&b] = {&d};
    G[&c] = {};
    G[&d] = {&c};

    // 시작 노드 a에서 종료 노드 c까지의 모든 경로 출력
    paths(G, &a, &c);

    return 0;
}
