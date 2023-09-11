#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

typedef struct LinkedList {
    Node* head;
} LinkedList;

LinkedList* create_linked_list() {
    LinkedList* newList = (LinkedList*)malloc(sizeof(LinkedList));
    newList->head = NULL;
    return newList;
}

void append(LinkedList* list, int val) {
    if (list->head == NULL) {
        list->head = create_node(val);
        return;
    }
    Node* current = list->head;
    while (current->next) {
        current = current->next;
    }
    current->next = create_node(val);
}

void removeNode(LinkedList* list, int val) {
    if (list->head == NULL) { return; }
    if (list->head->data == val) {
        list->head = list->head->next;
        return;
    }
    Node* current = list->head;
    while (current->next && current->next->data != val) {
        current = current->next;
    }
    // 삭제할 node를 찾았을 때
    if (current->next == NULL) {
        return;
    }
    current->next = current->next->next;
}

void insert(LinkedList* list, int index, int val) {
    if (index == 0) {
        Node* newNode = create_node(val);
        newNode->next = list->head;
        list->head = newNode;
        return;
    }
    Node* current = list->head;
    for (int i=0;i<index-1;i++) {
        if (current == NULL) { return; }
        current = current->next;
    }
    Node* newNode = create_node(val);
    newNode->next = current->next;
    current->next = newNode;
}

void sort(LinkedList* list) {
    if (list->head == NULL || list->head->next == NULL) { return; }
    Node* node = list->head;
    while (node != NULL) {
        Node* next = node->next;
        while (next != NULL) {
            if (node->data > next->data) {
                swap(&(node->data), &(next->data));
            }
            next = next->next;
        }
        node = node->next;
    }
}

void display(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int len(LinkedList* list) {
    int length = 0;
    Node* curr = list->head;
    while (curr != NULL) {
        length++;
        curr = curr->next;
    }
    return length;
}

void reverse_display(LinkedList* list, Node* start) {
    if (start == NULL) { 
        printf("\n");
        return; 
    }
    reverse_display(list, start->next);
    printf("%d ", start->data);
}

void reverse(LinkedList* list) {
    Node* prev = NULL;
    Node* curr = list->head;
    while (curr != NULL) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list->head = prev;
}

void clear(LinkedList* list) {
    list->head = NULL;
}

int main() {
    LinkedList* list = create_linked_list();
    append(list, 2);
    append(list, 1);
    append(list, 20);
    append(list, 32);
    append(list, 12);
    append(list, 26);
    append(list, 8);
    append(list, 7);

    display(list);

    insert(list, 1, 66);
    display(list);

    removeNode(list, 20);
    display(list);

    sort(list);
    display(list);

    printf("Length : %d\n", len(list));
    printf("Reverse display : ");
    reverse_display(list, list->head);

    reverse(list);
    display(list);
}