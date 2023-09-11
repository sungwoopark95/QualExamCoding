#include <iostream>  // C++ 표준 입출력 라이브러리 포함

using namespace std;  // 표준 네임스페이스 사용

// ListNode 라는 이름의 구조체 정의
typedef struct ListNode {
	int data;                 // 데이터를 저장할 변수
	struct ListNode* next;    // 다음 노드를 가리키는 포인터
} ListNode;

// 원형 연결 리스트의 길이를 반환하는 함수
int CircularListLength(ListNode* head) {
	int len = 0;             // 길이를 저장할 변수 초기화
	ListNode* current = head;  // 현재 노드를 헤드로 설정
	while (current != NULL) {  // 현재 노드가 NULL이 아닐 때까지 반복
		len++;                // 길이 증가
		current = current->next; // 다음 노드로 이동
	}
	return len;  // 길이 반환
}

// 원형 연결 리스트를 출력하는 함수
void PrintList(ListNode* head) {
	if (head == NULL) {      // 헤드가 NULL인 경우
		cout << "NULL\n";    // NULL 출력 후 반환
		return;
	}
	ListNode* current = head;  // 현재 노드를 헤드로 설정
	do {
		cout << current->data << " -> ";  // 현재 노드의 데이터 출력
		current = current->next;  // 다음 노드로 이동
	} while (current != head);   // 헤드에 도달할 때까지 반복
	cout << "HEAD\n";  // HEAD 출력
}

// 원형 연결 리스트의 시작 위치에 노드를 삽입하는 함수
void InsertAtBegin(ListNode * *head, int data) {
	ListNode* inserted = new ListNode;
	inserted->data = data;
	if (*head == NULL) {
		*head = inserted;
		inserted->next = *head;
	}
	else {
		ListNode* tail = *head;
		while (tail->next != *head) {
			tail = tail->next;
		}
		inserted->next = *head;
		*head = inserted;
		tail->next = *head;
	}
}
// 원형 연결 리스트의 마지막 위치에 노드를 삽입하는 함수
void InsertAtEnd(ListNode * *head, int data) {
	ListNode* inserted = new ListNode;
	inserted->data = data;
	if (*head == NULL) {
		*head = inserted;
		inserted->next = *head;
	}
	else {
		ListNode* tail = *head;
		while (tail->next != *head) {
			tail = tail->next;
		}
		tail->next = inserted;
		inserted->next = *head;
	}
}

// 원형 연결 리스트의 첫 노드를 삭제하는 함수
void DeleteFrontNode(ListNode * *head) {
	ListNode* removed = *head;
	if (*head == NULL) {
		return;
	}
	else {
		ListNode* tail = *head;
		while (tail->next != *head) {
			tail = tail->next;
		}
		if (tail == *head) {
			*head = NULL;
		}
		else {
			(*head) = (*head)->next;
			tail->next = *head;
		}
		delete(removed);
	}
}
// 원형 연결 리스트의 마지막 노드를 삭제하는 함수
void DeleteLastNode(ListNode * *head) {
	if (*head == NULL) {
		return;
	}
	else {
		ListNode* tail = *head;
		ListNode* tail_prev = NULL;
		
		while (tail->next != *head) { // tail node까지 가기.
			tail_prev = tail;
			tail = tail->next;
		}
		ListNode* removed = tail;
		if (tail == *head) {
			*head = NULL;
		}
		else {
			tail_prev->next = *head;  // 삭제된 노드 이전 노드와 head 연결
		}
		delete(removed);
	}
}

ListNode* head = NULL; // 원형 연결 리스트의 헤드를 NULL로 초기화

int main()
{
	InsertAtBegin(&head, 4);
	PrintList(head);
	InsertAtBegin(&head, 17);
	PrintList(head);
	InsertAtBegin(&head, 1);
	PrintList(head);
	InsertAtBegin(&head, 5);
	PrintList(head);

	InsertAtEnd(&head, 12);
	PrintList(head);
	InsertAtEnd(&head, 13);
	PrintList(head);
	InsertAtEnd(&head, 19);
	PrintList(head);
	InsertAtEnd(&head, 20);
	PrintList(head);

	DeleteFrontNode(&head);
	PrintList(head);
	DeleteFrontNode(&head);
	PrintList(head);
	DeleteFrontNode(&head);
	PrintList(head);
	DeleteFrontNode(&head);
	PrintList(head);

	DeleteLastNode(&head);
	PrintList(head);
	DeleteLastNode(&head);
	PrintList(head);
	DeleteLastNode(&head);
	PrintList(head);
	DeleteLastNode(&head);
	PrintList(head);
}


/*
# 실행 결과
4 -> HEAD
17 -> 4 -> HEAD
1 -> 17 -> 4 -> HEAD
5 -> 1 -> 17 -> 4 -> HEAD
5 -> 1 -> 17 -> 4 -> 12 -> HEAD
5 -> 1 -> 17 -> 4 -> 12 -> 13 -> HEAD
5 -> 1 -> 17 -> 4 -> 12 -> 13 -> 19 -> HEAD
5 -> 1 -> 17 -> 4 -> 12 -> 13 -> 19 -> 20 -> HEAD
1 -> 17 -> 4 -> 12 -> 13 -> 19 -> 20 -> HEAD
17 -> 4 -> 12 -> 13 -> 19 -> 20 -> HEAD
4 -> 12 -> 13 -> 19 -> 20 -> HEAD
12 -> 13 -> 19 -> 20 -> HEAD
12 -> 13 -> 19 -> HEAD
12 -> 13 -> HEAD
12 -> HEAD
NULL
*/