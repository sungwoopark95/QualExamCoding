/*
[linked list cycle 찾기]

Given head, the head of a linked list, 
    determine if the linked list has a cycle in it.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

Return true if there is a cycle in the linked list. Otherwise, return false.

Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, 
    where the tail connects to the 1st node (0-indexed).
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 노드의 구조를 정의한 구조체
typedef struct ListNode {
    int val;                   // 노드의 값을 저장하는 변수
    struct ListNode* next;    // 다음 노드를 가리키는 포인터
} ListNode;

// 방문한 노드들을 저장할 최대 크기
#define MAX_NODES 1000

bool hasCycle(ListNode* head) {
    ListNode* visited_nodes[MAX_NODES];  // 노드들을 저장하기 위한 배열 초기화
    int idx = 0;                         // 방문한 노드의 수를 저장하는 변수

    // 연결 리스트를 순회
    while (head) {
        // 이미 방문한 노드인지 확인
        for (int i = 0; i < idx; i++) {
            // 현재 노드가 방문한 노드 리스트에 있는 경우
            if (visited_nodes[i] == head) {
                return true;  // 사이클이 존재하므로 true 반환
            }
        }
        
        // 현재 노드를 방문한 노드 리스트에 추가
        visited_nodes[idx++] = head;
        
        // 다음 노드로 이동
        head = head->next;
    }
    // 모든 노드를 순회한 후 사이클을 발견하지 못한 경우
    return false;
}

ListNode* create_linked_list_with_cycle(int nums[], int len, int pos) {
    if (len == 0) {
        return NULL;  // 빈 리스트의 경우 NULL 반환
    }

    // 첫 번째 노드 생성
    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    head->val = nums[0];
    head->next = NULL;
    ListNode* node = head;

    // 모든 노드를 저장하기 위한 배열 초기화
    ListNode* nodes[MAX_NODES];
    nodes[0] = head;

    // 두 번째 노드부터 마지막 노드까지 순회하며 연결 리스트 생성
    for (int i = 1; i < len; i++) {
        ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
        new_node->val = nums[i];
        new_node->next = NULL;
        node->next = new_node;  // 이전 노드의 next를 현재 노드로 설정
        nodes[i] = new_node;
        node = new_node;        // 현재 노드 갱신
    }

    // pos 위치의 노드로 마지막 노드의 next 설정하여 사이클 생성
    if (pos != -1) {
        node->next = nodes[pos];
    }

    return head;  // 생성된 연결 리스트의 헤드 노드 반환
}

int main() {
    int test_list[] = {3, 2, 0, -4};  // 테스트용 배열
    int len = sizeof(test_list) / sizeof(test_list[0]);  // 배열의 길이 계산
    int pos = 1;  // 사이클을 생성할 위치
    
    // 테스트용 연결 리스트 생성
    ListNode* test_linked_list = create_linked_list_with_cycle(test_list, len, pos);
    
    // 사이클 유무 확인 후 결과 출력
    printf("%d\n", hasCycle(test_linked_list));  // 사이클이 존재하면 1(True) 출력
    return 0;
}
