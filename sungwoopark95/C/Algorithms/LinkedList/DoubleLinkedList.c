#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct DLinkedList {
    Node* header;
    Node* trailer;
} DLinkedList;


Node* create_node(const int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

DLinkedList* create_double_linked_list() {
    DLinkedList* newList = (DLinkedList*)malloc(sizeof(DLinkedList));
    newList->header = create_node(0);
    newList->trailer = create_node(0);
    newList->header->next = newList->trailer;
    newList->trailer->prev = newList->header;
    return newList;
}

int isEmpty(DLinkedList* list) {
    return list->header->next == list->trailer;
}

int getFront(DLinkedList* list) {
    return list->header->next->data;
}

int getBack(DLinkedList* list) {
    return list->trailer->prev->data;
}

void add(DLinkedList* list, Node* node, int val) {
    Node* newNode = create_node(val);
    newNode->next = node->next;
    newNode->prev = node;
    node->next->prev = newNode;
    node->next = newNode;
}

void addFront(DLinkedList* list, int val) {
    add(list, list->header, val);
}

void addBack(DLinkedList* list, int val) {
    add(list, list->trailer->prev, val);
}

void removeNode(DLinkedList* list, Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void removeFront(DLinkedList* list) {
    removeNode(list, list->header->next);
}

void removeBack(DLinkedList* list) {
    removeNode(list, list->trailer->prev);
}

void TraverseForward(DLinkedList* list) {
    Node* v = list->header->next;
    int is_first = 1;
    while (v->next != NULL) {
        if (!is_first) { printf(", "); }
        printf("%d", v->data);
        is_first = 0;
        v = v->next;
    }
    printf("\n");
}

void TraverseBackward(DLinkedList* list) {
    Node* v = list->trailer->prev;
    int is_first = 1;
    while (v->prev != NULL) {
        if (!is_first) { printf(", "); }
        printf("%d", v->data);
        is_first = 0;
        v = v->prev;
    }
    printf("\n");
}


int main() {
    DLinkedList* list = create_double_linked_list();

    addFront(list, 3);
    addFront(list, 5);
    addFront(list, 8);
    addFront(list, 10);

    TraverseBackward(list);
    TraverseForward(list);

    removeBack(list);
    removeBack(list);

    TraverseForward(list);
}