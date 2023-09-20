#include <stdio.h>
#include <stdlib.h>

typedef struct nodeType LinkedNode;
typedef struct listType SLList;

struct nodeType {
    int val;
    LinkedNode *next;
};

struct listType {
    LinkedNode *first;
    int size;
};

LinkedNode *createNode(int x) {
    LinkedNode *newNode;
    newNode = (LinkedNode *) malloc(sizeof(LinkedNode));
    newNode->val = x;
    newNode->next = NULL;
    return newNode;
}

void addFirst(SLList *LL, int x) {
    LinkedNode *newFirst;
    newFirst = createNode(x);
    newFirst->next = LL->first;
    LL->first = newFirst;
    LL->size++;
}

int getFirst(SLList *LL) {
    if (LL->first != NULL) return LL->first->val;
    return 0;
}

int getSize(SLList *LL) {
    return LL->size;
}

void printSLList(SLList *LL) {
    LinkedNode *curr = LL->first;
    printf("size: %d, firstval: %d, allVals: ", getSize(LL), getFirst(LL));
    while (curr != NULL) {
        printf("%d->", curr->val);
        curr = curr->next;
    }
    printf("END\n");
}

void removeNode(SLList *LL, int x) {
    if (LL->first == NULL) return;
    LinkedNode *curr = LL->first;
    if (curr->val == x) {
        /* Case 1: remove the first node in the list */
        LL->first = curr->next;
        free(curr);
        LL->size--;
        return;
    }
    LinkedNode *prev = curr;
    curr = curr->next;
    while (curr != NULL) {
        /* Case 2: remove the node in the middle of the list */
        if (curr->val == x) {
            prev->next = curr->next;
            free(curr);
            LL->size--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

int main(void) {
    SLList myLL = {NULL, 0};
    printf("Initialize a singly linked list     - ");
    printSLList(&myLL);
    addFirst(&myLL, 10);
    addFirst(&myLL, 9);
    addFirst(&myLL, 8);
    addFirst(&myLL, 7);
    addFirst(&myLL, 6);
    addFirst(&myLL, 5);
    addFirst(&myLL, 4);
    addFirst(&myLL, 3);
    addFirst(&myLL, 2);
    addFirst(&myLL, 1);
    printf("Construct a singly linked list      - ");
    printSLList(&myLL);
    printf("After removing the node with val= 4 - ");
    removeNode(&myLL, 4);
    printSLList(&myLL);
    printf("After removing the node with val= 1 - ");
    removeNode(&myLL, 1);
    printSLList(&myLL);
    printf("After removing the node with val=10 - ");
    removeNode(&myLL, 10);
    printSLList(&myLL);
    printf("After removing the node with val=99 - ");
    removeNode(&myLL, 99);
    printSLList(&myLL);
}