/*
[특정 key를 BST에 넣는 코드]

You are given the root node of a binary search tree (BST) and a value to insert into the tree. 
Return the root node of the BST after the insertion. 
It is guaranteed that the new value does not exist in the original BST.

Notice that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % gcc 701_InsertIntoBST_SM.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test  
Enter node values in [a,b,c,...] format: [4,2,7,1,3]
Enter the key to insert: 5
4 2 7 1 3 5 %         
                                                                                                                                                          
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test
Enter node values in [a,b,c,...] format: [4,2,7,1,3,None,None,None,None,None,None]
Enter the key to insert: 5
4 2 7 1 3 5 %  
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// TreeNode 구조체 정의
typedef struct TreeNode {
    int key;                // 노드에 저장될 키 값
    struct TreeNode *parent; // 부모 노드
    struct TreeNode *left;   // 왼쪽 자식 노드
    struct TreeNode *right;  // 오른쪽 자식 노드
} TreeNode;


// BST에 노드를 삽입하는 함수 (Insert 함수)
TreeNode* insert(TreeNode *root, int key) {
    if (key == 0) { // 'None'을 0으로 간주
        return root;
    }
    // 루트가 없을 경우 새 노드를 생성
    if (root == NULL) {
        root = (TreeNode *)malloc(sizeof(TreeNode));
        root->key = key;
        root->parent = NULL;
        root->left = NULL;
        root->right = NULL;
    } else if (key < root->key) { // 키 값이 현재 루트보다 작으면 왼쪽으로
        root->left = insert(root->left, key);
        root->left->parent = root;
    } else { // 키 값이 현재 루트보다 크면 오른쪽으로
        root->right = insert(root->right, key);
        root->right->parent = root;
    }
    return root; // 삽입 후 루트 반환
}


// List에서 BST를 만드는 함수 (List to BST 함수)
TreeNode* create_BST(int input_list[], int size) {
    TreeNode *root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert(root, input_list[i]); // 각 항목을 트리에 삽입
    }
    return root;   // 루트 반환
}


// BST를 BFS 방식으로 프린트하는 함수 (BFS 방향으로 프린트하는 함수 )
void print_BST(TreeNode *node) {
    if (node == NULL) { // 노드가 없으면 반환
        return;
    }

    // 큐 구현을 위한 배열과 front, rear 인덱스
    TreeNode **queue = (TreeNode **)malloc(sizeof(TreeNode *) * 1000);
    int front = 0;
    int rear = 0;

    queue[rear++] = node; // 초기 루트 노드 삽입

    // 큐가 빌 때까지 반복
    while (front < rear) {
        TreeNode *current = queue[front++];
        printf("%d ", current->key);

        if (current->left) {
            queue[rear++] = current->left; // 왼쪽 자식 노드 큐에 삽입
        }
        if (current->right) {
            queue[rear++] = current->right; // 오른쪽 자식 노드 큐에 삽입
        }
    }

    free(queue); // 동적 메모리 해제
}

int main() {
    int input_list[1000];
    int size = 0;
    int key;

    printf("Enter node values in [a,b,c,...] format: ");
    char line[1000];
    fgets(line, sizeof(line), stdin); // 사용자로부터 입력 받기
    char *token = strtok(line, "[,]\n"); // 입력 값을 토큰으로 분리
    while (token != NULL) {
        input_list[size++] = atoi(token); // 배열에 저장
        token = strtok(NULL, "[,]\n");    // 다음 토큰으로 이동
    }

    printf("Enter the key to insert: ");
    scanf("%d", &key); // 키 값 입력 받기

    TreeNode *root = create_BST(input_list, size); // BST 생성
    insert(root, key);  // 키 값을 BST에 삽입
    print_BST(root);    // BST 프린트

    return 0;
}
