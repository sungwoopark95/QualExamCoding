/*
[directed graph 순서 나열하기 (topological order)]

There are a total of numCourses courses you have to take, 
    labeled from 0 to numCourses - 1. 
You are given an array prerequisites 
    where prerequisites[i] = [ai, bi] indicates that 
    you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 
you have to first take course 1. (directed graph)
Return the ordering of courses you should take to finish all courses. 
If there are many valid answers, return any of them. 
If it is impossible to finish all courses, return an empty array.


Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So the correct course order is [0,1].

numCourses = 4
prerequisites = [[1,0],[2,0],[3,1],[3,2]]
findOrder(numCourses, prerequisites)
[0, 1, 2, 3]

numCourses = 1
prerequisites = []
findOrder(numCourses, prerequisites)
[0]

(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % c++ -std=c++17 210_CourseSchedule2.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test
[0,1]
[0,1,2,3]
[0]
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> G(numCourses);  // number of courses만큼 graph adj list 만들기

    // 각 edge들 정보 추가하기 (directed)
    for (auto& edge : prerequisites) {
        int want = edge[0];
        int pre = edge[1];
        G[pre].push_back(want);
    }

    vector<int> indegree(numCourses, 0); // 모든 노드의 진입차수를 0으로 초기화

    // 각 노드의 진입 차수 계산함
    for (auto& neighbors : G) {
        for (int neighbor : neighbors) {
            indegree[neighbor]++;
        }
    }

    queue<int> Q;
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) {  // 진입차수가 0인 node를 큐에 넣는다.
            Q.push(i);
        }
    }

    vector<int> order;  // 위상 순서를 저장할 리스트
    while (!Q.empty()) { // 큐가 비어있지 않으면 반복
        int cur = Q.front();
        Q.pop();
        order.push_back(cur); // 현재 node 리스트에 추가

        for (int adj : G[cur]) { // 인접 노드 돌기
            indegree[adj]--;  // 인접 노드의 진입 차수 감소
            if (indegree[adj] == 0) {  // 진입차수가 0이면 Q 추가
                Q.push(adj);
            }
        }
    }

    // 모든 정점을 방문하지 않은 경우 (cycle 존재함)
    if (order.size() != G.size()) {
        cout << "[]" << endl;
    } else {
        cout << "[";
        for (size_t i = 0; i < order.size(); i++) {
            cout << order[i];
            if (i != order.size() - 1) {
                cout << ",";
            }
        }
        cout << "]" << endl;
    }
}


int main() {
    vector<vector<int>> prerequisites;
    vector<int> result;

    prerequisites = {{1, 0}};
    findOrder(2, prerequisites);
  

    prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    findOrder(4, prerequisites);
    

    prerequisites = {};
    findOrder(1, prerequisites);

    return 0;
}


/*------------------ GNode class 버전으로 구현 --------------------*/

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <unordered_map>

// using namespace std;

// class GNode {
// public:
//     int id;                        // 노드의 ID 혹은 번호
//     vector<int> out_nodes;         // 이 노드로부터 나가는 간선의 목록
//     int in_degree;                 // 이 노드로 들어오는 간선의 개수 (진입차수)

//     GNode(int _id) : id(_id), in_degree(0) {}
// };

// vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
//     unordered_map<int, GNode*> graph;  // 그래프 저장을 위한 해시맵

//     // 각 번호를 가진 GNode 객체로 그래프 초기화
//     for (int i = 0; i < numCourses; ++i) {
//         graph[i] = new GNode(i);
//     }

//     // 그래프 구성하기
//     for (vector<int>& pair : prerequisites) {
//         int next_course = pair[0];
//         int prev_course = pair[1];
//         graph[prev_course]->out_nodes.push_back(next_course);  // 나가는 간선 정보 추가
//         graph[next_course]->in_degree++;                       // 진입차수 증가
//     }

//     // 진입차수가 0인 노드들로 큐 초기화
//     queue<int> Q;
//     for (auto& [id, node] : graph) {
//         if (node->in_degree == 0) {
//             Q.push(id);
//         }
//     }

//     vector<int> order;  // 위상 정렬 결과를 저장할 벡터

//     // 큐를 이용한 위상 정렬 수행
//     while (!Q.empty()) {
//         int node = Q.front(); Q.pop();  // 큐의 앞에서 노드 추출
//         order.push_back(node);          // 결과 벡터에 노드 추가

//         // 현재 노드의 나가는 간선에 연결된 노드들의 진입차수 감소
//         for (int next_node : graph[node]->out_nodes) {
//             graph[next_node]->in_degree--;
//             // 진입차수가 0이 된 노드는 큐에 추가
//             if (graph[next_node]->in_degree == 0) {
//                 Q.push(next_node);
//             }
//         }
//     }

//     // 동적 할당한 메모리 해제
//     for (auto& [id, node] : graph) {
//         delete node;
//     }

//     return order;
// }

// int main() {
//     // 예제 코드
//     vector<vector<int>> prerequisites = {{1,0},{2,0},{3,1},{3,2}};
//     int numCourses = 4;
//     vector<int> order = findOrder(numCourses, prerequisites);
    
//     // 모든 정점을 방문하지 않은 경우 (cycle 존재함)
//     if (order.size() != numCourses) {
//         cout << "[]" << endl;
//     } else {
//         cout << "[";
//         for (size_t i = 0; i < order.size(); i++) {
//             cout << order[i];
//             if (i != order.size() - 1) {
//                 cout << ",";
//             }
//         }
//         cout << "]" << endl;
//     }

//     return 0;
// }
