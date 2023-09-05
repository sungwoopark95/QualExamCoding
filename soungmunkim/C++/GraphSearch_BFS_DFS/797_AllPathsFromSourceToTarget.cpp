/*
[All paths From Source to Target]
DAG사용해서 풀기 (Directed Acyclic graph)

there is a directed edge from node i to node graph[i][j]

Input: graph = [[1,2],[3],[3],[]]
Output: [[0,1,3],[0,2,3]]
Explanation: There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.

Input: graph = [[4,3,1],[3,2,4],[3],[4],[]]
Output: [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]

(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % g++ -std=c++17 797_AllPathsFromSourceToTarget.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test
가능한 모든 경로:
0 -> 1 -> 4 -> END
0 -> 1 -> 2 -> 3 -> 4 -> END
0 -> 1 -> 3 -> 4 -> END
0 -> 3 -> 4 -> END
0 -> 4 -> END
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <algorithm> // find 함수를 사용하기 위해 포함

using namespace std;

vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    // 그래프를 map (Python의 dictionary와 유사) 형태로 만들기
    unordered_map<int, vector<int>> G;
    for (int i = 0; i < graph.size(); ++i) {
        G[i] = graph[i];
    }

    // DFS 탐색을 위한 스택 사용
    stack<pair<int, vector<int>>> stack;

    // 시작 노드 및 해당 경로
    stack.push({0, {0}});

    vector<vector<int>> allpaths;
    while (!stack.empty()) {
        int cur = stack.top().first;
        vector<int> path = stack.top().second;
        stack.pop();

        // 현재 노드에서 갈 수 있는 인접 노드가 없다면
        if (G[cur].empty()) {
            allpaths.push_back(path);
            continue;
        }

        for (int adj : G[cur]) {
            // 경로에 인접 노드가 포함되지 않았는지 확인 (비순환 경로를 확보)
            /*
            find 함수는 주어진 범위 내에서 원하는 값을 찾기 위해 사용되며, 
            해당 값이 범위 내에 없으면 마지막 iterator를 반환
            */
            if (find(path.begin(), path.end(), adj) == path.end()) {
                vector<int> newPath = path;
                newPath.push_back(adj);
                stack.push({adj, newPath});
            }
        }
    }

    return allpaths;
}

int main() {
    vector<vector<int>> graph = {{4,3,1},{3,2,4},{3},{4},{}};
    vector<vector<int>> result = allPathsSourceTarget(graph);

    cout << "가능한 모든 경로:" << endl;
    for (vector<int>& path : result) {
        for (int node : path) {
            cout << node << " -> ";
        }
        cout << "END" << endl;
    }

    return 0;
}
