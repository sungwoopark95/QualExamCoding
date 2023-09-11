// Prim's Algorithm in C++

#include <cstring>
#include <iostream>
using namespace std;

#define INF 9999999  // 무한대를 나타내는 값

// 그래프의 정점 수
#define V 5

// 그래프를 표현하기 위한 인접 행렬을 5x5 크기의 2차원 배열로 생성
int G[V][V] = {
  {0, 9, 75, 0, 0},
  {9, 0, 95, 19, 42},
  {75, 95, 0, 51, 66},
  {0, 19, 51, 0, 31},
  {0, 42, 66, 31, 0}};

int main() {
  int no_edge;  // 간선의 수

  // 선택된 정점을 추적하기 위한 배열 생성
  int selected[V];

  // 초기에 모든 정점을 선택되지 않은 상태로 설정
  memset(selected, false, sizeof(selected));

  // 간선의 수를 0으로 설정
  no_edge = 0;

  // 최소 신장 트리의 간선 수는 항상 (V - 1)보다 작거나 같음
  // V는 그래프의 정점 수

  // 0번 정점을 선택하고 true로 설정
  selected[0] = true;

  int x;  // 행 번호
  int y;  // 열 번호

  // 간선과 가중치를 출력
  cout << "Edge"
     << " : "
     << "Weight";
  cout << endl;
  while (no_edge < V - 1) {
    // 선택된 각 정점에 대해 인접한 모든 정점을 찾고,
    // 1단계에서 선택한 정점에서의 거리를 계산
    // 이미 S 집합에 있는 정점이면 그것을 제외하고
    // 1단계에서 선택한 정점에 가장 가까운 다른 정점을 선택

    int min = INF;
    x = 0;
    y = 0;

    for (int i = 0; i < V; i++) {
      if (selected[i]) {
        for (int j = 0; j < V; j++) {
          // 선택되지 않은 상태이며 간선이 있는 경우
          if (!selected[j] && G[i][j]) {  
            if (min > G[i][j]) {
              min = G[i][j];
              x = i;
              y = j;
            }
          }
        }
      }
    }
    cout << x << " - " << y << " :  " << G[x][y];
    cout << endl;
    selected[y] = true;
    no_edge++;
  }

  return 0;
}
