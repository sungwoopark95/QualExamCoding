#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <climits>

using namespace std;

// GNode 클래스 선언
class GNode {
public:
    int id; // 노드의 ID
    vector<pair<GNode*, int>> edges; // 노드의 인접 노드 및 가중치 정보

    GNode(int _id) {
        this->id = _id;
    } // 생성자

    // 인접 노드 및 가중치 정보를 추가하는 함수
    void addEdge(GNode* toNode, int w) {
        edges.push_back({toNode, w});
    }
};


// 그래프 G를 기반으로 초기 인접 행렬을 생성하는 함수입니다.
vector<vector<float>> initialize_adj_matrix(vector<GNode*>& G) {
    // 그래프 G에 있는 정점의 수를 저장합니다.
    int N = G.size();
    // 가중치를 저장할 2차원 벡터(행렬)입니다.
    vector<vector<float>> W;

    // W 행렬을 N x N 크기로 초기화하고, 모든 값을 무한대로 설정합니다.
    W.resize(N, vector<float>(N, numeric_limits<float>::infinity()));

    // 모든 정점 쌍에 대해
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            GNode* u = G[i]; // i 번째 정점
            GNode* v = G[j]; // j 번째 정점
            // 동일한 정점 사이의 거리는 0입니다.
            if (i == j) { W[i][j] = 0; }
            else {
                // i번째 node의 인접 리스트에 접근합니다.
                for (auto &item : u->edges) {
                    GNode* adj = item.first;
                    int weight = item.second;
                    // j번째 정점이 있으면 i에서 j로 가는 간선의 가중치를 W[i][j]에 저장합니다.
                    if (adj == v) {
                        W[i][j] = weight;
                        break;
                    }
                }
            }
        }
    }
    // 초기화된 인접 행렬을 반환합니다.
    return W;
}

// Floyd-Warshall 알고리즘을 통해 그래프의 모든 정점 쌍 간의 최단 거리와 경로를 계산하는 함수입니다.
pair<vector<vector<float>>, vector<vector<float>>> floyd_warshall(vector<GNode*>& G) {
    int N = G.size();  // 그래프의 정점 수를 저장합니다.
    vector<vector<float>> W = initialize_adj_matrix(G);  // 초기 인접 행렬을 구합니다.
    
    vector<vector<float>> D;  // 각 정점 쌍 간의 최단 거리를 저장할 행렬입니다.
    vector<vector<float>> P;  // 경로에서의 전 직전 정점을 저장할 행렬입니다.
    D.resize(N, vector<float>(N, 0));
    P.resize(N, vector<float>(N, numeric_limits<float>::infinity()));

    // D와 P 행렬의 초기값을 설정합니다.
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            D[i][j] = W[i][j];
            // i와 j가 다르며, W[i][j]가 무한대가 아니면, P[i][j]를 i로 설정합니다.
            if (i != j && W[i][j] != numeric_limits<float>::infinity()) {
                P[i][j] = i;  // 정점 i에서 정점 j로 직접 이어지는 경우, 직전 정점은 i입니다.
            }
        }
    }

    // k를 중간 정점으로 하는 모든 정점 쌍의 거리를 확인하고 업데이트합니다.
    for (int k=0;k<N;k++) {
        for (int i=0;i<N;i++) {
            for (int j=0;j<N;j++) {
                // i에서 j로 가는 기존의 거리보다 i-k-j 경로가 더 짧다면 
                if (D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];  // 거리를 업데이트합니다.
                    P[i][j] = P[k][j];  // 경로에서의 직전 정점을 업데이트합니다.
                }
            }
        }
    }

    // 최종 계산된 D(최단 거리) 행렬과 P(경로) 행렬을 반환합니다.
    return make_pair(D, P);
}

// 주어진 전체 경로 행렬을 기반으로 start에서 end까지의 최단 경로를 구성합니다.
vector<int> construct_path(vector<vector<float>>& pred, int start, int end) {
    vector<int> path;  // 최단 경로를 저장할 벡터입니다.
    
    // 시작점과 끝점이 같거나, 끝점에 도달할 수 없는 경우
    if (start == end || pred[start][end] == -1) {
        path.push_back(start);  // 경로에 시작점을 추가합니다.
        if (start != end) path.push_back(end);  // 시작점과 끝점이 다르면, 경로에 끝점도 추가합니다.
    } else {
        // 시작점부터 중간 지점까지의 경로를 재귀적으로 구합니다.
        vector<int> temp = construct_path(pred, start, pred[start][end]);
        path.insert(path.end(), temp.begin(), temp.end());  // 위에서 구한 경로를 현재 경로에 추가합니다.
        path.push_back(end);  // 최종 끝점을 경로에 추가합니다.
    }
    return path;  // 완성된 경로를 반환합니다.
}

