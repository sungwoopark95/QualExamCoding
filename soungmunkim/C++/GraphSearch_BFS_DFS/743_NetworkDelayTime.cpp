/*
[전체노드 visit되는 최소한의 시간 구하기 (Directed graph with weight)]
-> Shortest path 찾는 것처럼 푼 뒤 가장 max인 weight 뽑기 (다 들린 후 min time)

You are given a network of n nodes, labeled from 1 to n. 
You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), 
where ui is the source node, vi is the target node, 
and wi is the time it takes for a signal to travel from source to target.

We will send a signal from a given node k. 
Return the minimum time it takes for all the n nodes to receive the signal. 
If it is impossible for all the n nodes to receive the signal, return -1.

(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test                                         
Enter n: 4
Enter k: 2
Enter the times in the format [[from,to,weight],...]:
[[2,1,1],[2,3,1],[3,4,1]]
Minimum time for all nodes to receive the signal: 2

(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test
Enter n: 4
Enter k: 2
Enter the times in the format [[from,to,weight],...]:
[2,1,1],[2,3,1],[3,4,1
Minimum time for all nodes to receive the signal: 2

(base) soungmunkim@gimseongmun-ui-MacBookPro GraphSearch_BFS_DFS % ./test
Enter n: 2
Enter k: 2
Enter the times in the format [[from,to,weight],...]:
[1,2,1]
Minimum time for all nodes to receive the signal: -1
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <climits>

using namespace std;

// 그래프 G와 시작 노드 s를 받아서 모든 노드로의 최단 경로를 반환하는 함수
unordered_map<int, int> shortestpath(const unordered_map<int, vector<pair<int, int>>>& G, int s) {
    unordered_map<int, int> times;  // 각 노드까지의 시간을 저장할 맵

    // 초기화: 모든 노드의 시간을 무한대로 설정
    for (const auto& entry : G) {
        times[entry.first] = INT_MAX;
    }

    times[s] = 0;  // 시작 노드의 시간은 0
    stack<int> stk;  // DFS를 위한 스택
    stk.push(s);  // 시작 노드를 스택에 푸시

    // DFS 시작
    while (!stk.empty()) {
        int cur = stk.top();  // 현재 노드를 스택의 맨 위에서 가져옴
        stk.pop();

        // 인접한 모든 노드를 확인
        for (const auto& [node, weight] : G.at(cur)) {
            // relaxation: 현재 노드를 거쳐서 해당 노드로 가는 경로가 더 짧으면 업데이트
            if (times[node] > times[cur] + weight) {
                times[node] = times[cur] + weight;
                stk.push(node);  // 해당 노드를 스택에 푸시
            }
        }
    }

    return times;  // 최단 경로 반환
}

// n개의 노드와 연결 정보(times), 그리고 신호를 보내는 노드 k에 대해 모든 노드가 신호를 받는데 필요한 최소 시간을 반환
int networkDelayTime(const vector<vector<int>>& times, int n, int k) {
    unordered_map<int, vector<pair<int, int>>> G;  // 그래프 정보를 저장할 맵

    // 그래프 초기화
    for (int i = 1; i <= n; i++) {
        G[i] = {};
    }

    // 연결 정보를 그래프에 추가
    for (const auto& time : times) {
        int from = time[0];
        int to = time[1];
        int weight = time[2];

        G[from].push_back({to, weight});
    }

    // 모든 노드로의 최단 경로를 계산
    auto paths = shortestpath(G, k);

    int max_time = -1;
    // 모든 노드가 신호를 받는데 필요한 최소 시간을 계산
    for (const auto& [node, time] : paths) {
        if (time == INT_MAX) {  // 노드까지 도달할 수 없는 경우
            return -1;
        }
        max_time = max(max_time, time);  // 최대 시간 업데이트
    }

    return max_time;  // 결과 반환
}

int main() {
    int n, k;
    // n(노드의 수) 입력 받기
    cout << "Enter n: ";
    cin >> n;

    // k(시작 노드) 입력 받기
    cout << "Enter k: ";
    cin >> k;

    string input;
    // 연결 정보(times) 입력 받기
    // [from, to , weigh], .. 도 가능
    cout << "Enter the times in the format [[from,to,weight],...]:\n";
    cin >> input; // 전체 연결 정보를 한 문자열로 받음

    vector<vector<int>> times; // 연결 정보를 저장할 벡터

    size_t pos = 0;
    // 문자열 내의 모든 연결 정보를 처리
    while ((pos = input.find('[')) != string::npos) {
        input.erase(0, pos + 1); // 첫 번째 '[' 문자를 제거

        // 여기에 추가적인 코드를 넣습니다.
        if (input[0] == '[') {
            input.erase(0, 1); // 두 번째 '[' 문자를 제거
        }

        vector<int> time(3); // 각 연결 정보를 저장할 벡터

        for (int i = 0; i < 3; i++) {
            char delimiter; // 구분자를 저장할 변수
            if (i == 2) {
                delimiter = ']'; // 마지막 구분자는 ']' 이다
            } else {
                delimiter = ','; // 처음 두 구분자는 ',' 이다
            }

            size_t end_pos = input.find(delimiter); // 구분자의 위치 찾기

            // 변환하려는 문자열의 부분이 정상인지 확인하기 위해 출력 (나중에 제거 가능)
            // cout << "Trying to convert: " << input.substr(0, end_pos) << endl; 

            time[i] = stoi(input.substr(0, end_pos)); // 구분자까지의 부분을 int로 변환
            input.erase(0, end_pos + 1); // 현재 처리한 부분을 문자열에서 제거
        }
        times.push_back(time); // 연결 정보를 벡터에 추가
    }


    // 모든 노드가 신호를 받는 데 필요한 최소 시간 출력
    cout << "Minimum time for all nodes to receive the signal: " << networkDelayTime(times, n, k) << endl;

    return 0;
}
