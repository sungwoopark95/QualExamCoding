#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;  // Previous (bottom)
    struct Node* right; // Next (top)
} Node;

typedef struct {
    Node* head; // top
    Node* tail; // bottom
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->head = NULL;
    stack->tail = NULL;
    return stack;
}

void push(Stack* stack, int item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->left = NULL;
    newNode->right = stack->head;

    if (stack->head) {
        stack->head->left = newNode;
    }
    stack->head = newNode;

    if (!stack->tail) {
        stack->tail = newNode;
    }
}

int pop(Stack* stack) {
    if (!stack->head) {
        printf("스택이 비어있습니다.\n");
        exit(1);
    }

    Node* target = stack->head;
    int popped_item = target->data;
    stack->head = target->right;
    free(target);

    if (!stack->head) {
        stack->tail = NULL;
    }

    return popped_item;
}

int peek(Stack* stack) {
    if (!stack->head) {
        printf("스택이 비어있습니다.\n");
        exit(1);
    }

    return stack->head->data;
}

int is_empty(Stack* stack) {
    return stack->head == NULL;
}

int main() {
    Stack* s = createStack();
    push(s, 1);
    push(s, 2);
    push(s, 3);
    printf("%d\n", peek(s)); // 3
    printf("%d\n", pop(s));  // 3
    printf("%d\n", pop(s));  // 2
    push(s, 4);
    printf("%d\n", peek(s)); // 4
    printf("%d\n", pop(s));  // 4
    printf("%d\n", pop(s));  // 1

    return 0;
}
