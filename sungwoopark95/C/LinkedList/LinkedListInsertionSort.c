#include <stdio.h>      // 표준 입출력 함수를 사용하기 위한 헤더파일
#include <stdlib.h>     // malloc, atoi, exit 함수를 사용하기 위한 헤더파일
#include <string.h>     // strtok 함수를 사용하기 위한 헤더파일

// 연결 리스트의 노드를 표현하는 구조체 정의
typedef struct ListNode {
    int val;                    // 노드의 값
    struct ListNode* next;      // 다음 노드를 가리키는 포인터
} ListNode;

// 두 정수의 값을 교환하는 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 새로운 노드를 생성하고 그 포인터를 반환하는 함수
ListNode* createNode(int val) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));  // 메모리 할당
    if (!newNode) {               // 할당 실패 시
        exit(-1);                 // 프로그램 종료
    }
    newNode->val = val;          // 노드의 값 설정
    newNode->next = NULL;        // 다음 노드 포인터는 NULL로 설정
    return newNode;              // 새 노드 포인터 반환
}

// 주어진 배열을 기반으로 연결 리스트를 생성하는 함수
ListNode* create_linked_list(int* arr, int size) {
    if (size == 0) {             // 배열 크기가 0이면
        return NULL;             // NULL 반환
    }
    ListNode* start = createNode(arr[0]);  // 첫 번째 노드 생성
    ListNode* node = start;     // 작업 노드 설정
    for (int i=1;i<size;i++) {
        ListNode* newNode = createNode(arr[i]);  // 새 노드 생성
        node->next = newNode;   // 작업 노드의 다음 노드를 새 노드로 설정
        node = newNode;         // 작업 노드를 새 노드로 이동
    }
    return start;               // 연결 리스트의 시작 노드 반환
}

// 연결 리스트의 내용을 출력하는 함수
void print_linked_list(ListNode* head) {
    ListNode* curr = head;
    printf("[");
    while (curr->next) {
        printf("%d,", curr->val);   // 노드의 값을 출력
        curr = curr->next;          // 다음 노드로 이동
    }
    printf("%d", curr->val);        // 마지막 노드의 값을 출력
    printf("]\n");
}

// 연결 리스트를 배열로 변환하는 함수
int* LinkedListToList(ListNode* head, int size) {
    int* newArr = (int*)malloc(size * sizeof(int));  // 배열 메모리 할당
    int i = 0;
    ListNode* newCurr = head;
    while (newCurr) {
        newArr[i++] = newCurr->val;  // 배열에 노드의 값을 저장
        newCurr = newCurr->next;     // 다음 노드로 이동
    }
    return newArr;                   // 변환된 배열 반환
}

// 연결 리스트의 내용을 삽입 정렬로 정렬하는 함수
ListNode* insertion_sort_list(ListNode* head) {
    int size = 0;
    ListNode* curr = head;
    // 연결 리스트의 크기를 계산
    while (curr) {
        size++;
        curr = curr->next;
    }
    int* arr = LinkedListToList(head, size);   // 연결 리스트를 배열로 변환
    for (int i=1;i<size;i++) {
        for (int j=i;j>0;j--) {
            if (arr[j-1] > arr[j]) {
                swap(&arr[j-1], &arr[j]);      // 배열 내 원소 교환
            } else {
                break;
            }
        }
    }
    return create_linked_list(arr, size);      // 정렬된 배열을 연결 리스트로 변환
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s [array]\n", argv[0]);
        return 1;
    }

    char* input = argv[1];
    int numbers[100];
    int count = 0;

    char* token = strtok(input, "[,]");
    while (token != NULL) {
        numbers[count] = atoi(token);
        count++;
        token = strtok(NULL, "[,]");
    }

    ListNode* head = create_linked_list(numbers, count);  // 배열을 연결 리스트로 변환
    print_linked_list(head);                              // 연결 리스트 출력
    ListNode* sorted = insertion_sort_list(head);         // 연결 리스트 정렬
    print_linked_list(sorted);                            // 정렬된 연결 리스트 출력

    return 0;
}
