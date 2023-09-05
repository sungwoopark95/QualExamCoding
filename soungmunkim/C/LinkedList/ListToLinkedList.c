#include <stdio.h>
#include <stdlib.h> // 메모리 동적 할당을 위한 헤더파일

// ListNode라는 구조체 타입 정의
typedef struct ListNode {
    int val;                       // 노드에 저장될 값
    struct ListNode* next;         // 다음 노드를 가리키는 포인터
} ListNode;

// 주어진 배열을 연결 리스트로 변환하는 함수
ListNode* listToLinkedList(int* arr, int size) {
    // 배열이 NULL이거나 크기가 0인 경우 NULL 반환
    if (!arr || size == 0) {
        return NULL;
    }

    // 머리 노드를 위한 메모리 동적 할당
    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    head->val = arr[0];            // 배열의 첫 번째 값을 머리 노드에 저장
    head->next = NULL;             // 머리 노드의 다음 포인터를 NULL로 초기화

    ListNode* current = head;      // 현재 노드를 머리 노드로 설정

    // 배열의 나머지 요소를 순회하며 연결 리스트의 노드 생성
    for (int i = 1; i < size; i++) {
        current->next = (ListNode*)malloc(sizeof(ListNode));  // 새 노드를 위한 메모리 할당
        current = current->next;    // 현재 노드를 새로 생성된 노드로 업데이트
        current->val = arr[i];     // 새 노드에 배열의 값을 저장
        current->next = NULL;      // 새 노드의 다음 포인터를 NULL로 초기화
    }

    return head;                    // 연결 리스트의 머리 노드 반환
}
