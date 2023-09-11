#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <limits>
#include <string>

using namespace std;

class Vertex {
private:
    int id_;
    int key_ = 0;
    unordered_map<Vertex*, int> adjacency_list_;
    Vertex* previous_ = nullptr;

public:
    Vertex(int id) {
        this->id_ = id;
    }

    void AddEdge(Vertex* vertex, int weight) {
        adjacency_list_[vertex] = weight;
    }

    int GetId() { 
        return this->id_; 
    }

    void SetKey(int key) {
        this->key_ = key;
    }

    int GetKey() {
        return this->key_;
    }

    unordered_map<Vertex*, int>& GetAdjacencyList() { 
        return this->adjacency_list_; 
    }

    void SetPrevious(Vertex* prev) { 
        this->previous_ = prev; 
    }
    
    Vertex* GetPrevious() { 
        return this->previous_; 
    }
};

class Graph {
private:
    vector<Vertex*> vertices_;

public:
    Graph() {}

    ~Graph() {
        for (Vertex* vertex : this->vertices_) {
            delete vertex;
        }
        this->vertices_.clear();
    }

    Vertex* addNode(int id) {
        Vertex* newVertex = new Vertex(id);
        this->vertices_.push_back(newVertex);
        return newVertex;
    }

    void addEdge(Vertex* start, Vertex* end, int weight) {
        start->AddEdge(end, weight);
    }

    vector<Vertex*>& GetVertices() { 
        return this->vertices_; 
    }

    int GetNumVertices() {
        return this->vertices_.size();
    }
};

// G 그래프를 기반으로 인접 행렬을 초기화하는 함수
vector<vector<float>> initialize_adj_matrix(Graph* G) {
    // 그래프의 정점 수를 가져옵니다.
    int N = G->GetNumVertices();
    // 그래프의 모든 정점을 가져옵니다.
    vector<Vertex*> vertices = G->GetVertices();
    vector<vector<float>> W;
    // W를 NxN 크기로 확장하고 모든 값을 무한대로 초기화합니다.
    W.resize(N, vector<float>(N, numeric_limits<float>::infinity()));

    // 모든 정점 조합에 대해
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            Vertex* u = vertices[i];
            Vertex* v = vertices[j];
            // 같은 정점이면 0으로 설정합니다.
            if (u == v) { W[i][j] = 0; }
            else {
                // u의 인접 리스트를 가져옵니다.
                auto adj = u->GetAdjacencyList();
                // v가 u의 인접 리스트에 있으면, 해당 가중치로 설정합니다.
                if (adj.find(v) != adj.end()) {
                    W[i][j] = adj[v];
                }
            }
        }
    }
    // 인접 행렬 W를 반환합니다.
    return W;
}

// 그래프 G에 대한 Floyd-Warshall 알고리즘을 실행하는 함수
pair<vector<vector<float>>, vector<vector<float>>> floyd_warshall(Graph* G) {
    // 그래프의 정점 수를 가져옵니다.
    int N = G->GetNumVertices();
    // 인접 행렬을 초기화합니다.
    vector<vector<float>> W = initialize_adj_matrix(G);
    
    vector<vector<float>> D;
    vector<vector<float>> P;
    // D와 P를 NxN 크기로 확장합니다.
    D.resize(N, vector<float>(N, 0));
    P.resize(N, vector<float>(N, numeric_limits<float>::infinity()));

    // D와 P를 초기 설정합니다.
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            D[i][j] = W[i][j];
            // i와 j가 다르며, W[i][j]가 무한대가 아니면, P[i][j]를 i로 설정합니다.
            if (i != j && W[i][j] != numeric_limits<float>::infinity()) {
                P[i][j] = i;
            }
        }
    }

    // 모든 k에 대해 최단 경로를 업데이트합니다.
    for (int k=0;k<N;k++) {
        for (int i=0;i<N;i++) {
            for (int j=0;j<N;j++) {
                // 경로 i->k->j가 i->j보다 짧으면 업데이트합니다.
                if (D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[k][j];
                }
            }
        }
    }

    // 최단 거리 행렬 D와 경로 행렬 P를 반환합니다.
    return make_pair(D, P);
}

