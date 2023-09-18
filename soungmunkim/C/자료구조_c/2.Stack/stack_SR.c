#include <stdio.h>
#include <stdlib.h>

// 기본 데이터 타입으로 int를 정의합니다.
typedef int element;

// 노드 구조체를 정의합니다. 데이터와 다음 노드를 가리키는 링크로 구성됩니다.
typedef struct node{
	element data;
	struct node* link;
} Node;

// 스택 구조체를 정의합니다. 맨 위 노드를 가리키는 탑으로 구성됩니다.
typedef struct stack
{
	Node* top;
} Stack;

Stack* createStack();                  // 스택을 생성합니다.
void push(Stack** stack, element data); // 스택에 데이터를 추가합니다.
element pop(Stack** stack);             // 스택의 맨 위 데이터를 제거하고 반환합니다.
element pick(Stack** stack);            // 스택의 맨 위 데이터를 반환합니다.
int isEmpty(Stack** stack);             // 스택이 비어있는지 확인합니다.
void printStack(Stack** stack);         // 스택에 있는 모든 데이터를 출력합니다.

int main(void)
{
	Stack* stack = createStack();   // 스택을 생성합니다.

	int data = 31;
	printf("PUSH %d\n", data);     // 데이터를 푸시하고 출력합니다.
	push(&stack, 31);

	data = 27;
	printf("PUSH %d\n", data);
	push(&stack, data);

	data = 61;
	printf("PUSH %d\n", data);
	push(&stack, data);

	data = 90;
	printf("PUSH %d\n", data);
	push(&stack, data);
	
	printf("POP : %d\n", pop(&stack));  // 데이터를 팝하고 출력합니다.
	printf("POP : %d\n", pop(&stack));

	printf("PICK : %d\n", pick(&stack)); // 맨 위 데이터를 피크하고 출력합니다.

	printStack(&stack);                  // 스택에 있는 모든 데이터를 출력합니다.

	return 0;
}

Stack* createStack()
{
	Stack* stack = malloc(sizeof(Stack)); // 스택의 메모리를 할당받습니다.
	stack->top = NULL;                     // 초기 상태에서는 탑이 NULL입니다.

	return stack;                         // 생성된 스택을 반환합니다.
}

void push(Stack** input_stack, element data)
{
	if ((*input_stack) == NULL)           // 스택이 NULL이면 에러 메시지를 출력하고 종료합니다.
	{
		printf("Stack is null");
		exit(1);
	}

	Node* newNode = malloc(sizeof(Node)); // 새 노드의 메모리를 할당받습니다.
	newNode->data = data;                 // 새 노드의 데이터를 설정합니다.
	newNode->link = (*input_stack)->top;  // 새 노드의 링크는 현재 탑을 가리킵니다.
	(*input_stack)->top = newNode;        // 탑을 새 노드로 설정합니다.
}

element pop(Stack** input_stack)
{
	if (isEmpty(input_stack) == 1)        // 스택이 비어있으면 종료합니다.
	{
		exit(1);
	}

	const int return_data = (*input_stack)->top->data; // 반환할 데이터를 저장합니다.
	Node* temp = (*input_stack)->top->link;            // 임시 노드에 다음 노드를 저장합니다.

	free((*input_stack)->top);             // 현재 탑 노드의 메모리를 해제합니다.
	(*input_stack)->top = temp;           // 탑을 다음 노드로 설정합니다.

	return return_data;                   // 데이터를 반환합니다.
}

void printStack(Stack** input_stack)
{
	if(isEmpty(input_stack) == 1)          // 스택이 비어있으면 종료합니다.
	{
		exit(1);
	}

	Node* temp = (*input_stack)->top;     // 현재 탑부터 시작합니다.
	while (temp != NULL)                  // 노드가 NULL이 아닐 때까지 반복합니다.
	{
		printf("%d->", temp->data);       // 데이터를 출력합니다.
		temp = temp->link;                // 다음 노드로 이동합니다.
	}
}

element pick(Stack** input_stack)
{
	if(isEmpty(input_stack) == 0)         // 스택이 비어있지 않으면
	{
		return (*input_stack)->top->data; // 맨 위 데이터를 반환합니다.
	}

	exit(1);                             // 스택이 비어있으면 종료합니다.
}

int isEmpty(Stack** input_stack)
{
	if ((*input_stack) == NULL)           // 스택 자체가 NULL이면
	{
		printf("Stack is null");          // 에러 메시지를 출력하고
		return 1;                         // 1을 반환합니다.
	}

	if ((*input_stack)->top == NULL)      // 스택의 탑이 NULL이면 (데이터가 없으면)
	{
		printf("Stack is empty");         // 에러 메시지를 출력하고
		return 1;                         // 1을 반환합니다.
	}

	return 0;                             // 스택에 데이터가 있으면 0을 반환합니다.
}
