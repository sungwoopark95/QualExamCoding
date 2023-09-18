#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

pair<map<int, int>, map<int, int>> bellmanFord(const map<int, vector<pair<int, int>>>& G, int source) {
    map<int, int> distance, parents;
    // initialize
    for (const auto& node : G) {
        distance[node.first] = INF;
    }
    distance[source] = 0;

    // start
    for (int i = 0; i < G.size(); i++) {
        for (const auto& [u, adjList] : G) {
            for (const auto& [v, weight] : adjList) {
                if (distance[u] != INF && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    parents[v] = u;
                }
            }
        }
    }

    // check negative cycle
    for (const auto& [u, adjList] : G) {
        for (const auto& [v, weight] : adjList) {
            if (distance[u] != INF && distance[u] + weight < distance[v]) {
                return {{}, {}};
            }
        }
    }

    return {distance, parents};
}

int closestMeetingNode(const vector<int>& edges, int node1, int node2) {
    // construct graph
    map<int, vector<pair<int, int>>> graph;
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i] != -1) {
            graph[i].emplace_back(edges[i], 1);
        }
    }

    // bellman ford
    vector<map<int, int>> distances;
    for (const auto& [source, _] : graph) {
        if (source == node1 || source == node2) {
            auto [distance_dict, parents_dict] = bellmanFord(graph, source);
            if (distance_dict.empty()) {
                return -1;
            }
            distances.push_back(distance_dict);
        }
    }

    if (distances.size() == 2) {
        auto& distance1 = distances[0];
        auto& distance2 = distances[1];
        vector<pair<int, int>> both_destinations;
        for (const auto& [key, _] : graph) {
            if (distance1[key] != INF && distance2[key] != INF) {
                int maxweight = max(distance1[key], distance2[key]);
                both_destinations.emplace_back(key, maxweight);
            }
        }
        if (both_destinations.empty()) {
            return -1;
        }
        sort(both_destinations.begin(), both_destinations.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.second == b.second) return a.first < b.first;
            return a.second < b.second;
        });
        return both_destinations[0].first;
    } else {
        // when node1 == node2
        auto& dist_dict = distances[0];
        int min_dist = INF, min_key = INF;
        for (const auto& [key, dist] : dist_dict) {
            if (key == node1) continue; // Exclude node1 or node2
            if (min_dist > dist) {
                min_dist = dist;
                min_key = key;
            } else if (min_dist == dist) {
                min_key = min(min_key, key);
            }
        }
        return min_key;
    }
}

int main() {
    vector<int> edges1 = {2,2,3,-1};
    cout << "Output: " << closestMeetingNode(edges1, 0, 1) << endl;

    vector<int> edges2 = {1,2,-1};
    cout << "Output: " << closestMeetingNode(edges2, 0, 2) << endl;

    return 0;
}
