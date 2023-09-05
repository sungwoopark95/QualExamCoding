/*
Given the head of a singly linked list, implement the function insertion_sort_list such
that sorts the list using insertion sort, and returns the sorted list's head.

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % gcc 147_InsertionSortList_v2.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test                                
Enter the list of integers in the format [x,y,z,...]: [4,1,3,2]
[4, 1, 3, 2]
[1, 2, 3, 4]
*/

/*
Linked list를 유지해서 푼 버전
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 연결 리스트의 노드 정의
typedef struct ListNode {
    int val;                     // 노드의 값
    struct ListNode *next;      // 다음 노드를 가리키는 포인터
} ListNode;

// 주어진 배열로 연결 리스트를 생성하고 헤드 노드를 반환
ListNode* create_linked_list(int arr[], int n) {
    if (n == 0) return NULL;    // 배열의 크기가 0이면 NULL 반환

    ListNode* start = (ListNode*)malloc(sizeof(ListNode)); // 시작 노드 할당
    start->val = arr[0];       // 첫 번째 값 할당
    start->next = NULL;        // 다음 노드는 NULL로 초기화

    ListNode* node = start;    // 현재 노드를 시작 노드로 설정

    for (int i = 1; i < n; ++i) { // 배열의 나머지 원소들로 연결 리스트 생성
        ListNode* node_new = (ListNode*)malloc(sizeof(ListNode)); // 새 노드 할당
        node_new->val = arr[i];  // 배열의 값 할당
        node_new->next = NULL;   // 다음 노드는 NULL로 초기화

        node->next = node_new;  // 현재 노드의 다음을 새 노드로 연결
        node = node_new;        // 현재 노드를 새 노드로 갱신
    }

    return start; // 연결 리스트의 시작 노드 반환
}

// 연결 리스트의 모든 값을 출력
void print_linked_list(ListNode* node) {
    printf("[");
    while (node->next) {             // 노드가 NULL이 될 때까지 반복
        printf("%d, ", node->val); // 현재 노드의 값을 출력
        node = node->next;    // 다음 노드로 이동
    }
    printf("%d]\n", node->val); // 줄바꿈 출력
}

// 연결 리스트를 오름차순으로 정렬
ListNode* insert_sort_list(ListNode* head) {
    ListNode* dummy = (ListNode*)malloc(sizeof(ListNode)); // 더미 노드 할당
    dummy->next = head;       // 더미 노드의 다음은 헤드 노드로 연결
    ListNode* prev = dummy;   // prev 포인터를 더미 노드로 설정
    ListNode* curr = head;    // curr 포인터를 헤드 노드로 설정

    while (curr) {
        if (curr->next && curr->val > curr->next->val) { // 현재 노드의 값이 다음 노드의 값보다 크다면
            while (prev->next && prev->next->val < curr->next->val) { // 삽입할 위치를 찾기 위해 prev를 이동
                prev = prev->next;
            }

            ListNode* temp = curr->next; // temp는 현재 노드의 다음 노드
            curr->next = temp->next;     // curr의 다음 노드를 temp의 다음 노드로 연결
            temp->next = prev->next;     // temp의 다음 노드를 prev의 다음 노드로 연결
            prev->next = temp;           // prev의 다음 노드를 temp로 연결

            prev = dummy;                // prev를 더미 노드로 재설정
        } else {
            curr = curr->next;           // curr를 다음 노드로 이동
        }
    }

    return dummy->next;                  // 정렬된 연결 리스트의 시작 노드 반환
}

int main() {
    // 사용자에게 숫자 리스트를 입력하라는 메시지를 출력
    printf("Enter the list of integers in the format [x,y,z,...]: ");
    char line[1000]; // 입력 라인의 최대 길이로 가정
    fgets(line, sizeof(line), stdin); // 전체 라인을 읽음

    // \n character을 지우기 
    char *newline = strchr(line, '\n');
    if (newline) {
        *newline = '\0';
    }

    int arr[1000]; // 최대 1000개의 숫자를 가정
    int n = 0;
    char *token = strtok(line, "[], "); // 대괄호, 쉼표, 공백을 기준으로 첫 번째 토큰(숫자)를 얻음
    while (token) {
        arr[n++] = atoi(token); // 토큰을 정수로 변환하여 배열에 추가
        token = strtok(NULL, "[], "); // 다음 토큰을 얻음
    }

    // 연결 리스트 생성 및 출력
    ListNode* head = create_linked_list(arr, n);
    print_linked_list(head);
    
    // 연결 리스트 정렬 및 출력
    ListNode* sorted_head = insert_sort_list(head);
    print_linked_list(sorted_head);

    // 메모리 해제 (간략하게 생략)
    return 0;
}