// Floyd-Warshall 알고리즘을 사용하여 start에서 모든 정점까지의 최단 경로를 찾습니다.
unordered_map<GNode*, vector<GNode*>> floyd_warshall_shortest_paths(vector<GNode*>& G, GNode* start) {
    auto result = floyd_warshall(G);  // floyd_warshall 함수를 통해 모든 정점 쌍 간의 최단 거리와 경로를 계산합니다.
    vector<vector<float>> predecessors = result.second;  // 모든 정점 쌍에 대한 직전 정점 정보를 가져옵니다.
    
    int start_idx = -1;  // 시작 정점의 인덱스를 찾기 위한 변수입니다.
    for (int i = 0; i < G.size(); ++i) {
        if (G[i] == start) {
            start_idx = i;  // 시작 정점의 인덱스를 저장하고
            break;  // 루프를 종료합니다.
        }
    }

    unordered_map<GNode*, vector<GNode*>> shortest_paths;  // 최단 경로를 저장할 해시 맵입니다.
    for (int j = 0; j < G.size(); ++j) {
        // 시작 정점에서 j번째 정점까지의 최단 경로의 정점 인덱스를 가져옵니다.
        vector<int> id_paths = construct_path(predecessors, start_idx, j);
        vector<GNode*> vertex_path;  // 인덱스를 기반으로 정점의 최단 경로를 구성합니다.
        for (int id : id_paths) {
            vertex_path.push_back(G[id]);  // 경로에 해당 정점을 추가합니다.
        }
        shortest_paths[G[j]] = vertex_path;  // 해시 맵에 해당 정점의 최단 경로를 저장합니다.
    }

    return shortest_paths;  // 모든 정점에 대한 최단 경로를 반환합니다.
}

int NumCities(vector<GNode*> G, GNode* start, int threshold) {
    // 1. 그래프 G의 정점의 수를 N에 저장합니다.
    int N = G.size();
    // 2. floyd_warshall 알고리즘을 사용하여 그래프 G의 모든 정점 간의 최단 거리를 계산합니다.
    vector<vector<float>> distances = floyd_warshall(G).first;
    
    int cnt = 0;  // threshold 이내의 도시 수를 저장할 변수
    int startIndex = -1;  // 시작 정점의 인덱스를 저장할 변수
    for (int i = 0; i < N; i++) {
        if (G[i] == start) {
            startIndex = i;
            break;
        }
    }

    // 각 정점까지의 거리를 확인하고, threshold 이내인 경우 카운터를 증가시킵니다.
    for (int i = 0; i < N; i++) {
        if (startIndex == i || distances[startIndex][i] > threshold) { continue; }
        cnt++;
    }
    return cnt;  // 결과 반환
}

int FindTheCity(vector<GNode*> G, int threshold) {
    int max = INT_MIN;  // 도시 ID의 최댓값을 저장할 변수
    int min = INT_MAX;  // 도시의 최솟값을 저장할 변수

    // 모든 도시를 순회하며 threshold 이내에 도달 가능한 도시의 수와 해당 도시의 ID를 확인합니다.
    for (GNode* v : G) {
        int num_cities = NumCities(G, v, threshold);

        // 현재 도시가 최소 개수를 가지는 경우
        if (num_cities <= min) {
            min = num_cities;
            if (v->id > max) {
                max = v->id;
            }
        }
    }
    return max;  // 결과 반환
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
    int N = graph.size();
    vector<vector<float>> distance = floyd_warshall(graph).first;
    // floyd warshall 후의 distance matrix 출력
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << distance[i][j] << " ";
        }
        cout << endl;
    }

    GNode* start = node0;
    auto shortest_paths = floyd_warshall_shortest_paths(graph, start);
    for (auto& item : shortest_paths) {
        GNode* adj = item.first;
        vector<GNode*> path = item.second;
        cout << "Shortest path from " << start->id << " to " << adj->id << ": ";
        bool is_first = 1;
        for (GNode* node : path) {
            if (!is_first) { cout << " -> ";}
            cout << node->id;
            is_first = 0;
        }
        cout << endl;
    }

    int threshold = 4;
    // Print shortest paths for each pair of nodes
    cout << FindTheCity(graph, threshold) << endl;
    return 0;
}