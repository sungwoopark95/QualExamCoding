#include <stdio.h> //printf, scanf
#include <stdlib.h> //malloc
#include <stdbool.h> //bool

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

void init_node(Node* node, int x){
    node->val = x;
    node->left = NULL;
    node->right = NULL;
}

typedef struct Tree{
    Node* root;
} Tree;

void init_tree(Tree* tree){
    tree->root = NULL;
}


/*Queue for BFS (14번 파일)*/
    // Single Linked List 노드 구조체 정의
    typedef struct SLNode {
        Node* data;
        struct SLNode* next;
    } SLNode;

    void init_SLNode(SLNode* node){
        node->data = NULL;
        node->next = NULL;
    }

    // Queue 구조체 정의
    typedef struct Queue {
        SLNode* front; // 큐의 맨 앞 요소
        SLNode* rear;  // 큐의 맨 뒤 요소
    } Queue;

    // 큐 초기화 함수
    void initializeQueue(Queue* queue) {
        queue->front = NULL;
        queue->rear = NULL;
    }

    // 큐가 비어있는지 확인하는 함수
    int isEmpty(Queue* queue) {
        return (queue->front == NULL);
    }

    // 큐에 요소 추가 (enqueue)
    void enqueue(Queue* queue, Node* data) {
        // 새로운 노드 생성
        SLNode* newNode = (SLNode*)malloc(sizeof(SLNode));
        if (newNode == NULL) {
            fprintf(stderr, "메모리 할당 오류\n");
            exit(EXIT_FAILURE);
        }
        init_SLNode(newNode);
        newNode->data = data;
        newNode->next = NULL;

        // 큐가 비어있는 경우
        if (isEmpty(queue)) {
            queue->front = newNode;
            queue->rear = newNode;
        } else {
            // 큐의 뒤에 노드 추가
            queue->rear->next = newNode;
            queue->rear = newNode;
        }
    }

    // 큐에서 요소 제거 (dequeue)
    Node* dequeue(Queue* queue) {
        if (isEmpty(queue)) {
            fprintf(stderr, "큐가 비어있습니다.\n");
            exit(EXIT_FAILURE);
        }

        // 큐의 맨 앞 노드 제거
        Node* data = queue->front->data;
        SLNode* temp = queue->front;
        queue->front = queue->front->next;

        // 제거한 노드 메모리 해제
        free(temp);

        // 만약 큐가 비어있다면 rear도 NULL로 설정
        if (queue->front == NULL) {
            queue->rear = NULL;
        }

        return data;
    }

    // 큐의 맨 앞 요소 반환 (peek)
    Node* front(Queue* queue) {
        if (isEmpty(queue)) {
            fprintf(stderr, "큐가 비어있습니다.\n");
            exit(EXIT_FAILURE);
        }
        return queue->front->data;
    }

    // 큐 출력 함수 (디버깅용)
    void printQueue(Queue* queue) {
        if (isEmpty(queue)) {
            printf("큐가 비어있습니다.\n");
            return;
        }

        SLNode* current = queue->front;
        while (current != NULL) {
            printf("%d ", current->data->val);
            current = current->next;
        }
        printf("\n");
    }


    /*BST*/
    Node* insert_help(Node* currNode, int x){
    if (currNode==NULL){
        Node* newNode =(Node*) malloc(sizeof(Node));
        init_node(newNode, x);
        return newNode;
    }

    if (x<currNode->val){
        currNode->left=insert_help(currNode->left, x);
    }
    else if (x>currNode->val){
        currNode->right=insert_help(currNode->right, x);
    }
    else {
        printf("Already exist. (Value : %d)\n", x);
        return currNode;
    }
    return currNode;

}

    void insert(Tree* bst, int x){
        bst->root = insert_help(bst->root, x);
    }

void bfs(Tree* tree) {
    if (tree->root ==NULL){
        return;
    }
    printf("<BFS>\n");
    Queue q;
    initializeQueue(&q);
    enqueue(&q, tree->root);
    Node* curr_node;
    while (isEmpty(&q)==0){
        curr_node = dequeue(&q);
        printf("%d ", curr_node->val); //visit
        if (curr_node->left!=NULL){
            enqueue(&q, curr_node->left);
        }
        if (curr_node->right!=NULL){
            enqueue(&q, curr_node->right);
        }
        
    }
    printf(".\n");
}

void dfs_help_preorder(Node* curr_node){
    printf("%d ", curr_node->val); //visit
    if (curr_node->left!=NULL){
        dfs_help_preorder(curr_node->left);
    }
    if (curr_node->right!=NULL){
        dfs_help_preorder(curr_node->right);
    }
}

void dfs_preorder(Tree* tree){
    if (tree->root==NULL){
        return;
    }
    printf("<DFS_preorder>\n");
    dfs_help_preorder(tree->root);
    printf("\n");
}




void dfs_help_inorder(Node* curr_node){
    if (curr_node->left!=NULL){
        dfs_help_inorder(curr_node->left);
    }
    printf("%d ", curr_node->val); //visit
    if (curr_node->right!=NULL){
        dfs_help_inorder(curr_node->right);
    }
}

void dfs_inorder(Tree* tree){
    if (tree->root==NULL){
        return;
    }
    printf("<DFS_inorder>\n");
    dfs_help_inorder(tree->root);
    printf("\n");

}


void dfs_help_postorder(Node* curr_node){
    if (curr_node->left!=NULL){
        dfs_help_postorder(curr_node->left);
    }
    if (curr_node->right!=NULL){
        dfs_help_postorder(curr_node->right);
    }
    printf("%d ", curr_node->val); //visit

}

void dfs_postorder(Tree* tree){
    if (tree->root==NULL){
        return;
    }
    printf("<DFS_postorder>\n");
    dfs_help_postorder(tree->root);
    printf("\n");

}


/*File Size Calculation By DFS*/
int own_size(Node* node){
    if (node==NULL){
        return 0;
    }
    return node->val;
}

int cumulative_sum(Node* node){
    int ans=0;
    if (node==NULL){
        return ans;
    }
    if (node->left!=NULL){
        ans+=cumulative_sum(node->left);
    }
    if (node->right!=NULL){
        ans+=cumulative_sum(node->right);
    }
    ans+=own_size(node);
    return ans;
}

int cumulative_sum_of_tree(Tree* tree){
    if (tree->root==NULL){
        return 0;
    }
    return cumulative_sum(tree->root);
}


int main(void){
    Tree tree;
    init_tree(&tree);

    insert(&tree, 5);
    insert(&tree, 3);
    insert(&tree, 7);
    insert(&tree, 1);
    insert(&tree, 4);
    insert(&tree, 6);
    insert(&tree, 8);
    
    bfs(&tree);

    dfs_preorder(&tree);
    dfs_inorder(&tree);
    dfs_postorder(&tree);

    printf("Cumulative sum of the tree is (%d).\n", cumulative_sum_of_tree(&tree));

}