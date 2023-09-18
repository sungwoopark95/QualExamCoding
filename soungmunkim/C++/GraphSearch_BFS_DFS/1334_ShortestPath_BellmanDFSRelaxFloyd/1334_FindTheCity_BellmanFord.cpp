
/*
[Bellman ford's algorithm 사용해서 모든 노드 shortest path 찾기]
1) threshold 이하인 shortest paths(노드들이 가장 적은 path중 source node가 가장큰 것 프린트)
2) threshold 이하인 shortest paths (from node, to node):[shortest path] 형식으로 프린트
    -> previous member variable 추가해서 프린트하기
    -> pred (previous node 정보) matrix 추가해서 프린트하기 

Bellman-Ford 알고리즘은 그래프 내의 모든 간선에 대해 여러 번의 반복을 필요로하므로, 
DFS보다 훨씬 느릴 수 있습니다. 

그러나 음의 가중치를 가진 간선이 있는 경우에도 사용할 수 있습니다. 
이 문제의 문맥에서는 음의 가중치를 갖는 간선이 없기 때문에 DFS가 더 효율적일 수 있음

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

/*--------------- previous member variable 추가해서 shortest path 프린트 하는 형식 ----------------*/
// #include <iostream>
// #include <vector>
// #include <unordered_map>
// #include <limits>
// #include <stack>

// using namespace std;

// // GNode 클래스 선언
// class GNode {
// public:
//     int id;  // 노드의 ID
//     vector<pair<GNode*, int>> edges;  // 인접 노드와 간선의 가중치를 저장하는 벡터

//     /*shortest path 프린트 하기 위해 필요함*/
//     // GNode* previous = nullptr;  // 최단 경로에서 이전 노드를 추적하기 위한 포인터 

//     GNode(int _id) : id(_id) {}  // 생성자

//     // 인접 노드와 그 간선의 가중치를 추가하는 함수
//     void addEdge(GNode* node, int weight) {
//         edges.push_back({node, weight});
//     }
// };

// // 주어진 시작 노드로부터의 최단 거리를 계산하는 함수 (Bellman-Ford 알고리즘 사용)
// unordered_map<GNode*, int> shortestpath(const vector<GNode*>& graph, GNode* s) {
//     unordered_map<GNode*, int> distances;  // 각 노드까지의 거리를 저장하는 맵

//     // 모든 노드의 거리를 무한대로 초기화 (Initialize adj(distance) matrix)
//     for (GNode* node : graph) {
//         distances[node] = numeric_limits<int>::max();

//         /*shortest path 프린트 하기 위해 필요함*/
//         // node->previous = nullptr;  // 이전 노드를 null로 초기화
//     }
//     distances[s] = 0;  // 시작 노드의 거리는 0으로 설정

//     // Bellman-Ford 알고리즘 구현 부분
//     for (int i = 0; i < graph.size() - 1; ++i) {  // 각 노드를 대상으로 (n-1)번 반복
//         for (GNode* node : graph) {  // 모든 노드에 대해서
//             for (auto& edge : node->edges) {  // 해당 노드의 모든 인접 노드에 대해서
//                 GNode* dest = edge.first;  // 인접 노드
//                 int weight = edge.second;  // 간선의 가중치

//                 // 시작 노드로부터 현재 노드를 거쳐 인접 노드까지의 거리가 더 짧은 경우 업데이트
//                 if (distances[node] != numeric_limits<int>::max() && distances[dest] > distances[node] + weight) {
//                     distances[dest] = distances[node] + weight;

//                     /*shortest path 프린트 위해 필요함*/
//                     // dest->previous = node;  // 이전 노드를 업데이트
//                 }
//             }
//         }
//     }

//     return distances;  // 계산된 최단 거리 정보 반환
// }

// // 지정된 거리 임계값 이하의 도시 중 가장 적은 도시에 도달할 수 있는 도시 반환
// int findTheCity(int n, const vector<GNode*>& graph, int distanceThreshold) {
//     int max_city = -1;
//     int min_cnt = numeric_limits<int>::max();

//     // 모든 노드에 대해서 최단 거리 계산
//     for (GNode* source : graph) {
//         auto dist_dct = shortestpath(graph, source);

//         int cnt = 0;
//         // 거리 임계값 이하의 도시의 수 계산
//         for (const auto& node_distance_pair : dist_dct) {
//             int distance = node_distance_pair.second;
//             if (distance <= distanceThreshold && distance > 0) {
//                 cnt++;
//             }
//         }

//         // 가장 적은 도시에 도달할 수 있는 도시를 찾기 위한 로직
//         if (cnt <= min_cnt) {
//             if (cnt < min_cnt || (cnt == min_cnt && source->id > max_city)) {
//                 max_city = source->id;
//                 min_cnt = cnt;
//             }
//         }
//     }

//     return max_city;  // 결과 반환
// }

// /*----------------- shortest path 프린트 함수 ----------------------------*/
// // // 주어진 시작 노드로부터의 최단 경로를 출력하는 함수
// // void printShortestPaths(const vector<GNode*>& graph, GNode* s, int threshold) {
// //     auto dist_dct = shortestpath(graph, s);  // 시작 노드에서의 최단 거리를 계산

