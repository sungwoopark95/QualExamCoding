#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
    Node* current;
    Node* before;
    int len;
} LinkedList;

Node* create_node(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

LinkedList* create_linked_list() {
    LinkedList* newList = (LinkedList*)malloc(sizeof(LinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->current = NULL;
    newList->before = NULL;
    newList->len = 0;
    return newList;
}

void add(LinkedList* list, int val) {
    Node* newNode = create_node(val);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->len++;
}

int first(LinkedList* list) {
    if (list->head == NULL) {
        return -1;
    }
    list->before = list->head;
    list->current = list->head->next;
    return list->before->data;
}

int next(LinkedList* list) {
    if (list->current == NULL) {
        return -1;
    }
    list->before = list->current;
    list->current = list->current->next;
    return list->before->data;
}

int pop(LinkedList* list) {
    if (list->current == NULL) {
        return -1;
    }
    int data = list->current->data;

    if (list->before == list->head) {
        list->head = list->current->next;
        list->before = list->current;
    } else {
        list->before->next = list->current->next;
    }

    if (list->current->next) {
        list->current = list->current->next;
    } else {
        list->tail = list->before;
        list->current = NULL;
    }

    list->len--;

    return data;
}

void removeNode(LinkedList* list) {
    if (list->before == list->head) {
        list->head = list->current->next;
        list->before = list->current;
    } else {
        list->before->next = list->current->next;
    }

    if (list->current->next) {
        list->current = list->current->next;
    } else {
        list->tail = list->before;
        list->current = NULL;
    }

    list->len--; 
}

int getSize(LinkedList* list) {
    return list->len;
}

int isEmpty(LinkedList* list) {
    return list->len == 0;
}

int hasNext(LinkedList* list) {
    return list->current != NULL;
}

void print_list(LinkedList* list) {
    printf("[");
    int data = first(list);
    while(data != -1) {
        printf("%d", data);
        data = next(list);
        if(data != -1) printf(", ");
    }
    printf("]\n");
}

int main() {
    LinkedList* list = create_linked_list();
    add(list, 1);
    add(list, 2);
    add(list, 3);
    add(list, 4);
    add(list, 5);

    printf("Original List: ");
    print_list(list);

    int data = first(list);
    while(data != -1) {
        if(data == 3 || data == 4) {
            printf("Pop: %d\n", pop(list));
        }
        data = next(list);
    }

    printf("After Popping: ");
    print_list(list);

    return 0;
}