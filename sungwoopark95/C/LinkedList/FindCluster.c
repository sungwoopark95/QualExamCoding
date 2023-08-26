#include <stdio.h>
#include <stdlib.h>

/* Linked list node structure */
struct Node {
    int data;
    struct Node* next;
};
 
/* Function to create a new node */
struct Node * createNode(struct Node * newNode, int data){
    newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main(int argc, char* argv[])
{  
    /* length: the length of input arguments (except for inputList.txt) */
    int length = argc - 2;
    /* inputArr: array of input arguments (except for inputList.txt) */
    int * inputArr = (int *) malloc(sizeof(int) * length);
    /* filepath: path for inputList.txt which will be give as a first argument */
    char * filepath = argv[1]; 

    /* Create inputArr */
    for (int i = 0; i < length; ++i){
        inputArr[i] = atoi(argv[i+2]);
    }

    /* Create a linked list from file input */
    int k = 1;
    struct Node* head = NULL;
    struct Node* prev = NULL;
    struct Node* curr = NULL;

    FILE *fp = fopen(filepath, "r");
    char buffer[10]; 

    while (fscanf(fp, "%s", buffer) == 1){
        curr = createNode(curr, atoi(buffer));  
        if (k > 1){
            prev->next = curr;
        }
        else{
            head = curr;
        }
        k++;
        prev = curr;
    }

    fclose(fp);

    /* numConnected: the number of connected "cluster" */
    int numConnected = 0;

    /* * TODO: Your code starts here */	
    /* python
    def P5(head:ListNode, nums:List[int]):
        curr = head
        while curr.val != nums[0]:
            curr = curr.next
        # curr <- 처음으로 일치한 부분
        cnt = 1
        curr = curr.next
        for i in range(1, len(nums)):
            if nums[i] == curr.val:
                curr = curr.next
                continue
            else:
                while curr.val != nums[i] and curr is not None:
                    curr = curr.next
                if curr is not None:
                    cnt += 1
        return cnt
    */
    struct Node* curpoint = head;
    while (curpoint->data != inputArr[0]) {
        curpoint = curpoint->next;
    }
    numConnected++;
    curpoint = curpoint->next;
    for (int i=1;i<length;i++) {
        if (inputArr[i] == curpoint->data) {
            curpoint = curpoint->next;
            continue;
        } else {
            while (curpoint->data != inputArr[i] && curpoint != NULL) {
                curpoint = curpoint->next;
            }
            if (curpoint != NULL) {
                numConnected++;
            }
        }
    }

    /* * Do not modify below */	

    printf("%d", numConnected);

    return 0;
}

