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

int NumCities(Graph* G, Vertex* start, int threshold) {
    int N = G->GetNumVertices();
    vector<vector<float>> distances = floyd_warshall(G).first;
    
    int cnt = 0;
    int startIndex = -1;
    vector<Vertex*> vertices = G->GetVertices();
    for (int i = 0; i < N; i++) {
        if (vertices[i] == start) {
            startIndex = i;
            break;
        }
    }

    for (int i = 0; i < N; i++) {
        if (startIndex == i || distances[startIndex][i] > threshold) { continue; }  // Skip self.
        cnt++;
    }
    return cnt;
}

int FindTheCity(Graph* G, int threshold) {
    int max = INT_MIN;
    int min = INT_MAX;

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
