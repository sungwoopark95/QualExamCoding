#include <stdio.h>
#define HEAP_SIZE 256    // 힙의 크기를 256으로 정의합니다.
#define ARRAY_SIZE 10    // 배열의 크기를 10으로 정의합니다.

using namespace std;     // C++의 표준 네임스페이스를 사용합니다.
int heap[HEAP_SIZE];     // 힙으로 사용할 배열을 선언합니다.
int heapCount = 0;       // 현재 힙에 들어있는 원소의 개수를 저장하는 변수입니다.

void swap(int *a, int *b){    // 두 정수를 바꾸는 함수입니다.
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void push(int x){   // 힙에 원소를 삽입하는 함수입니다.
    heap[++heapCount] = x;   // 힙의 마지막 위치에 원소를 삽입합니다.
    
    int child = heapCount;   // 삽입된 원소의 위치입니다.
    int parent = child/2;    // 삽입된 원소의 부모의 위치입니다.
    
    // 원소가 루트가 아니고, 삽입된 원소가 부모보다 클 경우 계속 반복합니다.
    while(child>1 && heap[child]>heap[parent]){
        swap(&heap[child], &heap[parent]);   // 원소와 부모를 바꿉니다.
        child = parent;   // 원소의 위치를 부모로 변경합니다.
        parent = child/2; // 부모의 위치를 업데이트합니다.
    }
}

int pop(){   // 힙에서 원소를 삭제하고 반환하는 함수입니다.
    int ret = heap[1];    // 반환할 원소를 저장합니다. (힙의 최상단 원소)
    
    // 힙의 첫 번째 원소와 마지막 원소를 바꿉니다.
    swap(&heap[1], &heap[heapCount]);
    heapCount = heapCount-1;   // 힙의 크기를 줄입니다.
    
    int parent = 1;       // 시작 위치는 힙의 최상단입니다.
    int child = parent*2; // 현재 위치의 왼쪽 자식입니다.
    
    // 오른쪽 자식이 존재하고, 왼쪽 자식보다 오른쪽 자식이 더 크면 오른쪽 자식을 선택합니다.
    if(child+1 <= heapCount){
        child = (heap[child]>heap[child+1]) ? child : child+1;
    }
    
    // 자식이 부모보다 클 경우 계속 반복합니다.
    while(child<=heapCount && heap[child]>heap[parent]){
        swap(&heap[child], &heap[parent]);  // 부모와 자식을 바꿉니다.
        parent = child;  // 원소의 위치를 자식으로 변경합니다.
        child = parent*2;   // 현재 위치의 왼쪽 자식으로 업데이트합니다.
        
        // 오른쪽 자식이 존재하고, 왼쪽 자식보다 오른쪽 자식이 더 크면 오른쪽 자식을 선택합니다.
        if(child+1 <= heapCount){
            child = (heap[child]>heap[child+1])? child : child+1;
        }
    }
    
    return ret;   // 삭제된 원소를 반환합니다.
}

int main(){   // 메인 함수입니다.
    int a[ARRAY_SIZE] = {5,6,3,7,9,8,1,2,4,10};   // 초기 배열을 선언합니다.
    
    printf("Push : ");
    // 배열의 원소들을 하나씩 힙에 삽입합니다.
    for(int i = 0 ; i<ARRAY_SIZE ; i++){
        printf("%d ", a[i]);
        push(a[i]);
    }
    printf("\n");
    
    printf("Pop : ");
    // 힙에서 원소들을 하나씩 삭제하며 출력합니다.
    for(int i = 0 ; i<ARRAY_SIZE ; i++){
        printf("%d ", pop());
    }
    printf("\n");
    
    return 0;   // 프로그램 종료
}
