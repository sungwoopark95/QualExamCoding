/*
[Shortest Path tree edges (Bellman-Ford Algorithm)]

Suppose that the vertex 1 is root.
You will need to print out the sequence of the shortest-paths tree edges 
    selected when the Bellman-ford algorithm is run on given graph from source.

(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % g++ -std=c++17 모의코테2_ShortestPathsTreeEdges_SM.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test                                                        
(5, 2) (1, 3) (1, 4) (3, 5) 
*/

#include <iostream>  // 입출력 관련 헤더 파일 포함
#include <string>    // 문자열 관련 헤더 파일 포함
#include <vector>    // 벡터 관련 헤더 파일 포함

using namespace std; // 표준 네임스페이스 사용 선언

class GNode;  // GNode 클래스의 전방 선언 (아직 정의되지 않았지만 Edge 클래스에서 참조할 예정)

// 그래프의 간선을 표현하는 클래스
class Edge{
    public:
        GNode* to;      // 이 간선이 연결하는 노드에 대한 포인터
        int weight;     // 간선의 가중치

        // 생성자: 대상 노드와 가중치로 초기화
        Edge(GNode* toNode, int w) { 
            to = toNode;    // 대상 노드 초기화
            weight = w;     // 가중치 초기화
        }
};

// 그래프의 노드를 표현하는 클래스
class GNode {
    public:
        int id;                  // 노드의 고유 ID
        string color;            // 노드의 색상 (현재 사용하지 않음)
        int distance;            // 시작 노드로부터의 거리
        GNode* parent;           // BFS나 DFS 수행시 부모 노드
        vector<Edge> edges;      // 노드에 연결된 간선들의 목록

        // 생성자: 노드의 속성들을 초기화
        GNode(int id_val, string color_val = "W", int d_val = INT_MAX, GNode* p_val = nullptr) {
            id = id_val;
            color = color_val;
            distance = d_val;
            parent = p_val;
        }

        // 노드에 간선을 추가하는 메소드
        void addEdge(GNode* toNode, int w) {
            edges.push_back(Edge(toNode, w)); // 벡터에 edge 객체 추가
        }
};

// Bellman-Ford 알고리즘 수행 함수
void bellmanFord(GNode* source, vector<GNode*>& graph) {
    source->distance = 0;  // 시작 노드의 거리를 0으로 초기화

    // 모든 노드와 간선에 대해 relaxation을 수행
    for (size_t i = 1; i < graph.size(); ++i) {
        for (GNode* node : graph) {
            for (Edge edge : node->edges) {
                // relaxation 실행
                if (node->distance + edge.weight < edge.to->distance) {
                    edge.to->distance = node->distance + edge.weight;
                    edge.to->parent = node; // 부모 노드 업데이트
                }
            }
        }
    }
}

// 최단 경로 트리의 edges 출력하는 함수
void print_shortest_path(GNode* source, vector<GNode*>& graph) {
    bellmanFord(source, graph);  // 최단 경로 계산

    cout << "최단 경로 트리의 간선들: ";
    for (GNode* node : graph) {
        if (node->parent) {  // 부모 노드가 있는 경우 출력
            cout << "(" << node->parent->id << ", " << node->id << ") ";
        }
    }
    cout << endl;  // 줄 바꿈
}

// 메인 함수
int main() {
    vector<GNode*> graph;
    
    GNode* node1 =  new GNode(1);
    GNode* node2 =  new GNode(2);
    GNode* node3 =  new GNode(3);
    GNode* node4 =  new GNode(4);
    GNode* node5 =  new GNode(5);

    node1->addEdge(node2, 6);
    node1->addEdge(node3, 1);
    node1->addEdge(node4, 4);
    node1->addEdge(node5, 6);
    node3->addEdge(node5, 1);
    node4->addEdge(node2, 2);
    node4->addEdge(node5, 4);
    node5->addEdge(node2, 3);
    
    graph.push_back(node1);
    graph.push_back(node2);
    graph.push_back(node3);
    graph.push_back(node4);
    graph.push_back(node5);
    
    print_shortest_path(node1, graph);

    return 0;
}



/*--------------- [shortestdistance랑 parent를 따로 Vector로 저장해서 푼 방법] ----------------*/
// #include <iostream>
// #include <string>
// #include <vector>

// using namespace std;

// class GNode;  // GNode 클래스의 선언. 아래 Edge 클래스에서 사용하기 위함.

// // 그래프의 간선을 표현하는 클래스
// class Edge{
//     public:
//         GNode* to;      // 이 간선이 연결하는 대상 노드
//         int weight;     // 간선의 가중치

