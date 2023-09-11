#include <iostream> // C++의 기본 입출력 라이브러리를 포함합니다.

using namespace std; // std 네임스페이스를 사용하여 표준 라이브러리 함수 및 객체에 접근합니다.

#define NIL -1       // NIL을 -1로 정의합니다.
#define MAX 101      // MAX를 101로 정의합니다.

int dist[MAX][MAX]; // 모든 노드 쌍 간의 최단 거리를 저장할 2차원 배열입니다.
int pred[MAX][MAX]; // 최단 경로를 따라 각 노드의 전 노드를 저장할 2차원 배열입니다.

// 플로이드-워셜 알고리즘 함수
void floyd(int n){
    // 중간 노드로서 모든 노드들을 고려합니다.
    for (int mid=1; mid<=n; mid++){
        // 시작 노드로서 모든 노드들을 고려합니다.
        for (int start=1; start<=n; start++){
            // 종료 노드로서 모든 노드들을 고려합니다.
            for (int end=1; end<=n; end++){
                // mid 노드를 거쳐가는 것이 직접 가는 것보다 짧은 경우, 거리를 갱신합니다.
                if (dist[start][end] > dist[start][mid] + dist[mid][end]){
                    dist[start][end] = dist[start][mid] + dist[mid][end];
                    pred[start][end] = pred[mid][end];
                }
            }
        }
    }
}

// i에서 j까지의 최단 경로를 재귀적으로 출력하는 함수
void print_shortest_path(int i, int j){
    if (i == j){
        printf("%d ",i);
    }
    else {
        print_shortest_path(i, pred[i][j]);
        printf("%d ",j);
    }
}

int main(){    
    // n은 노드(정점)의 수입니다.
    cout << "vertex의 개수를 입력하세요:\n";
    int n;
    cin >> n;

    // dist와 pred 배열을 초기화합니다.
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            dist[i][j] = MAX;
            if (i==j) dist[i][j] = 0; // 노드에서 자신까지의 거리는 0입니다.
            pred[i][j] = NIL;         // 초기 전 노드값은 NIL로 설정합니다.
        }
    }
    
    // 사용자로부터 인접 행렬을 입력받습니다.
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            if (i!=j){
                int d;
                cout << i <<"->"<<j<<"의 거리를 입력하세요:";
                cin >> d;
                dist[i][j] = d;      // 입력받은 거리를 dist 배열에 저장합니다.
            }
        }
    }

    // pred 배열을 설정합니다.
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            if (i!=j and dist[i][j]<MAX){
                pred[i][j] = i;      // 시작 노드 i를 전 노드로 설정합니다.
            } 
        }
    }
    
    cout << "초기값\n";  // 초기 인접 행렬과 전 노드 행렬을 출력합니다.
    
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            cout << dist[i][j] << "\t";  // 거리 행렬 출력
        }
        cout << "\n";
    }
    
    cout << "\n";

    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            cout << pred[i][j] << "\t";  // 전 노드 행렬 출력
        }
        cout << "\n";
    }
    
    floyd(n); // 플로이드-워셜 알고리즘을 사용하여 최단 거리를 계산합니다.
    
    cout << "최종값\n";  // 계산된 최단 거리와 전 노드 행렬을 출력합니다.
    
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            cout << dist[i][j] << "\t";
        }
        cout << "\n";
    }
    
    cout << "\n";
    
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            cout << pred[i][j] << "\t";
        }
        cout << "\n";
    }
}
