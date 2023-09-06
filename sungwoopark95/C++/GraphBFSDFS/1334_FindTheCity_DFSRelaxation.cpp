
/*
[DFS + Relaxation 사용해서 모든 노드 shortest path 찾기]
shortestpath 함수에서는 DFS를 사용하여 그래프를 탐색하고 relaxation를 진행하며, 
이 과정에서 현재 노드를 통해 도달할 수 있는 다른 노드까지의 거리가 더 짧은 경로가 존재할 경우 
해당 거리 정보를 업데이트하는 방식

1) threshold 이하인 shortest paths(노드들이 가장 적은 path중 source node가 가장큰 것 프린트)
2) threshold 이하인 shortest paths (from node, to node):[shortest path] 형식으로 프린트
    -> pred (previous node 정보) matrix 추가해서 프린트하기 

(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test                                                   
거리 임계값 이하의 도시 중 가장 적은 도시에 도달할 수 있는 도시는: 3
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % g++ -std=c++17 1334_FindTheCity_DFSRelaxation.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test                                                   
(0, 2) : [0, 1, 2]
(0, 1) : [0, 1]
(1, 3) : [1, 2, 3]
(1, 2) : [1, 2]
(1, 0) : [1, 0]
(2, 3) : [2, 3]
(2, 1) : [2, 1]
(2, 0) : [2, 1, 0]
(3, 2) : [3, 2]
(3, 1) : [3, 2, 1]
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <stack>

using namespace std;

// GNode 클래스 선언
class GNode {
public:
    int id; // 노드의 ID
    vector<pair<GNode*, int>> edges; // 노드의 인접 노드 및 가중치 정보

    GNode(int _id) : id(_id) {} // 생성자

    // 인접 노드 및 가중치 정보를 추가하는 함수
    void addEdge(GNode* toNode, int w) {
        edges.push_back({toNode, w});
    }
};

// 주어진 시작 노드로부터의 최단 경로를 반환하는 함수
unordered_map<GNode*, int> shortestpath(const vector<GNode*>& graph, GNode* s) {
    unordered_map<GNode*, int> distances; // 거리 정보 저장

    // 거리 정보 초기화
    for (GNode* node : graph) {
        distances[node] = numeric_limits<int>::max();
    }

    distances[s] = 0; // 시작 노드의 거리는 0
    vector<GNode*> stack = {s}; // DFS용 스택 (시작노드 포함)

    // DFS를 사용하여 최단 경로 계산
    while (!stack.empty()) {
        GNode* cur = stack.back();
        stack.pop_back();

        for (const auto& node_weight_pair : cur->edges) {
            GNode* node = node_weight_pair.first;
            int weight = node_weight_pair.second;

            // 현재 경로가 더 짧은 경우 업데이트
            if (distances[node] > distances[cur] + weight) {
                distances[node] = distances[cur] + weight;
                stack.push_back(node);
            }
        }
    }

    return distances;
}


// 지정된 거리 임계값 이하의 도시 중 가장 적은 도시에 도달할 수 있는 도시 반환
int findTheCity(int n, const vector<GNode*>& graph, int distanceThreshold) {
    int max_city = -1;
    int min_cnt = numeric_limits<int>::max();

    // 모든 노드에 대한 계산
    for (GNode* source : graph) {
        auto dist_dct = shortestpath(graph, source);

        int cnt = 0;
        // 임계값 이하의 거리에 있는 도시 계산
        for (const auto& node_distance_pair : dist_dct) {
            int distance = node_distance_pair.second;
            if (distance <= distanceThreshold && distance > 0) {
                cnt++;
            }
        }

        // 최소 도시 수 및 최대 도시 ID 업데이트
        if (cnt <= min_cnt) {
            if (cnt < min_cnt || (cnt == min_cnt && source->id > max_city)) {
                max_city = source->id;
                min_cnt = cnt;
            }
        }
    }

    return max_city;
}

int main() {
    vector<GNode*> graph; // 그래프 정보 저장

    // 노드 및 간선 생성
    GNode* node0 =  new GNode(0);
    GNode* node1 =  new GNode(1);
    GNode* node2 =  new GNode(2);
    GNode* node3 =  new GNode(3);

    node0->addEdge(node1, 3);
    node1->addEdge(node2, 1);
    node1->addEdge(node3, 4);
    node1->addEdge(node0, 3);
    node2->addEdge(node1, 1);
    node2->addEdge(node3, 1);
    node3->addEdge(node1, 4);
    node3->addEdge(node2, 1);

    // 그래프에 노드 추가
    graph.push_back(node0);
    graph.push_back(node1);
    graph.push_back(node2);
    graph.push_back(node3);

    int threshold = 4;  // 예시 거리 임계값
    int city = findTheCity(graph.size(), graph, threshold); // 계산 및 결과 출력
    cout << "거리 임계값 이하의 도시 중 가장 적은 도시에 도달할 수 있는 도시는: " << city << endl;


    // 메모리 정리
    for (GNode* node : graph) {
        delete node;
    }

    return 0;
}



// /*----------------------- distance threshold 이하인 shortest path 프린트 -------------------------*/
// #include <iostream>
// #include <vector>
// #include <unordered_map>
// #include <limits>

