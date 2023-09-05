#include <iostream>

using namespace std;

typedef struct ListNode {
	int data;
	struct ListNode* next;
} ListNode;

int CircularListLength(ListNode* head) {
	int len = 0;
	ListNode* current = head;
	while (current != NULL)
	{
		len++;
		current = current->next;
	}
	return len;
}

void PrintList(ListNode* head) {
	if (head == NULL) {
		cout << "NULL\n";
		return;
	}
	ListNode* current = head;
	do {
		cout << current->data << " -> ";
		current = current->next;
	} while (current != head);
	cout << "HEAD\n";
}

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

ListNode* head = NULL;

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