//         // 생성자: 대상 노드와 가중치를 초기화
//         Edge(GNode* toNode, int w){ 
//             to = toNode;
//             weight = w;
//         }
// };

// // GNode 클래스: 그래프의 노드 정보를 나타내는 클래스
// class GNode{
//     public:
//         int id;             // 노드의 고유 번호
//         string color;       // 노드의 색상. 현재 사용되지 않는 변수
//         int distance;       // 시작 노드로부터의 거리. 현재 사용되지 않는 변수
//         GNode* parent;      // BFS 또는 DFS 실행시 참조될 부모 노드. 현재 사용되지 않는 변수
//         vector<Edge> edges; // 이 노드에 연결된 모든 간선들의 리스트

//         // GNode 클래스의 생성자
//         // 노드 ID와 다른 속성들로 초기화한다.
//         GNode(int id_val, string color_val = "W", int d_val = INT_MAX, GNode* p_val = nullptr){
//             id = id_val;
//             color = color_val;
//             distance = d_val;
//             parent = p_val;
//         }

//         // 이 노드에 새로운 간선을 추가하는 메소드
//         void addEdge(GNode* toNode, int w) {
//             edges.push_back(Edge(toNode, w));
//         }
// };

// vector<int> shortestDistance; // 각 노드까지의 최단 거리 정보 저장용 벡터
// vector<GNode*> predecessor;   // 최단 경로 트리에서의 각 노드의 선행 노드 정보 저장용 벡터

// // 모든 노드의 거리를 무한대로 초기화하는 함수
// void Initialize_Single_Source(vector<GNode*>& graph, GNode* source) {
//     // 각 size를 Graph size에 맞게 조정
//     shortestDistance.resize(graph.size()+1, INT_MAX);
//     predecessor.resize(graph.size()+1);

//     for(GNode* node: graph){
//         shortestDistance[node->id] = INT_MAX;  // 거리를 무한대로 설정
//         predecessor[node->id] = nullptr;       // 선행 노드는 없음으로 설정
//     }
//     shortestDistance[source->id] = 0;  // 시작 노드의 거리는 0
// }

// // 노드 u와 v 사이의 거리를 필요시 업데이트하는 함수
// void Relax(GNode* u, GNode* v, int w) {
//     // u를 통해 v로 가는 거리가 직접 가는 것보다 짧으면 업데이트
//     if(shortestDistance[v->id] > shortestDistance[u->id] + w) {
//         shortestDistance[v->id] = shortestDistance[u->id] + w;
//         predecessor[v->id] = u;
//     }
// }

// // Bellman-Ford 알고리즘을 이용한 최단 경로 및 결과 출력 함수
// void print_shortest_path(GNode* source, vector<GNode*>& graph, vector<GNode*>& predecessor) {
//     Initialize_Single_Source(graph, source);  // 초기 설정

//     // 모든 간선에 대해서 Relax 연산을 수행
//     for(int i = 1; i <= graph.size() - 1; i++) {
//         for(GNode* u: graph) {
//             for(Edge e: u->edges) {
//                 Relax(u, e.to, e.weight);
//             }
//         }
//     }

//     // 음수 가중치의 사이클 존재 여부를 체크
//     for(GNode* u: graph) {
//         for(Edge e: u->edges) {
//             if(shortestDistance[e.to->id] > shortestDistance[u->id] + e.weight) {
//                 cerr << "그래프에 negative weight cycle이 있습니다." << endl;
//                 return;
//             }
//         }
//     }

//     // 최단 경로 트리의 간선을 출력
//     for(GNode* node: graph) {
//         // parent 노드가 있으면 출력하기 (연결되어 있는 이전 노드, 현재 노드)
//         if (predecessor[node->id]) {
//             cout << "(" << predecessor[node->id]->id << ", " << node->id << ") ";
//         }
//     }
//     cout << endl;
// }

// // 메인 함수
// int main() {
//     vector<GNode*> graph;
    
//     GNode* node1 =  new GNode(1);
//     GNode* node2 =  new GNode(2);
//     GNode* node3 =  new GNode(3);
//     GNode* node4 =  new GNode(4);
//     GNode* node5 =  new GNode(5);

//     node1->addEdge(node2, 6);
//     node1->addEdge(node3, 1);
//     node1->addEdge(node4, 4);
//     node1->addEdge(node5, 6);
//     node3->addEdge(node5, 1);
//     node4->addEdge(node2, 2);
//     node4->addEdge(node5, 4);
//     node5->addEdge(node2, 3);
    
//     graph.push_back(node1);
//     graph.push_back(node2);
//     graph.push_back(node3);
//     graph.push_back(node4);
//     graph.push_back(node5);
    
//     print_shortest_path(node1, graph, predecessor);

//     return 0;
// }

