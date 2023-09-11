
#include<iostream>
#include<queue>
#include<list>   // list 헤더 포함
#include<vector> // vector 헤더 포함
using namespace std;

class graph{ // 그래프 클래스 정의
  int vertices; // 정점의 수
  list<int> *adjecentList; // 인접 리스트 배열 포인터
public:
  graph(int vertices){ // 생성자 정의
    this->vertices = vertices; // 정점 수 초기화
    adjecentList = new list<int>[vertices]; // 인접 리스트 동적 할당
  }
  void createEdge(int u, int v){ // 간선 생성 함수
    adjecentList[u].push_back(v); // u의 인접 리스트에 v 추가
  }
  void TopologicalSort(){ // 위상 정렬 함수
    // filling the vector with zero initially
    vector<int> indegree_count(vertices,0); // 모든 정점의 진입차수를 0으로 초기화

    for(int i=0;i<vertices;i++){ // 각 정점에 대하여
      list<int>::iterator itr;
      for(itr=adjecentList[i].begin(); itr!=adjecentList[i].end();itr++){ // 해당 정점의 인접 리스트 순회
        indegree_count[*itr]++; // 진입차수 카운트 증가
      }
    }
    queue<int> Q; // 정점을 저장할 큐
    for(int i=0; i<vertices;i++){
      if(indegree_count[i]==0){ // 진입차수가 0인 정점을 큐에 넣는다.
        Q.push(i);
      }
    }
    int visited_node = 0; // 방문한 정점 수
    vector<int> order; // 위상 순서를 저장할 벡터
    while(!Q.empty()){ // 큐가 비어있지 않으면 반복
      int u = Q.front(); // 큐의 첫 번째 요소 추출
      Q.pop(); 
      order.push_back(u); // 결과 벡터에 추가

      list<int>::iterator itr;
      for(itr=adjecentList[u].begin(); itr!=adjecentList[u].end();itr++){ // u의 인접 리스트 순회
        if(--indegree_count[*itr]==0){ // 진입차수 감소 후 0이면
          Q.push(*itr); // 큐에 추가
        }
      }
      visited_node++; // 방문한 정점 수 증가
    }
    if(visited_node!=vertices){ // 모든 정점을 방문하지 않은 경우
      cout<<"There's a cycle present in the Graph.\nGiven graph is not DAG"<<endl; // DAG가 아니라는 메시지 출력
      return;
    }
    for(int i=0; i<order.size();i++){ // 결과 벡터 출력
      cout<<order[i]<<"\t";
    }
  }
};

int main(){ // 메인 함수
  graph G(6); // 6개의 정점으로 그래프 생성
  G.createEdge(0,1); // 간선 추가
  G.createEdge(0,2);
  G.createEdge(1,3);
  G.createEdge(1,5);
  G.createEdge(2,3);
  G.createEdge(2,5);
  G.createEdge(3,4);
  G.createEdge(5,4);
  G.TopologicalSort(); // 위상 정렬 실행
}
