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

// 시작 정점에서 다른 정점까지의 거리가 threshold보다 작거나 같은 도시의 개수를 반환하는 함수
int NumCities(Graph* G, Vertex* start, int threshold) {
    // 그래프의 정점 개수를 가져옵니다.
    int N = G->GetNumVertices();

    // floyd_warshall 알고리즘을 사용하여 모든 쌍의 최단 거리를 계산합니다.
    vector<vector<float>> distances = floyd_warshall(G).first;
    
    int cnt = 0;  // threshold 이하의 거리를 가지는 도시의 개수를 저장할 변수
    int startIndex = -1;
    vector<Vertex*> vertices = G->GetVertices();

    // 시작 정점의 인덱스를 찾습니다.
    for (int i = 0; i < N; i++) {
        if (vertices[i] == start) {
            startIndex = i;
            break;
        }
    }

    // 모든 정점에 대해 거리가 threshold 이하인 정점의 개수를 세줍니다.
    for (int i = 0; i < N; i++) {
        if (startIndex == i || distances[startIndex][i] > threshold) { 
            continue;  // 자기 자신이거나 거리가 threshold보다 큰 경우 건너뜁니다.
        }
        cnt++;  // threshold 이하인 도시 개수를 카운트
    }
    return cnt;  // 결과 반환
}

// threshold 이하의 거리를 가지는 도시의 개수가 가장 적은 도시의 ID를 반환하는 함수
int FindTheCity(Graph* G, int threshold) {
    int max = INT_MIN;  // 도시의 ID 중 최대값을 저장할 변수
    int min = INT_MAX;  // threshold 이하의 거리를 가지는 도시의 최소 개수를 저장할 변수

    // 모든 도시에 대해
    for (Vertex* v : G->GetVertices()) {
        // 현재 도시에서 threshold 이하의 거리를 가지는 도시의 개수를 계산
        int num_cities = NumCities(G, v, threshold);

        // 현재 도시가 최소 개수를 가지는 경우
        if (num_cities <= min) {
            min = num_cities;

            // 현재 도시의 ID가 이전에 발견된 도시의 ID보다 큰 경우 업데이트
            if (v->GetId() > max) {
                max = v->GetId();
            }
        }
    }
    return max;  // 결과 반환
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
