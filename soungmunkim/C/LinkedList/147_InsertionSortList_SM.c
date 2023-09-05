#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 정의: 단일 연결 리스트의 노드
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

// 리스트로부터 연결 리스트를 생성하고 head 노드를 반환
ListNode* create_linked_list(int* arr, int size) {
    if(size == 0) return NULL;
    
    ListNode* start = malloc(sizeof(ListNode));
    start->val = arr[0];
    start->next = NULL;
    ListNode* node = start;

    for(int i = 1; i < size; i++) {
        ListNode* node_new = malloc(sizeof(ListNode));
        node_new->val = arr[i];
        node_new->next = NULL;
        node->next = node_new;
        node = node_new;
    }

    return start;
}

// 연결 리스트의 모든 값을 출력
void print_linked_list(ListNode* head) {
    printf("[");
    while(head != NULL) {
        printf("%d", head->val);
        head = head->next;
        if(head != NULL) printf(", ");
    }
    printf("]\n");
}

// Helper: 배열을 연결 리스트로 변환
ListNode* arrayToLinkedList(int* arr, int size) {
    if(size == 0) return NULL;

    ListNode* head = malloc(sizeof(ListNode));
    head->val = arr[0];
    head->next = NULL;
    ListNode* current = head;

    for(int i = 1; i < size; i++) {
        current->next = malloc(sizeof(ListNode));
        current->next->val = arr[i];
        current->next->next = NULL;
        current = current->next;
    }

    return head;
}

// 연결 리스트 정렬
ListNode* insertion_sort_list(int* arr, int size) {
    for(int i = 1; i < size; i++) {
        for(int j = i; j > 0; j--) {
            if(arr[j-1] > arr[j]) {
                int temp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = temp;
            } else {
                break;
            }
        }
    }

    return arrayToLinkedList(arr, size);
}

int main() {
    char input[100];
    printf("Enter the numbers in list format (e.g. [2,1,4,3]): ");
    fgets(input, sizeof(input), stdin);

    int arr[100];
    int size = 0;

    char* token = strtok(input, "[], ");
    while(token != NULL) {
        sscanf(token, "%d", &arr[size]);
        size++;
        token = strtok(NULL, "[], ");
    }

    ListNode* sorted = insertion_sort_list(arr, size);
    print_linked_list(sorted);

    return 0;
}
