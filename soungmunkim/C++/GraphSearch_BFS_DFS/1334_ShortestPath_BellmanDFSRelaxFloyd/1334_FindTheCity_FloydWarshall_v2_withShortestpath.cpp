/*
Vertex 버전으로 푼 것
shortest path 찾는것 number city 찾는 것 있지만
프린트 함수는 없음
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <limits>
#include <string>

using namespace std;

class Vertex {
private:
    int id_; // 정점의 ID
    int key_ = 0; // 키 (일반적으로 알고리즘에서 사용됨, 예: 프림 알고리즘)
    unordered_map<Vertex*, int> adjacency_list_; // 인접한 정점과 가중치를 담는 목록
    Vertex* previous_ = nullptr; // 알고리즘에서 사용될 이전 정점 참조

public:
    Vertex(int id) { // 생성자
        this->id_ = id;
    }

    // 정점에 엣지를 추가하는 함수
    void AddEdge(Vertex* vertex, int weight) {
        adjacency_list_[vertex] = weight;
    }

    // 정점의 ID를 반환하는 함수
    int GetId() { 
        return this->id_; 
    }

    // 키를 설정하는 함수
    void SetKey(int key) {
        this->key_ = key;
    }

    // 키를 반환하는 함수
    int GetKey() {
        return this->key_;
    }

    // 인접 리스트를 반환하는 함수
    unordered_map<Vertex*, int>& GetAdjacencyList() { 
        return this->adjacency_list_; 
    }

    // 이전 정점을 설정하는 함수
    void SetPrevious(Vertex* prev) { 
        this->previous_ = prev; 
    }

    // 이전 정점을 반환하는 함수
    Vertex* GetPrevious() { 
        return this->previous_; 
    }
};

class Graph {
private:
    vector<Vertex*> vertices_; // 그래프 내의 모든 정점들을 담는 벡터

public:
    Graph() {} // 기본 생성자

    // 소멸자: 동적으로 할당된 모든 정점들을 해제
    ~Graph() {
        for (Vertex* vertex : this->vertices_) {
            delete vertex;
        }
        this->vertices_.clear();
    }

    // 새로운 정점을 그래프에 추가하는 함수
    Vertex* addNode(int id) {
        Vertex* newVertex = new Vertex(id);
        this->vertices_.push_back(newVertex);
        return newVertex;
    }

    // 엣지를 그래프에 추가하는 함수
    void addEdge(Vertex* start, Vertex* end, int weight) {
        start->AddEdge(end, weight);
    }

    // 모든 정점들을 반환하는 함수
    vector<Vertex*>& GetVertices() { 
        return this->vertices_; 
    }

    // 그래프 내의 정점 개수를 반환하는 함수
    int GetNumVertices() {
        return this->vertices_.size();
    }
};

// 그래프 G를 기반으로 초기 인접 행렬을 생성하는 함수입니다.
vector<vector<float>> initialize_adj_matrix(Graph* G) {
    int N = G->GetNumVertices();  // 그래프 G에 있는 정점의 수를 저장합니다.
    vector<Vertex*> vertices = G->GetVertices();  // 그래프의 정점들을 vertices 벡터에 저장합니다.
    vector<vector<float>> W;  // 가중치를 저장할 2차원 벡터(행렬)입니다.

    // W 행렬을 N x N 크기로 초기화하고, 모든 값을 무한대로 설정합니다.
    W.resize(N, vector<float>(N, numeric_limits<float>::infinity()));

    // 모든 정점 쌍에 대해
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            Vertex* u = vertices[i];  // i 번째 정점
            Vertex* v = vertices[j];  // j 번째 정점
            if (u == v) {  // 동일한 정점 사이의 거리는 0입니다.
                W[i][j] = 0; 
            } else {
                auto adj = u->GetAdjacencyList();  // i번째 정점의 인접 리스트를 가져옵니다.
                if (adj.find(v) != adj.end()) {  // 인접 리스트에 j번째 정점이 있으면
                    W[i][j] = adj[v];  // i에서 j로 가는 간선의 가중치를 W[i][j]에 저장합니다.
                }
            }
        }
    }
    return W;  // 초기화된 인접 행렬을 반환합니다.
}

// Floyd-Warshall 알고리즘을 통해 그래프의 모든 정점 쌍 간의 최단 거리와 경로를 계산하는 함수입니다.
pair<vector<vector<float>>, vector<vector<float>>> floyd_warshall(Graph* G) {
    int N = G->GetNumVertices();  // 그래프의 정점 수를 저장합니다.
    vector<vector<float>> W = initialize_adj_matrix(G);  // 초기 인접 행렬을 구합니다.
    
    vector<vector<float>> D;  // 각 정점 쌍 간의 최단 거리를 저장할 행렬입니다.
    vector<vector<float>> P;  // 경로에서의 전 직전 정점을 저장할 행렬입니다.
    D.resize(N, vector<float>(N, 0));
    P.resize(N, vector<float>(N, numeric_limits<float>::infinity()));

    // D와 P 행렬의 초기값을 설정합니다.
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            D[i][j] = W[i][j];
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
unordered_map<Vertex*, vector<Vertex*>> floyd_warshall_shortest_paths(Graph* G, Vertex* start) {
    auto result = floyd_warshall(G);  // floyd_warshall 함수를 통해 모든 정점 쌍 간의 최단 거리와 경로를 계산합니다.
    vector<vector<float>> predecessors = result.second;  // 모든 정점 쌍에 대한 직전 정점 정보를 가져옵니다.
    vector<Vertex*> vertices = G->GetVertices();  // 그래프의 모든 정점을 가져옵니다.
    
    int start_idx = -1;  // 시작 정점의 인덱스를 찾기 위한 변수입니다.
    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices[i] == start) {
            start_idx = i;  // 시작 정점의 인덱스를 저장하고
            break;  // 루프를 종료합니다.
        }
    }

    unordered_map<Vertex*, vector<Vertex*>> shortest_paths;  // 최단 경로를 저장할 해시 맵입니다.
    for (int j = 0; j < vertices.size(); ++j) {
        // 시작 정점에서 j번째 정점까지의 최단 경로의 정점 인덱스를 가져옵니다.
        vector<int> id_paths = construct_path(predecessors, start_idx, j);
        vector<Vertex*> vertex_path;  // 인덱스를 기반으로 정점의 최단 경로를 구성합니다.
        for (int id : id_paths) {
            vertex_path.push_back(vertices[id]);  // 경로에 해당 정점을 추가합니다.
        }
        shortest_paths[vertices[j]] = vertex_path;  // 해시 맵에 해당 정점의 최단 경로를 저장합니다.
    }

    return shortest_paths;  // 모든 정점에 대한 최단 경로를 반환합니다.
}

int NumCities(Graph* G, Vertex* start, int threshold) {
    // 1. 그래프 G의 정점의 수를 N에 저장합니다.
    int N = G->GetNumVertices();
    // 2. floyd_warshall 알고리즘을 사용하여 그래프 G의 모든 정점 간의 최단 거리를 계산합니다.
    vector<vector<float>> distances = floyd_warshall(G).first;
    
    int cnt = 0;  // threshold 이내의 도시 수를 저장할 변수
    int startIndex = -1;  // 시작 정점의 인덱스를 저장할 변수
    vector<Vertex*> vertices = G->GetVertices();
    for (int i = 0; i < N; i++) {
        if (vertices[i] == start) {
            startIndex = i;
            break;
        }
    }

    // 각 정점까지의 거리를 확인하고, threshold 이내인 경우 카운터를 증가시킵니다.
    for (int i = 0; i < N; i++) {
        if (startIndex == i || distances[startIndex][i] > threshold) { continue; }
        cnt++;
    }
    return cnt;
}

int FindTheCity(Graph* G, int threshold) {
    int max = INT_MIN;  // 도시 ID의 최댓값을 저장할 변수
    int min = INT_MAX;  // 도시의 최솟값을 저장할 변수

    // 모든 도시를 순회하며 threshold 이내에 도달 가능한 도시의 수와 해당 도시의 ID를 확인합니다.
    for (Vertex* v : G->GetVertices()) {
        int num_cities = NumCities(G, v, threshold);
        if (num_cities <= min) {
            min = num_cities;
            if (v->GetId() > max) {
                max = v->GetId();
            }
        }
    }
    return max;
}

int main() {
    Graph* graph = new Graph();

    Vertex* node0 = graph->addNode(0);
    Vertex* node1 = graph->addNode(1);
    Vertex* node2 = graph->addNode(2);
    Vertex* node3 = graph->addNode(3);

    graph->addEdge(node0, node1, 3);
    graph->addEdge(node1, node2, 1);
    graph->addEdge(node1, node3, 4);
    graph->addEdge(node1, node0, 3);
    graph->addEdge(node2, node1, 1);
    graph->addEdge(node2, node3, 1);
    graph->addEdge(node3, node1, 4);
    graph->addEdge(node3, node2, 1);

    int threshold = 4;
    // Print shortest paths for each pair of nodes
    cout << FindTheCity(graph, threshold) << endl;
    return 0;
}
