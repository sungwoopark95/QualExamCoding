#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

int* linkedListToList(ListNode* head, int* size) {
    // 결과를 저장할 동적 배열 초기화
    int* result = (int*)malloc(32 * sizeof(int)); // 최대 크기가 32라고 가정
    *size = 0; // 결과 배열의 크기 초기화

    ListNode* current = head;
    while (current) {
        result[(*size)++] = current->val; // 현재 노드의 값을 배열에 추가
        current = current->next;          // 다음 노드로 이동
    }

    return result; // 결과 배열 반환
}
