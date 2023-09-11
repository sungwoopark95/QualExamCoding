#include <iostream>
using namespace std;

void max_heapify(int arr[], int n, int i) { // 최대 힙을 만들기 위한 함수
    int largest = i;                     // 현재 노드를 최대 값으로 설정
    int l = 2 * i + 1;                   // 왼쪽 자식 노드의 인덱스 계산
    int r = 2 * i + 2;                   // 오른쪽 자식 노드의 인덱스 계산

    if (l < n && arr[i] < arr[l])        // 왼쪽 자식이 존재하고 현재 노드 값보다 크면
        largest = l;                     // 최대 값 업데이트

    if (r < n && arr[largest] < arr[r])  // 오른쪽 자식이 존재하고 지금까지의 최대 값보다 크면
        largest = r;                     // 최대 값 업데이트

    if (largest != i) {                  // 최대 값이 현재 노드와 다르다면 (swap 필요)
        swap(arr[i], arr[largest]);      // 현재 노드와 최대 값 노드의 위치 교환
        max_heapify(arr, n, largest);    // 재귀적으로 최대 힙 만들기
    }
}

void min_heapify(int arr[], int n, int i) { // 최소 힙을 만들기 위한 함수
    int smallest = i;                    // 현재 노드를 최소 값으로 설정
    int l = 2 * i + 1;                   // 왼쪽 자식 노드의 인덱스 계산
    int r = 2 * i + 2;                   // 오른쪽 자식 노드의 인덱스 계산

    if (l < n && arr[i] > arr[l])        // 왼쪽 자식이 존재하고 현재 노드 값보다 작으면
        smallest = l;                    // 최소 값 업데이트

    if (r < n && arr[smallest] > arr[r]) // 오른쪽 자식이 존재하고 지금까지의 최소 값보다 작으면
        smallest = r;                    // 최소 값 업데이트

    if (smallest != i) {                 // 최소 값이 현재 노드와 다르다면 (swap 필요)
        swap(arr[i], arr[smallest]);     // 현재 노드와 최소 값 노드의 위치 교환
        min_heapify(arr, n, smallest);   // 재귀적으로 최소 힙 만들기
    }
}
