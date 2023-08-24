/*
[Node간 거리 확인 true or false]
class Graph(filename)
filename 파일에 적힌 edge 정보를 읽어와 undirected graph를 구성한다. 
Graph의 각 node를 표현하기 위해 0 이상의 정수가 한 개 씩 ID로 배정 되며, 
    filename 파일에는 graph의 모든 edge 정보가 적혀 있다.
    
check_distance(x, y, max_distance)
x를 ID로 가지는 node와 y를 ID로 가지는 node 사이의 거리가 max distance 보다 작거나 같은지의 여부를 확인하여 반환한다. 
x에서 y로 가는 path가 없 으면 max distance값과 상관 없이 False를 반환
*/

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <queue>
#include <set>
#include <string>
#include <sstream>

using namespace std;

class Graph {
private:
    // 그래프는 map 자료구조를 사용하여 표현. 각 노드의 인접 노드들은 vector에 저장됨.
    map<int, vector<int>> graph;

public:
    // 생성자: 파일에서 그래프 정보를 읽어와서 초기화
    Graph(string filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);  // 문자열 스트림을 이용해 문자열 파싱
            int node1, node2;
            char comma;  // 콤마(,)를 저장할 변수
            ss >> node1 >> comma >> node2;  // 두 정수와 콤마를 읽어옴

            // 양방향 그래프이므로 두 노드 모두에 인접 노드 정보 추가
            graph[node1].push_back(node2);
            graph[node2].push_back(node1);
        }
    }

    // BFS 알고리즘을 통해 시작 노드로부터 각 노드까지의 거리를 계산
    map<int, int> bfs(int start) {
        queue<int> q;  // BFS에 사용할 큐
        set<int> visited;  // 방문한 노드를 저장할 집합
        map<int, int> distances;  // 각 노드까지의 거리를 저장할 map

        // 모든 노드의 거리를 무한대로 초기화
        for (auto& pair : graph) {
            distances[pair.first] = INT32_MAX;
        }

        q.push(start);
        visited.insert(start);
        distances[start] = 0;  // 시작 노드의 거리는 0

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            // 현재 노드의 모든 이웃 노드를 순회
            for (int neighbor : graph[current]) {
                if (visited.find(neighbor) == visited.end()) {  // 이웃 노드가 방문되지 않았다면
                    visited.insert(neighbor);
                    q.push(neighbor);
                    distances[neighbor] = distances[current] + 1;  // 거리 정보 업데이트
                }
            }
        }

        return distances;  // 계산된 거리 정보 반환
    }

    // 두 노드 사이의 거리가 주어진 max_distance 이하인지 체크
    bool check_distance(int x, int y, int max_distance) {
        map<int, int> distances = bfs(x);  // x에서 시작하는 BFS를 통해 거리 정보를 얻음
        return distances[y] <= max_distance;  // y까지의 거리가 max_distance 이하인지 확인
    }
};

int main() {
    Graph g("small.txt");  // 파일에서 그래프 정보를 읽어와 객체 생성

    // 테스트: 두 노드 사이의 거리가 주어진 거리 이하인지 체크
    cout << g.check_distance(0, 1, 1) << endl;  // True(1)을 출력해야 함
    cout << g.check_distance(0, 4, 2) << endl;  // True(1)을 출력해야 함
    cout << g.check_distance(0, 5, 3) << endl;  // True(1)을 출력해야 함
    cout << g.check_distance(0, 5, 2) << endl;  // False(0)을 출력해야 함

    return 0;
}

/*-------------------- GNode() 이런식으로 객체로 노드를 받고 그래프 그릴 때 코드 -----------------*/

// #include <iostream>
// #include <vector>
// #include <map>
// #include <queue>
// #include <set>

// using namespace std;

// // GNode 클래스 정의
// class GNode {
// public:
//     string id;  // 각 노드는 문자열 ID를 가진다.
//     vector<string> neighbors;  // 해당 노드에 연결된 이웃 노드들의 ID 리스트

//     // GNode 클래스 생성자: 노드 ID만을 인자로 받아 초기화
//     GNode(string node_id) : id(node_id) {}
// };

// // 그래프를 표현하기 위한 Graph 클래스 정의
// class Graph {
// private:
//     map<string, GNode> nodes;  // 노드 ID를 key로 하고, 해당 GNode 객체를 value로 하는 맵

// public:
//     // Graph 내에 노드를 추가하는 함수
//     void addNode(GNode node) {
//         nodes[node.id] = node;
//     }

//     // Graph 내에 양방향 edge를 추가하는 함수
//     // id1과 id2는 연결되어야 하는 두 노드의 ID
//     void addEdge(string id1, string id2) {
//         nodes[id1].neighbors.push_back(id2);
//         nodes[id2].neighbors.push_back(id1);
//     }

//     // BFS (Breadth First Search)를 통해 시작 노드에서 다른 노드들까지의 거리를 계산하는 함수
//     map<string, int> bfs(string start) {
//         queue<string> q;  // BFS 탐색을 위한 큐
//         set<string> visited;  // 방문한 노드를 저장하기 위한 집합
//         map<string, int> distances;  // 시작 노드로부터의 거리 정보를 저장하기 위한 맵

//         // 초기에는 모든 노드의 거리를 무한대로 설정
//         for (auto& pair : nodes) {
//             distances[pair.first] = INT32_MAX;
//         }

//         q.push(start);
//         visited.insert(start);
//         distances[start] = 0;

//         // BFS 탐색 시작
//         while (!q.empty()) {
//             string current = q.front();
//             q.pop();
//             // 현재 노드에 연결된 이웃 노드들을 방문
//             for (string neighbor : nodes[current].neighbors) {
//                 if (visited.find(neighbor) == visited.end()) {
//                     visited.insert(neighbor);
//                     q.push(neighbor);
//                     distances[neighbor] = distances[current] + 1;
//                 }
//             }
//         }

//         return distances;  // 거리 정보 반환
//     }

//     // 두 노드 사이의 거리가 주어진 최대 거리 이하인지 판별하는 함수
//     bool check_distance(string x, string y, int max_distance) {
//         map<string, int> distances = bfs(x);
//         return distances[y] <= max_distance;
//     }
// };

// int main() {
//     Graph g;  // 그래프 객체 생성
    
//     // 예제 그래프 정보를 정의
//     vector<GNode> nodeList = {
//         GNode("0"), 
//         GNode("1"), 
//         GNode("2"), 
//         GNode("3"), 
//         GNode("4"), 
//         GNode("5"), 
//         GNode("6"), 
//         GNode("7")
//     };
//     vector<pair<string, string>> edges = {{"0", "1"}, {"1", "4"}, {"4", "5"}, {"1", "6"}, {"2", "7"}, {"3", "7"}};
    
//     // 그래프 객체에 노드와 에지 정보 추가
//     for (GNode node : nodeList) {
//         g.addNode(node);
//     }
//     for (auto edge : edges) {
//         g.addEdge(edge.first, edge.second);
//     }

//     // 테스트 실행: 두 노드 사이의 거리가 주어진 거리 이하인지 출력
//     cout << g.check_distance("0", "1", 1) << endl;  // True(1) 출력
//     cout << g.check_distance("0", "4", 2) << endl;  // True(1) 출력
//     cout << g.check_distance("0", "5", 3) << endl;  // True(1) 출력
//     cout << g.check_distance("0", "5", 2) << endl;  // False(0) 출력

//     return 0;
// }