// 주어진 후속자 행렬과 시작 및 종료 인덱스를 사용하여 최단 경로를 생성하는 함수
vector<int> construct_path(vector<vector<float>>& pred, int start, int end) {
    vector<int> path;
    // 시작과 종료가 동일하거나 경로가 없는 경우
    if (start == end || pred[start][end] == -1) {
        path.push_back(start);
        if (start != end) path.push_back(end);
    } else {
        // 재귀적으로 경로를 구성
        vector<int> temp = construct_path(pred, start, pred[start][end]);
        // 임시 경로를 기본 경로에 추가
        path.insert(path.end(), temp.begin(), temp.end());
        path.push_back(end);
    }
    return path;
}

// 그래프 G와 시작 정점을 입력으로 받아 최단 경로를 생성하는 함수
unordered_map<Vertex*, vector<Vertex*>> floyd_warshall_shortest_paths(Graph* G, Vertex* start) {
    // floyd_warshall 알고리즘을 사용하여 최단 거리와 후속자 행렬을 가져옴
    auto result = floyd_warshall(G);
    vector<vector<float>> predecessors = result.second;
    vector<Vertex*> vertices = G->GetVertices();
    
    int start_idx = -1;
    // 시작 정점의 인덱스를 찾음
    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices[i] == start) {
            start_idx = i;
            break;
        }
    }

    unordered_map<Vertex*, vector<Vertex*>> shortest_paths;
    // 각 목적지 정점에 대해
    for (int j = 0; j < vertices.size(); ++j) {
        // 최단 경로의 인덱스를 생성
        vector<int> id_paths = construct_path(predecessors, start_idx, j);
        vector<Vertex*> vertex_path;
        // 인덱스 경로를 정점 경로로 변환
        for (int id : id_paths) {
            vertex_path.push_back(vertices[id]);
        }
        // 결과 맵에 정점 경로 저장
        shortest_paths[vertices[j]] = vertex_path;
    }

    // 모든 최단 경로를 반환
    return shortest_paths;
}

// G 그래프에서 start 정점으로부터 모든 다른 정점까지의 최단 경로를 출력하는 함수
void PrintShortestPath(Graph* G, Vertex* start, int threshold) {
    // threshold가 필요 없는 경우, 함수 인자에서 제거하면 됩니다

    // 그래프 G에서 모든 정점을 가져옴
    vector<Vertex*> vertices = G->GetVertices();

    // floyd_warshall 알고리즘을 사용하여 모든 쌍의 최단 거리를 계산
    vector<vector<float>> distance = floyd_warshall(G).first;

    // 시작 정점에서 모든 다른 정점까지의 최단 경로를 계산
    unordered_map<Vertex*, vector<Vertex*>> shortest_paths = floyd_warshall_shortest_paths(G, start);

    int start_idx = -1;
    // 시작 정점의 인덱스를 찾음
    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices[i] == start) {
            start_idx = i;
            break;
        }
    }
    
    // 모든 최단 경로에 대해
    for (auto& item : shortest_paths) {
        Vertex* to = item.first;  // 목적지 정점
        vector<Vertex*> path = item.second;  // 시작에서 목적지까지의 경로

        // 시작 정점과 목적지 정점이 동일한 경우는 건너뛴다
        if (start == to) { continue; }

        // threshold에 따라서 출력 여부를 결정하는 부분 (필요하지 않은 경우 주석 처리 가능)
        int to_idx = -1;
        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[i] == to) {
                to_idx = i;
                break;
            }
        }

        // 거리가 임계값을 초과하면 해당 경로를 건너뜀
        if (distance[start_idx][to_idx] > threshold) { continue; }

        // 시작 정점과 목적지 정점의 ID를 출력
        cout << "(" << start->GetId() << ", " << to->GetId() << ") : ";

        // 경로 상의 중간 정점들을 출력
        bool is_start = true;
        cout << "[";
        for (Vertex* intermediate : path) {
            if (!is_start) {
                cout << ", ";
            }
            cout << intermediate->GetId();
            is_start = false;
        }
        // 최단 거리를 출력
        cout << "] distance : " << distance[start_idx][to_idx] << endl;
    }
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
    for (Vertex* v : graph->GetVertices()) {
        cout << "Shortest path from " << v->GetId() << " : " << endl;
        PrintShortestPath(graph, v, threshold);
        cout << "=========================== DONE ===========================" << endl;
    }
    
    return 0;
}