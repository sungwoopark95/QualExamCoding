#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Stack {
    int storage[MAX_SIZE];
    int top;
} Stack;

// 스택 초기화
Stack* createStack() {
    Stack* newStack = (Stack*)malloc(sizeof(Stack));
    newStack->top = -1;
    return newStack;
}

// 스택이 가득 찼는지 확인
int is_full(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

// 스택이 비어 있는지 확인
int is_empty(Stack *stack) {
    return stack->top == -1;
}

// 아이템을 스택에 푸시
void push(Stack *stack, int item) {
    if (is_full(stack)) {
        printf("스택이 가득 찼습니다.\n");
        exit(1);  // or return
    }
    stack->storage[++stack->top] = item;
}

// 스택의 최상단에서 아이템을 팝
int pop(Stack *stack) {
    if (is_empty(stack)) {
        printf("스택이 비어있습니다.\n");
        exit(1);  // or return -1
    }
    return stack->storage[stack->top--];
}

// 스택의 최상단 아이템을 확인
int peek(Stack *stack) {
    if (is_empty(stack)) {
        printf("스택이 비어있습니다.\n");
        exit(1);  // or return -1
    }
    return stack->storage[stack->top];
}

int main() {
    Stack* stack = createStack();

    push(stack, 10);
    push(stack, 20);
    push(stack, 30);

    printf("%d\n", peek(stack));  // 30
    printf("%d\n", pop(stack));   // 30
    printf("%d\n", peek(stack));  // 20

    return 0;
}
