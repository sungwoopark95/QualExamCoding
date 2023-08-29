#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

class Graph {
private:
    map<int, vector<int>> adj;

    map<int, vector<int>> construct_graph(const string& fname) {
        map<int, vector<int>> adj;
        ifstream file(fname);
        string line;

        while (getline(file, line)) {
            istringstream ss(line);
            int x, y;
            char comma;
            ss >> x >> comma >> y;

            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        return adj;
    }

public:
    Graph(const string& filename) {
        adj = construct_graph(filename);
    }

    map<int, int> bfs(int start) {
        queue<int> q;
        map<int, int> distance;
        q.push(start);
        distance[start] = 0;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            int dist = distance[curr];

            for (int neighbor : adj[curr]) {
                if (distance.find(neighbor) == distance.end()) {
                    q.push(neighbor);
                    distance[neighbor] = dist + 1;
                }
            }
        }

        return distance;
    }

    bool check_distance(int x, int y, int max_distance) {
        map<int, int> distance_dict = bfs(x);
        if (distance_dict.find(y) == distance_dict.end()) {
            return false;
        }
        return distance_dict[y] <= max_distance;
    }
};

int main() {
    // 예제 사용
    Graph g("/Users/sungwoo/Desktop/computer/gsds/QualExamCoding/sungwoopark95/python/BFSDFS/small.txt");
    cout << g.check_distance(1, 5, 2) << endl;
    return 0;
}
