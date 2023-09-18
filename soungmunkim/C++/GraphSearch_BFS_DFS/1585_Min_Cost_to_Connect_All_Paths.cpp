#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/* ============================= 두 개의 점 리스트를 입력받아 둘 사이의 Manhattan 거리를 계산하는 함수 ============================= */ 
int get_weight(pair<int, int> p1, pair<int, int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}
/* =================================================================================================================== */

/* ==================================== 점들의 리스트를 받아 adjacency list를 만드는 함수 ==================================== */ 
unordered_map<pair<int, int>, vector<pair<pair<int, int>, int>>> build_graph(vector<pair<int, int>> points) {
    unordered_map<pair<int, int>, vector<pair<pair<int, int>, int>>> graph;
    for (auto from_ : points) {
        for (auto to : points) {
            if (from_ == to) continue;
            int weight = get_weight(from_, to);
            graph[from_].push_back({to, weight});
            graph[to].push_back({from_, weight});
        }
    }
    return graph;
}
/* =================================================================================================================== */

unordered_map<pair<int, int>, pair<int, int>> parents;
unordered_map<pair<int, int>, int> tree_rank;

/* ==================================== 각 node의 parent와 tree_rank를 초기화하는 함수 ==================================== */ 
void make_set(pair<int, int> v) {
    parents[v] = v;            // 현재 노드의 부모를 자신으로 초기화합니다.
    tree_rank[v] = 0;          // 현재 노드의 트리 랭크를 0으로 초기화합니다.
}
/* =================================================================================================================== */

/* ======================================= 각 node가 속한 집합의 대표 원소를 찾는 함수 ======================================== */ 
pair<int, int> find_set(pair<int, int> v) {
    if (v != parents[v]) {                 // 노드 v의 부모가 자신이 아니라면(즉, 루트 노드가 아니라면)
        parents[v] = find_set(parents[v]); // 재귀적으로 노드 v의 집합의 대표 원소(루트)를 찾습니다.
    }
    return parents[v];                     // 노드 v의 집합의 대표 원소(루트)를 반환합니다.
}
/* =================================================================================================================== */

/* ============================================ 두 node를 서로 연결하는 함수 ============================================== */
void union_sets(pair<int, int> v1, pair<int, int> v2) {
    auto root1 = find_set(v1);   // v1의 집합의 대표 원소(루트)를 찾습니다.
    auto root2 = find_set(v2);   // v2의 집합의 대표 원소(루트)를 찾습니다.

    if (root1 == root2) return;  // 두 노드가 같은 집합에 속한다면 아무 작업도 수행하지 않습니다.

    if (tree_rank[root1] < tree_rank[root2]) {   // root1의 트리 랭크가 root2의 트리 랭크보다 작다면
        parents[root1] = root2;                  // root1의 부모를 root2로 설정하여 두 집합을 합칩니다.
    } else if (tree_rank[root1] > tree_rank[root2]) {  // 반대의 경우에는
        parents[root2] = root1;                          // root2의 부모를 root1로 설정하여 두 집합을 합칩니다.
    } else {
        parents[root2] = root1;                  // 두 트리 랭크가 같다면, root2의 부모를 root1로 설정하고
        tree_rank[root1]++;                      // root1의 트리 랭크를 1 증가시킵니다.
    }
}
/* =================================================================================================================== */

/* ================================= kruskal을 수행하고 minimum spanning tree를 반환하는 함수 =============================== */
vector<tuple<pair<int, int>, pair<int, int>, int>> kruskalMST(const unordered_map<pair<int, int>, vector<pair<pair<int, int>, int>>>& graph) {
    // 최소 신장 트리에 포함되는 간선들을 저장할 벡터
    vector<tuple<pair<int, int>, pair<int, int>, int>> ans;

    // 그래프의 모든 노드에 대하여 make_set 함수를 호출하여 초기화 작업을 수행
    for (const auto& [point, _] : graph) {
        make_set(point);
    }

    // 그래프의 모든 간선을 저장할 벡터
    vector<tuple<pair<int, int>, pair<int, int>, int>> edges;

    // 그래프의 모든 노드와 연결된 인접 노드들에 대해 간선 정보를 저장
    for (const auto& [point, adj_list] : graph) {
        for (const auto& [to, weight] : adj_list) {
            edges.push_back({point, to, weight});
        }
    }

    // 저장된 간선들을 가중치를 기준으로 오름차순 정렬
    sort(edges.begin(), edges.end(), [](const auto& lhs, const auto& rhs) {
        return get<2>(lhs) < get<2>(rhs);
    });

    // 정렬된 간선들에 대하여
    for (const auto& [u, v, weight] : edges) {
        // 두 노드 u와 v가 서로 다른 집합에 속한다면(즉, 사이클을 형성하지 않는다면)
        if (find_set(u) != find_set(v)) {
            // 해당 간선을 선택한 간선 목록에 추가
            ans.push_back({u, v, weight});
            // 두 노드 u와 v를 같은 집합으로 합침
            union_sets(u, v);
        }
    }

    // 최소 신장 트리에 포함되는 간선들을 반환
    return ans;
}
/* =================================================================================================================== */

/* ============================= kruskal을 수행하고 minimum spanning tree의 cost를 반환하는 함수 ============================= */
int kruskalCost(unordered_map<pair<int, int>, vector<pair<pair<int, int>, int>>> graph) {
    vector<tuple<pair<int, int>, pair<int, int>, int>> edges, ans;   // 그래프의 간선들을 저장할 벡터와 최종 선택된 간선들을 저장할 벡터

    // 모든 노드에 대해
    for (auto [point, adj_list] : graph) {
        // 해당 노드와 연결된 인접 노드들의 정보를 가져와
        for (auto [to, weight] : adj_list) {
            // 간선 목록에 추가합니다.
            edges.push_back({point, to, weight});
        }
    }

    // 간선들을 가중치를 기준으로 오름차순 정렬합니다.
    sort(edges.begin(), edges.end(), [](auto a, auto b) {
        return get<2>(a) < get<2>(b);
    });

    // 모든 간선들에 대해
    for (auto [u, v, weight] : edges) {
        // 두 노드 u와 v가 서로 다른 집합에 속한다면(즉, 사이클을 형성하지 않는다면)
        if (find_set(u) != find_set(v)) {
            // 해당 간선을 선택한 간선 목록에 추가하고
            ans.push_back({u, v, weight});
            // 두 노드 u와 v를 같은 집합으로 합칩니다.
            union_sets(u, v);
        }
    }

    int cost = 0;  // 최종적으로 선택된 간선들의 총 가중치를 저장할 변수

    // 선택된 간선들의 가중치를 합산합니다.
    for (auto [u, v, weight] : ans) {
        cost += weight;
    }

    return cost;   // 총 가중치를 반환합니다.
}
/* =================================================================================================================== */

int minCostConnectPoints(vector<pair<int, int>> points) {
    auto graph = build_graph(points);
    return kruskalCost(graph);
}

int main() {
    vector<pair<int, int>> points = {{0,0},{2,2},{3,10},{5,2},{7,0}};
    cout << minCostConnectPoints(points) << endl;

    vector<pair<int, int>> points2 = {{3,12},{-2,5},{-4,1}};
    cout << minCostConnectPoints(points2) << endl;

    return 0;
}