// //     // 모든 노드에 대해
// //     for (const auto& node_distance_pair : dist_dct) {
// //         // 시작 노드와 목적지 노드가 같지 않고, 거리가 threshold 이하인 경우
// //         if (s->id != node_distance_pair.first->id && node_distance_pair.second <= threshold) {
// //             cout << "(" << s->id << ", " << node_distance_pair.first->id << ")\t[";

// //             // 최단 경로를 출력하기 위한 스택 사용
// //             stack<int> path;
// //             for (GNode* current = node_distance_pair.first; current; current = current->previous) {
// //                 path.push(current->id);
// //             }
// //             while (!path.empty()) {
// //                 cout << path.top();
// //                 path.pop();
// //                 if (!path.empty()) cout << ", ";
// //             }

// //             cout << "]" << endl;
// //         }
// //     }
// // }

// int main() {
//     vector<GNode*> graph;  // 그래프 정보를 저장할 벡터

//     // 노드 생성
//     GNode* node0 =  new GNode(0);
//     GNode* node1 =  new GNode(1);
//     GNode* node2 =  new GNode(2);
//     GNode* node3 =  new GNode(3);

//     // 각 노드의 인접 정보 및 간선의 가중치 설정
//     node0->addEdge(node1, 3);
//     node1->addEdge(node2, 1);
//     node1->addEdge(node3, 4);
//     node1->addEdge(node0, 3);
//     node2->addEdge(node1, 1);
//     node2->addEdge(node3, 1);
//     node3->addEdge(node1, 4);
//     node3->addEdge(node2, 1);
    
//     // 그래프에 노드 추가
//     graph.push_back(node0);
//     graph.push_back(node1);
//     graph.push_back(node2);
//     graph.push_back(node3);

//     int threshold = 4;  // 예시 거리 임계값 설정
//     int city = findTheCity(graph.size(), graph, threshold);  // 결과 계산
//     // // 결과 출력
//     cout << "거리 임계값 이하의 도시 중 가장 적은 도시에 도달할 수 있는 도시는: " << city << endl;


//     // // 각 노드에 대해서 거리 임계값 이하인 도시들의 최단 경로를 출력
//     // /* shortest path 출력하기 위해 사용*/
//     // for (GNode* source : graph) {
//     //     printShortestPaths(graph, source, threshold);
//     // }

//     // 메모리 해제
//     for (GNode* node : graph) {
//         delete node;
//     }


//     return 0;
// }



/*--------------- pred(이전노드 정보) matrix 추가해서 shortest path 프린트 하는 형식 ----------------*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>

using namespace std;

class GNode {
public:
    int id;
    vector<pair<GNode*, int>> edges;

    GNode(int _id) : id(_id) {}

    void addEdge(GNode* node, int weight) {
        edges.push_back({node, weight});
    }
};

unordered_map<GNode*, int> shortestpath(const vector<GNode*>& graph, GNode* s, unordered_map<GNode*, GNode*>& previous) {
    unordered_map<GNode*, int> distances;
    for (GNode* node : graph) {
        distances[node] = numeric_limits<int>::max();
    }
    distances[s] = 0;

    for (int i = 0; i < graph.size() - 1; ++i) {
        for (GNode* node : graph) {
            for (auto& edge : node->edges) {
                GNode* dest = edge.first;
                int weight = edge.second;
                if (distances[node] != numeric_limits<int>::max() && distances[dest] > distances[node] + weight) {
                    distances[dest] = distances[node] + weight;
                    previous[dest] = node;  // Update the predecessor for the destination node.
                }
            }
        }
    }

    return distances;
}

void printShortestPaths(const vector<GNode*>& graph, GNode* s, int threshold) {
    unordered_map<GNode*, GNode*> previous; // to keep track of the path
    auto dist_dct = shortestpath(graph, s, previous);

    for (const auto& node_distance_pair : dist_dct) {
        GNode* dest = node_distance_pair.first;
        if (s->id != dest->id && node_distance_pair.second <= threshold) {
            vector<int> path;
            GNode* current = dest;
            while (current) {
                path.push_back(current->id);
                current = previous[current];
            }
            reverse(path.begin(), path.end()); // to get the path from source to destination

            cout << "(" << s->id << ", " << dest->id << ") : [";
            for (int i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i != path.size() - 1) cout << ", ";
            }
            cout << "]" << endl;
        }
    }
}

int main() {
    vector<GNode*> graph;  // 그래프 정보를 저장할 벡터

    // 노드 생성
    GNode* node0 =  new GNode(0);
    GNode* node1 =  new GNode(1);
    GNode* node2 =  new GNode(2);
    GNode* node3 =  new GNode(3);

    // 각 노드의 인접 정보 및 간선의 가중치 설정
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

    // 각 노드에 대해서 거리 임계값 이하인 도시들의 최단 경로를 출력
    int threshold = 4;
    for (GNode* source : graph) {
        printShortestPaths(graph, source, threshold);
    }

    // 메모리 해제
    for (GNode* node : graph) {
        delete node;
    }

    return 0;
}
