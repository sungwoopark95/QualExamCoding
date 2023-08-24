/*
[reversed linked list]
프로그램의 입력값(Argument)으로 Singly linked list의 각 Data값을 순서대로 입력 받은 뒤, 
순서를 뒤집은 Singly linked list로 만들고 이를 출력하는 함수를 작성하여라.
 (출력 시 node 사이에 공백이나 맨 마지막에 공백, new line 등은 불필요함) 

※ Command line argument 입력 시 각 node는 공백(space)으로 구분된다. 

TestCase1)
>>> ./P1 1 2 3 4 5
54321
*/

#include <stdio.h>
#include <stdlib.h>

// Singly linked list의 Node 구조 정의
typedef struct Node {
    int data;               // 데이터 값
    struct Node* next;      // 다음 Node를 가리키는 포인터
} Node;

// 주어진 데이터로 새 node를 생성하는 함수
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // 새 노드에 대한 메모리 할당
    newNode -> data = data; // newNode에 데이터 설정
    newNode -> next = NULL; // next pointer를 NULL로 설정
    return newNode;         // 새 노드 반환
}

// reverse linked list 만드는 함수
Node* reverseLinkedlist(Node* head){
    Node* prev = NULL; // 이전 pointer를 NULL로 초기화
    Node* curr = head; // head Node에서 시작
    Node* next = NULL; // next pointer 초기화

    while (curr != NULL){
        next = curr->next; // 다음 node 저장
        curr->next = prev; // 방향 반대로
        prev = curr;       // 이전 노드를 현재 노드로 지정
        curr = next;       // 현재 노드를 다음 노드로 지정
    }
    return prev;           // 역순 리스트의 head로 반환
}

int main(int argc, char *argv[]){
    if (argc < 2){
        return 1;
    }
    // 첫번째 input 값으로 node head 생성
    Node* head = createNode(atoi(argv[1])); // char로 받은 숫자를 int 숫자로 바꿔 node 생성
    Node* current = head; // 현재 노드를 head로 설정

    // 나머지 input 값들로 linked list 만들기
    for (int i = 2; i < argc; i++){
        current->next = createNode(atoi(argv[i]));
        current = current->next;
    }

    // linked list 역순으로 만듦
    head = reverseLinkedlist(head);

    // reverse linked list print하기
    current = head;
    while (current != NULL){
        printf("%d", current->data);
        current = current->next;
        if(current != NULL){
            printf(" ");
        }
    }

    // linked list가 차지하는 메모리 해제
    while (head != NULL){
        Node* temp = head;
        head = head->next;
        free(temp);
    }
    return 0;

}