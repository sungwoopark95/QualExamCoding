#include <stdio.h>
#include <stdlib.h>

// Define the stack structure
typedef struct {
    int* array;      // Array to store stack elements
    int capacity;    // Maximum capacity of the stack
    int top;         // Index of the current top element in the stack
} Stack;

// Stack initialization function
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    stack->array = (int*)malloc(capacity * sizeof(int));
    if (stack->array == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    stack->capacity = capacity;
    stack->top = -1; // Initialize to -1 to indicate an empty stack

    return stack;
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return (stack->top == -1);
}

// Function to check if the stack is full
int isFull(Stack* stack) {
    return (stack->top == stack->capacity - 1);
}

// Function to add an element to the stack (push)
void push(Stack* stack, int data) {
    if (isFull(stack)) {
        fprintf(stderr, "Stack is full.\n");
        return;
    }

    stack->array[++stack->top] = data;
}

// Function to remove and return an element from the stack (pop)
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    return stack->array[stack->top--];
}

// Function to return the top element of the stack (peek)
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    return stack->array[stack->top];
}

// Function to print the stack elements (for debugging)
void printStack(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}

// Function to free the memory allocated for the stack
void freeStack(Stack* stack) {
    free(stack->array);
    free(stack);
}

int main() {
    Stack* stack = createStack(5);

    push(stack, 1);
    push(stack, 2);
    push(stack, 3);

    printf("Top element of the stack: %d\n", peek(stack));

    printf("Stack: ");
    printStack(stack);

    pop(stack);
    printf("Stack after removing an element: ");
    printStack(stack);

    freeStack(stack);

    return 0;
}
