#include <stdio.h>
#include <stdlib.h>

//NODE에 대한 정의부터
typedef struct nodeType LinkedNode;

struct nodeType{
    int val;
    LinkedNode *next;
};

LinkedNode *createNode(int x){
    LinkedNode *newNode;
    newNode = (LinkedNode *) malloc(sizeof(LinkedNode));
    newNode->val=x;
    newNode->next=NULL;
    return newNode;
}

//SL-list 정의
typedef struct listType SLList;
struct listType{
    LinkedNode *first;
    int size;
};

void addFirst(SLList* sl, int x) {
    LinkedNode *newNode = createNode(x);
    newNode->next = sl->first;
    sl->first=newNode;
    sl->size++;
    printf("New node is added as a first element with value (%d). Now the size is (%d)\n", x, sl->size);
}

LinkedNode* getFirst(SLList* sl){
    if (sl->first!=NULL) {
        return sl->first;
    }
    return NULL;
}

int getSize(SLList* sl){
    // printf("getSize called. Size is (%d).", sl->size);
    return sl->size;
}

void printSLList(SLList* sl){
    LinkedNode* currentNode=sl->first;
    printf("size: %d, firstVal : %d, allVals : ", getSize(sl), getFirst(sl)->val);
    while (currentNode) {
        if (currentNode->next !=NULL){
            printf("%d->", currentNode->val);
        }
        else {
            printf("%d. End.\n", currentNode->val);
        }
        currentNode=currentNode->next;
    }
}

int main(void){
    SLList myLL = {NULL, 0};
    addFirst(&myLL, 10);
    printf("%d\n", getFirst(&myLL)->val);
    getSize(&myLL);
    printSLList(&myLL);

    addFirst(&myLL, 5);
    printf("%d\n", getFirst(&myLL)->val);
    getSize(&myLL);

    printSLList(&myLL);

   
}