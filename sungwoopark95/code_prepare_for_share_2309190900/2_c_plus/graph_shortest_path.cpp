
#include <queue>
#include <algorithm>
#include <vector>
#include <limits>
#include <iostream>

using namespace std;

int num_vertex, num_edge, source; //arguments
const int INF = numeric_limits<int>::max(); // int infinity 

int main(void){

    //input process
    cin >> num_vertex >> num_edge >> source;
    source--; //modify due to 0-indexed

    vector<vector<pair<int,int>>> adjacent(num_vertex); //need vector for adjacent list
    vector<int> dist(num_vertex); //distance from source
    vector<int> predecessor(num_vertex); //predecessor on the path from s

    int m=num_edge;
    int start, end, weight;
    while (m--){
        cin >> start >> end >> weight;
        adjacent[start-1].push_back({end-1, weight});
    }

    /*      Dijkstra's algorithm        */

    //initialize-single-source
    fill(dist.begin(), dist.end(), INF);
    fill(predecessor.begin(), predecessor.end(), -1);
    dist[source]=0;

    //priority queue for algorithm
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>> > pq;
    int left_node=num_vertex; // to check the algorithm is over(needed since the priority number can't be updated in the pq)

    for (int i=0;i<num_vertex;++i){
        pq.push(make_pair(dist[i],i));
    }
    pq.push(make_pair(dist[source], source));
    pair<int,int> dist_and_node;
    while (left_node>0){
        dist_and_node=pq.top();
        pq.pop();
        if (dist_and_node.first!=dist[dist_and_node.second]){
            continue; // since the poped one is out-dated
        }
        left_node--;
        for (auto end_and_weight : adjacent[dist_and_node.second]){
            if (dist[end_and_weight.first] > dist[dist_and_node.second] + end_and_weight.second){
                dist[end_and_weight.first] = dist[dist_and_node.second] + end_and_weight.second;
                predecessor[end_and_weight.first]=dist_and_node.second;
                pq.push(make_pair(dist[end_and_weight.first], end_and_weight.first));
            }
        }
    }

    /*      End of algorithm        */

    for (int i=0; i<num_vertex;++i){
        if (dist[i]==INF){cout << "INF" << endl;}
        else {cout << dist[i] << endl;}
    }

    return 0;
}