#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
    int max_size;
    int size;
} Stack;

// 스택 초기화 함수
Stack* createStack(int max_size) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    stack->max_size = max_size;
    stack->size = 0;
    return stack;
}

// 데이터를 스택에 추가하는 함수
void push(Stack* stack, char data) {
    if (stack->size == stack->max_size) {
        printf("Stack Overflow\n");
        return;
    }

    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = stack->top;
    stack->top = temp;
    stack->size++;
}

// 스택이 비어있는지 확인하는 함수
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// 스택의 최상단 데이터를 확인하는 함수
char peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        exit(1);
    }
    return stack->top->data;
}

// 스택의 최상단 데이터를 제거하는 함수
void pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return;
    }
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
}

// 스택의 모든 데이터를 출력하는 함수
void display(Stack* stack) {
    Node* temp = stack->top;
    while (temp) {
        printf("%c -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Stack* s = createStack(4);
    push(s, 'a');
    push(s, 'b');
    push(s, 'c');
    push(s, 'd');

    display(s);
    printf("Top element is %c\n", peek(s));

    pop(s);
    pop(s);

    display(s);
    printf("Top element is %c\n", peek(s));

    return 0;
}
