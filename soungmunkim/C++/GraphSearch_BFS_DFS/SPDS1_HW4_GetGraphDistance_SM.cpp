/*
[BFS를 이용해서 graph 노드간의 distance 얻기]
*/

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>

using namespace std;

// GNode 클래스 정의
class GNode {
public:
    string id;  // 각 노드는 문자열 ID를 가진다.
    vector<string> neighbors;  // 해당 노드에 연결된 이웃 노드들의 ID 리스트

    // GNode 클래스 생성자: 노드 ID만을 인자로 받아 초기화
    GNode(string node_id) : id(node_id) {}
};

// 그래프를 표현하기 위한 Graph 클래스 정의
class Graph {
private:
    map<string, GNode> nodes;  // 노드 ID를 key로 하고, 해당 GNode 객체를 value로 하는 맵

public:
    // Graph 내에 노드를 추가하는 함수
    void addNode(GNode node) {
        nodes[node.id] = node;
    }

    // Graph 내에 양방향 edge를 추가하는 함수
    void addEdge(string id1, string id2) {
        nodes[id1].neighbors.push_back(id2);
        nodes[id2].neighbors.push_back(id1);
    }

    // BFS (Breadth First Search)를 통해 시작 노드에서 다른 노드들까지의 거리를 계산하는 함수
    map<string, int> bfs(string start) {
        queue<string> q;  // BFS 탐색을 위한 큐
        set<string> visited;  // 방문한 노드를 저장하기 위한 집합
        map<string, int> distances;  // 시작 노드로부터의 거리 정보를 저장하기 위한 맵

        for (auto& pair : nodes) {
            distances[pair.first] = INT32_MAX;
        }

        q.push(start);
        visited.insert(start);
        distances[start] = 0;

        while (!q.empty()) {
            string current = q.front();
            q.pop();
            for (string neighbor : nodes[current].neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                    distances[neighbor] = distances[current] + 1;
                }
            }
        }

        return distances;  // 거리 정보 반환
    }

    // 두 노드 사이의 거리를 반환하는 함수
    int get_distance(string x, string y) {
        map<string, int> distances = bfs(x);
        return distances[y];
    }
};

int main() {
    Graph g;  // 그래프 객체 생성
    
    // 예제 그래프 정보를 정의
    vector<GNode> nodeList = {
        GNode("0"), 
        GNode("1"), 
        GNode("2"), 
        GNode("3"), 
        GNode("4"), 
        GNode("5"), 
        GNode("6"), 
        GNode("7")
    };
    vector<pair<string, string>> edges = {{"0", "1"}, {"1", "4"}, {"4", "5"}, {"1", "6"}, {"2", "7"}, {"3", "7"}};
    
    for (GNode node : nodeList) {
        g.addNode(node);
    }
    for (auto edge : edges) {
        g.addEdge(edge.first, edge.second);
    }

    // 테스트 실행: 두 노드 사이의 거리를 출력
    cout << "Distance between 0 and 1: " << g.get_distance("0", "1") << endl;  
    cout << "Distance between 0 and 4: " << g.get_distance("0", "4") << endl;  
    cout << "Distance between 0 and 5: " << g.get_distance("0", "5") << endl;  
    cout << "Distance between 0 and 5: " << g.get_distance("0", "5") << endl;

    return 0;
}
