/*
[list 합치기]
C에서는 nested list 지원이 안 되므로 -> Linked list로 풀기
list1 = [1, 2, 3]
list2 = [1, [2, 3], [[4]]]
list3 = [[[1], 3], [[4, 2], 5], 6, [[7]]]
위와 같은 정수 nested list를 입력으로 받아 저장된 모든 정수를 합쳐서 반환하는 함수

>>> ./SPDSHW1_2_ListAccumulator_SM "[1, 2, 3]"
6
>>> ./SPDSHW1_2_ListAccumulator_SM "[1, [2, 3], [4]]"
10
*/

#include <stdio.h>
#include <stdlib.h>

/*
node type을 나타내기 위한 열거형 (이름만 부여하는 느낌?)
INTEGER는 정수 노드, LIST는 리스트 노드를 나타냄
*/
typedef enum {
    INTEGER,
    LIST
} NodeType;

// nested list의 각 node를 나타내는 구조체 (변수도 가질 수 있는 class같은 느낌?)
typedef struct ListNode {
    NodeType type; // 현재 노드의 유형 정의 (int or list)
    // node가 int 또는 sublist 중 하나를 가질 수 있기 때문에 union을 사용
    union {
        int value; 
        struct ListNode* sublist;
    };
    struct ListNode* next; // next node 가르키는 pointer 설정
} ListNode;

// int type node를 생성하는 함수
ListNode* createIntNode(int value){
    /*
    sizeof(ListNode)는 앞서 정의된 ListNode 구조체의 전체 크기를 바이트로 반환하고,
     이를 malloc에 사용하여 해당 크기만큼의 메모리를 동적으로 할당힘
    */ 
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->type = INTEGER;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// list type node를 생성하는 함수
ListNode* createListNode(ListNode* sublist){
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->type = LIST;
    newNode->sublist = sublist;
    newNode->next = NULL;
    return newNode;
}

// 주어진 list의 끝에 node를 추가하는 함수 (node append인 것!)
// 여기서 Node는 list라서 **이중 pointer 설정함
void appendNode(ListNode** head, ListNode* newNode){
    // 만약 주어진 head가 NULL이라면, list가 비어있다는 것
    if (*head == NULL) 
        *head = newNode;
    else{ // 그렇지 않다면, list 끝을 찾기 위해 반복함
        ListNode* temp = *head;
        while (temp->next) {
            // list 마지막 노드의 next node로 newNode 연결함
            temp = temp->next;
        }
    }
}

// nested list의 모든 값을 더하는 함수
int listAccumulator(ListNode* node) {
    int sum = 0; 
    // 주어진 노드로부터 시작하여 list의 끝까지 반복합니다.
    while (node) {
        // 노드의 타입이 INTEGER라면 그 값을 합계에 더합니다.
        if (node->type == INTEGER) {
            sum += node->value;
        } else {
            // 노드의 타입이 LIST라면, 재귀적으로 sublist의 값을 더합니다.
            sum += listAccumulator(node->sublist);
        }
        // 다음 노드로 이동합니다.
        node = node->next;
    }
    return sum;
}

// nested list의 memory를 해제하는 함수
void freeNestedList(ListNode* head){
    // 주어진 node로부터 시작하여 list의 끝까지 반복
    while (head){
        ListNode* temp = head;
        // node type이 list라면, recursively sublist의 memory 해제
        if (head->type == LIST){
            freeNestedList(head->sublist);
        }
        // next node로 이동
        head = head->next;
        free(temp);
    }
}

// 문자열로부터 nested list를 파싱하는 함수
ListNode* parseNestedList(const char** pStr) {
    // 반환될 리스트의 head를 초기화
    ListNode* head = NULL;
    // 현재 노드의 pointer를 저장하는 변수 (이중 포인터 사용)
    ListNode** current = &head;

    // 문자열의 끝이 아니고 ']' 문자를 만나지 않을 동안 반복
    while (**pStr && **pStr != ']') {
        // '[' 문자를 만나면 sublist 시작
        if (**pStr == '[') {
            (*pStr)++;  // '[' 문자 다음으로 이동
            // 재귀적으로 sublist 파싱
            ListNode* sublist = parseNestedList(pStr);
            // 새로운 리스트 노드 생성
            ListNode* newNode = createListNode(sublist);
            if (*current) {
                (*current)->next = newNode;
                current = &((*current)->next);
            } else {
                *current = newNode;
            }
        } 
        // 숫자 문자를 만나면
        else if ('0' <= **pStr && **pStr <= '9') {
            int value = 0;
            // 숫자 값을 추출
            while ('0' <= **pStr && **pStr <= '9') {
                value = value * 10 + (**pStr - '0');
                (*pStr)++;
            }
            // 새로운 정수 노드 생성
            ListNode* newNode = createIntNode(value);
            if (*current) {
                (*current)->next = newNode;
                current = &((*current)->next);
            } else {
                *current = newNode;
            }
        } 
        // 숫자나 리스트가 아닌 다른 문자를 만나면 무시
        else {
            (*pStr)++;
        }
    }

    // ']' 문자를 만나면 문자열에서 다음 위치로 이동
    if (**pStr == ']') (*pStr)++;
    return head;
}

int main(int argc, char* argv[]) {
    // command line input이 2개가 아니면 (프로그램 이름 + 입력 문자열)
    if (argc != 2) {
        printf("Usage: %s <nested list>\n", argv[0]);
        return 1;
    }

    // 첫 번째 command line input을 입력 문자열로 사용
    const char* input = argv[1];
    // 문자열로부터 nested list를 파싱
    ListNode* head = parseNestedList(&input);

    // nested list의 모든 값을 더함
    int sum = listAccumulator(head);
    printf("%d\n", sum);

    // nested list 메모리 해제
    freeNestedList(head);

    return 0;
}





