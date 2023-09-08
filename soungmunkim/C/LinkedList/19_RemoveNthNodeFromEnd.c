/*
[뒤에서 n번째 노드 지우기]
Given the head of a linked list, 
remove the nth node from the end of the list and return its head.


(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test                               
Enter the list of integers in the format [x,y,z,...]: [1,2,3,4,5]
[1, 2, 3, 4, 5]
Enter the integer(nth): 2
[1, 2, 3, 5]
(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % gcc 19_RemoveNthNodeFromEnd.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the list of integers in the format [x,y,z,...]: [1]
[1]
Enter the integer(nth): 1
[]

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the first list: [1,2]
Enter the integer(nth) that you want to remove: 1
[1]
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
    while (node->next) {             // 노드가 NULL이 될 때까지 반복
        printf("%d, ", node->val); // 현재 노드의 값을 출력
        node = node->next;    // 다음 노드로 이동
    }
    printf("%d]\n", node->val); // 줄바꿈 출력
}


ListNode* removeNthFromEnd(ListNode* head, int n) {
    // 더미 노드를 생성하고 초기화한다.
    ListNode* dummy = (ListNode*)malloc(sizeof(ListNode));
    dummy->val = 0;
    dummy->next = head;

    ListNode* front = dummy;
    ListNode* back = dummy;

    // 뒷 포인터를 n개 먼저 움직인다.
    for (int i = 0; i < n; i++) {
        back = back->next;
    }

    // n개 떨어진 앞, 뒤 포인터가 끝까지 순차적으로 간다.
    while (back->next) {
        front = front->next;
        back = back->next;
    }

    // 맨 마지막에 다다르면 앞 포인터의 다음 노드를 뒷 포인터와 연결한다.
    front->next = front->next->next;

    // dummy 노드의 다음 노드를 반환한다.
    ListNode* result = dummy->next;
    free(dummy);
    return result;
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
    
    // 사용자에게 삭제할 nth을 입력받음
    int idx;
    printf("Enter the integer(nth): ");
    scanf("%d", &idx);

    // 연결 리스트 정렬 및 출력
    ListNode* result = removeNthFromEnd(head, idx);
    if(result)
        print_linked_list(result);
    else
        printf("[]\n");

     // 메모리 해제
    while (result) {
        ListNode* temp = result;
        result = result->next;
        free(temp);
    }
    return 0;
}