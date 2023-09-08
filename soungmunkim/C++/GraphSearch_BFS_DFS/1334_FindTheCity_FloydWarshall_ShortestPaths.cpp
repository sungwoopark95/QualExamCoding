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

vector<vector<float>> initialize_adj_matrix(Graph* G) {
    int N = G->GetNumVertices();
    vector<Vertex*> vertices = G->GetVertices();
    vector<vector<float>> W;
    W.resize(N, vector<float>(N, numeric_limits<float>::infinity()));

    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            Vertex* u = vertices[i]; 
            Vertex* v = vertices[j];
            if (u == v) { W[i][j] = 0; }
            else {
                auto adj = u->GetAdjacencyList();
                if (adj.find(v) != adj.end()) {
                    // if v in adj
                    W[i][j] = adj[v];
                }
            }
        }
    }
    return W;
}

pair<vector<vector<float>>, vector<vector<float>>> floyd_warshall(Graph* G) {
    int N = G->GetNumVertices();
    vector<vector<float>> W = initialize_adj_matrix(G);
    
    vector<vector<float>> D;
    vector<vector<float>> P;
    D.resize(N, vector<float>(N, 0));
    P.resize(N, vector<float>(N, numeric_limits<float>::infinity()));

    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            D[i][j] = W[i][j];
            if (i != j && W[i][j] != numeric_limits<float>::infinity()) {
                P[i][j] = i;
            }
        }
    }

    for (int k=0;k<N;k++) {
        for (int i=0;i<N;i++) {
            for (int j=0;j<N;j++) {
                if (D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[k][j];
                }
            }
        }
    }

    return make_pair(D, P);
}

vector<int> construct_path(vector<vector<float>>& pred, int start, int end) {
    vector<int> path;
    if (start == end || pred[start][end] == -1) {
        path.push_back(start);
        if (start != end) path.push_back(end);
    } else {
        vector<int> temp = construct_path(pred, start, pred[start][end]);
        path.insert(path.end(), temp.begin(), temp.end());
        path.push_back(end);
    }
    return path;
}

unordered_map<Vertex*, vector<Vertex*>> floyd_warshall_shortest_paths(Graph* G, Vertex* start) {
    auto result = floyd_warshall(G);
    vector<vector<float>> predecessors = result.second;
    vector<Vertex*> vertices = G->GetVertices();
    
    int start_idx = -1;
    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices[i] == start) {
            start_idx = i;
            break;
        }
    }

    unordered_map<Vertex*, vector<Vertex*>> shortest_paths;
    for (int j = 0; j < vertices.size(); ++j) {
        vector<int> id_paths = construct_path(predecessors, start_idx, j);
        vector<Vertex*> vertex_path;
        for (int id : id_paths) {
            vertex_path.push_back(vertices[id]);
        }
        shortest_paths[vertices[j]] = vertex_path;
    }

    return shortest_paths;
}


void PrintShortestPath(Graph* G, Vertex* start, int threshold) {
    // threshold 필요 없는 경우 함수 argument에서 제거하면 됨
    vector<Vertex*> vertices = G->GetVertices();
    vector<vector<float>> distance = floyd_warshall(G).first;
    unordered_map<Vertex*, vector<Vertex*>> shortest_paths = floyd_warshall_shortest_paths(G, start);

    int start_idx = -1;
    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices[i] == start) {
            start_idx = i;
            break;
        }
    }
    
    for (auto& item : shortest_paths) {
        Vertex* to = item.first;
        vector<Vertex*> path = item.second;
        if (start == to) { continue; }

        // threshold 필요 없는 경우 주석 처리
        // if (to->GetKey() > threshold) { continue; }
        int to_idx = -1;
        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[i] == to) {
                to_idx = i;
                break;
            }
        }

        if (distance[start_idx][to_idx] > threshold) { continue; }

        cout << "(" << start->GetId() << ", " << to->GetId() << ") : ";
        bool is_start = true;
        cout << "[";
        for (Vertex* intermediate : path) {
            if (!is_start) {
                cout << ", ";
            }
            cout << intermediate->GetId();
            is_start = false;
        }
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