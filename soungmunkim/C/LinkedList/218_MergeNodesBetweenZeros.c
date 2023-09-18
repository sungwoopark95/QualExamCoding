/*
[0 사이의 숫자 합들을 리스트로 반환하기]

You are given the head of a linked list, 
    which contains a series of integers separated by 0's. 
    
The beginning and end of the linked list will have Node.val == 0.

For every two consecutive 0's, 
    merge all the nodes lying in between them into a single node 
    whose value is the sum of all the merged nodes. 

The modified list should not contain any 0's.

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % gcc 218_MergeNodesBetweenZeros.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test                                  
Enter the list of integers in the format [x,y,z,...]: [0,3,1,0,4,5,2,0]
[4, 11]

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the list of integers in the format [x,y,z,...]: [0,1,0,3,0,2,2,0]
[1, 3, 4]
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

void mergeNodes(ListNode* head){
    int ans[1000];
    int idx = 0;
    int sum = 0;

    ListNode* curr = head;
    ListNode* next = NULL;

    while(curr->next){
        next = curr->next;
        curr = next;

        if(curr->val !=0){
            sum += curr->val;
        }else{
            ans[idx++] = sum;
            sum = 0;
        }
    }
    printf("[");
    for(int i=0; i<idx; i++){
        printf("%d", ans[i]);
        if(i != idx-1)
            printf(", ");
    }
    printf("]\n");
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
    // print_linked_list(head);


    mergeNodes(head);

    // 메모리 해제 (간략하게 생략)
    return 0;
}