// using namespace std;

// // 그래프 노드를 표현하는 클래스
// class GNode {
// public:
//     int id;  // 노드의 고유 아이디
//     vector<pair<GNode*, int>> edges;  // 이 노드에서부터 연결된 다른 노드들과 그 연결의 가중치를 저장하는 벡터

//     // 생성자
//     GNode(int _id) : id(_id) {}

//     // 이 노드에서 다른 노드로 연결(간선) 추가
//     void addEdge(GNode* node, int weight) {
//         edges.push_back({node, weight});
//     }
// };

// // Bellman-Ford 알고리즘 구현 함수
// unordered_map<GNode*, int> bellmanFord(const vector<GNode*>& graph, GNode* s, unordered_map<GNode*, GNode*>& previous) {
//     unordered_map<GNode*, int> distances;  // 각 노드까지의 최단 거리를 저장하는 맵
//     for (GNode* node : graph) {
//         distances[node] = numeric_limits<int>::max();  // 초기에 모든 거리를 '무한'으로 설정
//     }
//     distances[s] = 0;  // 시작 노드의 거리는 0

//     // 모든 노드와 간선에 대해 거리를 업데이트
//     for (int i = 0; i < graph.size() - 1; ++i) {
//         for (GNode* node : graph) {
//             for (auto& edge : node->edges) {
//                 GNode* dest = edge.first;  // 목적지 노드
//                 int weight = edge.second;  // 간선의 가중치
//                 // 현재 노드까지의 거리와 현재 노드에서 목적지 노드까지의 가중치 합이 
//                 // 목적지 노드의 현재 거리보다 작다면 거리 업데이트
//                 if (distances[node] != numeric_limits<int>::max() && distances[dest] > distances[node] + weight) {
//                     distances[dest] = distances[node] + weight;
//                     previous[dest] = node;  // 경로 추적을 위한 이전 노드 업데이트
//                 }
//             }
//         }
//     }

//     // 음수 가중치의 순환 검사
//     for (GNode* node : graph) {
//         for (auto& edge : node->edges) {
//             GNode* dest = edge.first;
//             int weight = edge.second;
//             if (distances[node] != numeric_limits<int>::max() && distances[dest] > distances[node] + weight) {
//                 cerr << "그래프에 음수 가중치의 순환이 있습니다!" << endl;
//                 exit(1);
//             }
//         }
//     }

//     return distances;
// }

// // 시작 노드로부터 threshold 이하의 거리에 있는 모든 도시까지의 최단 경로를 출력하는 함수
// void printShortestPaths(const vector<GNode*>& graph, GNode* s, int threshold) {
//     unordered_map<GNode*, GNode*> previous;  // 경로 추적을 위한 맵
//     auto dist_dct = bellmanFord(graph, s, previous);  // 최단 거리 계산

//     for (const auto& node_distance_pair : dist_dct) {
//         GNode* dest = node_distance_pair.first;
//         // 시작 노드가 아니며 거리가 threshold 이하인 노드만 처리
//         if (s->id != dest->id && node_distance_pair.second <= threshold) {
//             vector<int> path;
//             GNode* current = dest;
//             // 경로 추적
//             while (current) {
//                 path.push_back(current->id);
//                 current = previous[current];
//             }
//             reverse(path.begin(), path.end());  // 경로의 순서를 뒤집음

//             cout << "(" << s->id << ", " << dest->id << ") : [";
//             for (int i = 0; i < path.size(); ++i) {
//                 cout << path[i];
//                 if (i != path.size() - 1) cout << ", ";
//             }
//             cout << "]" << endl;
//         }
//     }
// }

// int main() {
//     vector<GNode*> graph;  // 그래프 정보를 저장할 벡터

//     // 각 도시를 나타내는 노드 생성
//     GNode* node0 =  new GNode(0);
//     GNode* node1 =  new GNode(1);
//     GNode* node2 =  new GNode(2);
//     GNode* node3 =  new GNode(3);

//     // 각 도시(노드)의 인접 정보 및 간선의 가중치 설정
//     node0->addEdge(node1, 3);
//     node1->addEdge(node2, 1);
//     node1->addEdge(node3, 4);
//     node1->addEdge(node0, 3);
//     node2->addEdge(node1, 1);
//     node2->addEdge(node3, 1);
//     node3->addEdge(node1, 4);
//     node3->addEdge(node2, 1);
    
//     // 그래프에 도시(노드) 추가
//     graph.push_back(node0);
//     graph.push_back(node1);
//     graph.push_back(node2);
//     graph.push_back(node3);

//     // 최대 허용 거리 설정
//     int threshold = 4;
//     // 각 도시를 시작으로 하는 최단 경로 계산 및 출력
//     for (GNode* source : graph) {
//         printShortestPaths(graph, source, threshold);
//     }

//     // 동적 할당 받은 메모리 해제
//     for (GNode* node : graph) {
//         delete node;
//     }

//     return 0;  // 프로그램 종료
// }
