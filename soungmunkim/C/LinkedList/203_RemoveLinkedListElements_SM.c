/*
[Remove linked list elements]
Given the head of a linked list and an integer val, 
    remove all the nodes of the linked list that has Node.val == val, 
    and return the new head.
    
(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % g++ -std=c++17 203_RemoveLinkedListElements_SM.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the list of integers separated by spaces and value: [7,7,7,7]
Enter the value you want to delete: 7
[]

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the list of integers separated by spaces and value: [1,2,3,4,6,5,6]
Enter the value you want to delete: 6
[1, 2, 3, 4, 5]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 단일 연결 리스트의 노드를 위한 정의
typedef struct ListNode {
    int val;                // 노드의 값
    struct ListNode *next;  // 다음 노드를 가리키는 포인터
} ListNode;

// 리스트로부터 연결 리스트를 생성한 후 헤드 노드를 반환
ListNode* create_linked_list(int* arr, int n) {
    if (n == 0) {
        return NULL;       // 입력된 배열의 길이가 0인 경우 NULL 반환
    }

    ListNode* start = (ListNode*)malloc(sizeof(ListNode));  // 시작 노드 동적 할당
    start->val = arr[0];                         // 시작 노드의 값 설정
    start->next = NULL;                          // 시작 노드의 다음을 NULL로 설정

    ListNode* node = start;                      // 현재 노드를 시작 노드로 설정

    for (int i = 1; i < n; i++) {
        ListNode* node_new = (ListNode*)malloc(sizeof(ListNode)); // 새 노드 동적 할당
        node_new->val = arr[i];                         // 새 노드의 값 설정
        node_new->next = NULL;                          // 새 노드의 다음을 NULL로 설정

        node->next = node_new;    // 현재 노드의 다음을 새 노드로 연결
        node = node_new;          // 현재 노드를 새 노드로 갱신
    }

    return start;   // 연결 리스트의 시작 노드 반환
}

// 연결 리스트 출력 
void print_linked_list(ListNode* node) {
    printf("[");
    while (node) {             // 노드가 NULL이 될 때까지 반복
        printf("%d", node->val); // 현재 노드의 값을 출력
        if (node->next) printf(", ");
        node = node->next;    // 다음 노드로 이동
    }
    printf("]\n"); // 줄바꿈 출력
}

// 연결 리스트의 연속된 두 노드를 교환
ListNode* removeElements(ListNode* head, int val) {


    if (head == NULL) {
        return NULL;  // 헤드 노드가 없는 경우 NULL 반환
    }

    ListNode* dummy = (ListNode*)malloc(sizeof(ListNode));  // 더미 노드 동적 할당
    dummy->next = head;                          // 더미의 다음 노드를 헤드로 설정
    ListNode* prev = dummy;                      // prev 포인터를 더미 노드로 설정
    ListNode* curr = dummy;                       // curr 포인터를 dummy 노드로 설정

    while (curr->next != NULL) {
        // 현재 노드의 다음 노드의 값이 삭제 대상 값과 동일한 경우
        if(curr->next->val == val){
            // 현재 노드의 next를 그 다음 노드로 갱신
            curr->next = curr->next->next;
        }
        else {
            // 그렇지 않으면 현재 노드를 다음 노드로 이동
            curr = curr->next;
        }
    }
    ListNode* result = dummy->next;  // 결과 헤드 노드 설정
    free(dummy);                     // 더미 노드 메모리 해제
    return result;                   // 결과 헤드 노드 반환
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

    // 사용자에게 삭제할 값을 입력받음
    int val;
    printf("Enter the integer value to be removed from the list: ");
    scanf("%d", &val);
    
    // 연결 리스트에서 해당 값을 제거 및 출력
    ListNode* updated_head = removeElements(head, val);
    print_linked_list(updated_head);

    // 메모리 해제 (간략하게 생략)
    return 0;
}