#include <stdio.h>
#include <stdlib.h>

typedef int Element;

// 양방향 연결 리스트의 노드 정의
typedef struct node
{
	Element data;        // 노드에 저장될 데이터
	struct node* next;   // 다음 노드를 가리키는 포인터
	struct node* previous;  // 이전 노드를 가리키는 포인터
} Node;

// 연결 리스트 정의
typedef struct list
{
	struct node* head;  // 연결 리스트의 첫 번째 노드
} List;

void add(List** list, int index, Element data);
void addFirst(List** list, Element data);
void addLast(List** list, Element data);
void removeNode(List** list, int index);
void removeAll(List** list);
void reverse(List** list);
int size(List** list);
// order 1이면 내림차순, 0 이면 오름차순
void sort(List* list, int order);
Node* get(List** list, int index);
void printAll(List* list);

void init(List** list, Element data);
Node* moveNode(List** list, int index);  //list의 indexdnlcl node return
Node* makeNode(Element data);
void println();

int main()
{
	List* list = NULL;

	add(&list, 0, 1);
	add(&list, 1, 2);
	add(&list, 2, 3);
	add(&list, 3, 15);
	add(&list, 4, 15);
	addFirst(&list, 1);
	addLast(&list, 5);
	removeNode(&list, 2);
	reverse(&list);
	printAll(list);
	printf("The value of 4th : %d\n", get(&list, 4)->data);
	printf("The size : %d", size(&list));
	removeAll(&list);
}
// 리스트 초기화 함수
void init(List** list, Element data)
{
	if (*list == NULL)
	{
		*list = malloc(sizeof(List));
		(*list)->head = malloc(sizeof(Node));
		(*list)->head->data = data;
		(*list)->head->next = NULL;
		(*list)->head->previous = NULL;
	}
}

// 지정된 위치에 데이터를 추가하는 함수
void add(List** list, int index, Element data)
{
	if (*list == NULL)
	{
		init(list, data);
		return;
	}

	if (index == 0)
	{
		Node* head = (*list)->head;
		Node* newNode = makeNode(data);
		newNode->next = head;
		head->previous = newNode;

		(*list)->head = newNode;
	}
	else
	{
		Node* current = moveNode(list, index - 1);
		Node* newNode = makeNode(data);
		Node* nextNode = current->next;

		newNode->next = nextNode;

		if (nextNode != NULL)
		{
			nextNode->previous = newNode;
		}

		current->next = newNode;
		newNode->previous = current;
	}
}
// 리스트의 맨 앞에 데이터를 추가하는 함수
void addFirst(List** list, Element data)
{
	add(list, 0, data);
}
// 리스트의 맨 끝에 데이터를 추가하는 함수
void addLast(List** list, Element data)
{
	add(list, size(list), data);
}
// 지정된 위치의 노드를 제거하는 함수
void removeNode(List** list, Element index)
{
	Node* previous = moveNode(list, index - 1);
	Node* current = previous->next;

	if (current != NULL)
	{
		previous->next = current->next;
		current->next->previous = previous;

		free(current);
	}
}
// 리스트의 모든 노드를 제거하는 함수
void removeAll(List** list)
{
	Node* movingNode = (*list)->head;
	Node* temp = NULL;
	for (int i = 0; movingNode != NULL; i++)
	{
		temp = movingNode;
		movingNode = movingNode->next;

		if (temp != NULL) free(temp);
	}
}
// 리스트의 순서를 뒤집는 함수
void reverse(List** list)
{
	Node* current = (*list)->head;
	int index = 0;

	for (; current->next != NULL; index++)
	{
		current = current->next;
	}

	int isFirst = 1;
	for (; current != NULL; index--)
	{
		if (isFirst == 1)
		{
			(*list)->head = makeNode(current->data);
			isFirst = 0;
		}
		else
		{
			addLast(list, current->data);
		}

		Node* temp = current;
		current = current->previous;
		free(temp);
	}
}
// 리스트의 크기(노드의 개수)를 반환하는 함수
int size(List** list)
{
	Node* temp = (*list)->head;
	int i = 0;

	for (; temp != NULL; temp = temp->next, i++)
		;

	return i;
}
// 리스트를 정렬하는 함수 (현재 미구현 상태)
void sort(List* list, int order)
{
	List* bucket = NULL;
	init(&bucket, 0);


}
// 지정된 위치의 노드를 반환하는 함수
Node* get(List** list, int index)
{
	Node* temp = (*list)->head;
	int i = 0;

	for (; i < index; temp = temp->next, i++)
		;

	return temp;
}
// 리스트의 모든 노드를 출력하는 함수
void printAll(List* list)
{
	Node* temp = list->head;
	for (int i = 0; temp != NULL; i++)
	{
		printf("[%d] %d \n", i, temp->data);
		temp = temp->next;
	}
}
// 지정된 위치의 노드를 반환하는 함수 (get 함수와 동일한 기능을 수행)
Node* moveNode(List** list, int index)
{
	if ((*list)->head == NULL)
	{
		return NULL;
	}

	if (index == 0)
	{
		return (*list)->head;
	}

	Node* temp = (*list)->head;
	for (int i = 0; i < index; i++)
	{
		temp = temp->next;
	}

	return temp;
}
// 새로운 노드를 생성하는 함수
Node* makeNode(Element data)
{
	Node* newNode = (Node *)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	newNode->previous = NULL;

	return newNode;
}
// 줄바꿈을 위한 함수
void println()
{
	printf("\n");
}