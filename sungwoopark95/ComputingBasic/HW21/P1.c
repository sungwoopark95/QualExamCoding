/*
프로그램의 입력값(Argument)으로 Singly linked list의 각 Data값을 순서대로 입력 받은 뒤, 순서를 뒤집은 Singly linked list로 만들고 이를 출력하는 함수를 작성하여라. 
(출력 시 node 사이에 공백이나 맨 마지막에 공백, new line 등은 불필요함) 

Python의 reverse_linked_list
def reverse_linked_list(head:ListNode):
    if head is None:
        return None

    prev = head
    curr = head.next
    head.next = None
    while curr:
        curr_next = curr.next
        curr.next = prev
        prev = curr
        curr = curr_next
    return prev
*/

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

/* Function to reverse the linked list */
struct Node* reverse_linked_list(struct Node* head) {
    struct Node* prev = head;
    struct Node* curr = head->next;
    head->next = NULL;
    while (curr) {
        struct Node* curr_next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = curr_next;
    }
    return prev;
}

int main(int argc, char* argv[]) {  
    int length = argc - 1;

    /* Create a linked list from input integers */
    int k = 1;
    struct Node * head = NULL;
    struct Node * prev = NULL;
    struct Node * curr = NULL;

/*
addNode는 실제로 함수가 아닙니다. 
코드에서 addNode는 레이블(label)로 사용되었고, goto 문을 사용하여 해당 레이블 위치로 점프하는 데 사용됩니다.

goto와 레이블을 사용하여 반복 작업을 수행하는 대신, 일반적인 반복문(예: while 또는 for 문)을 사용하여 동일한 작업을 수행할 수 있습니다. 
goto는 코드의 흐름을 추적하기 어렵게 만들 수 있기 때문에, 일반적으로는 goto를 피하고 대신 반복문이나 함수를 사용하는 것이 좋습니다.

int k = 1;
struct Node * head = NULL;
struct Node * prev = NULL;
struct Node * curr = NULL;

while (k <= length) {
    curr = createNode(curr, atoi(argv[k]));  
    
    if (k > 1)
        prev->next = curr;
    else
        head = curr;

    k++;
    prev = curr;
}
*/
addNode: 
    curr = createNode(curr, atoi(argv[k]));  
    
    if (k > 1)
        prev->next = curr;
    else
        head = curr;

    k++;
    prev = curr;

    // If there are more nodes left, go back to 'addNode' and execute the codes below again
    if (k <= length)
        goto addNode;

    /* * TODO: Your code starts here */
    head = reverse_linked_list(head);
    /* * Do not modify below  */	

    /* Pinrt reversed linked list */
    curr = head;

    while (curr){
        printf("%d", curr->data);
        curr = curr->next;
    }

  return 0;
}
