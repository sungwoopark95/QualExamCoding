#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define RED 0
#define BLACK 1

// Node 구조체
typedef struct Node {
    int data;
    int color;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

// RBT 구조체
typedef struct RedBlackTree {
    Node* NIL_LEAF;
    Node* root;
} RedBlackTree;

Node* createNode(int data, int color, Node* parent, RedBlackTree* tree) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->color = color;
    new_node->parent = parent;
    new_node->left = tree->NIL_LEAF;  // 수정된 부분
    new_node->right = tree->NIL_LEAF; // 수정된 부분
    return new_node;
}

// RBT 초기화 함수
RedBlackTree* createRBT() {
    RedBlackTree* tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    tree->NIL_LEAF = createNode(0, BLACK, NULL, tree);  // None 대체
    tree->root = tree->NIL_LEAF;
    return tree;
}

Node* insert_node(RedBlackTree* tree, Node* root, Node* node) {
    if (root == tree->NIL_LEAF) {
        return node;
    }

    if (node->data < root->data) {
        root->left = insert_node(tree, root->left, node);
        root->left->parent = root;
        return root;
    } else {
        root->right = insert_node(tree, root->right, node);
        root->right->parent = root;
        return root;
    }
}

// 왼쪽 회전 함수
void rotate_left(RedBlackTree* tree, Node* node) {
    // node의 오른쪽 자식을 임시로 저장
    Node* right_temp = node->right;
    
    // node의 오른쪽 자식을 right_temp의 왼쪽 자식으로 설정
    node->right = right_temp->left;
    
    // right_temp의 왼쪽 자식이 NIL 노드가 아니라면, 그 부모를 node로 설정
    if (right_temp->left != tree->NIL_LEAF) {
        right_temp->left->parent = node;
    }

    // right_temp의 부모를 node의 부모로 설정
    right_temp->parent = node->parent;
    
    // node가 루트 노드라면 right_temp를 새로운 루트로 설정
    if (node->parent == NULL) {
        tree->root = right_temp;
    }
    // node가 부모의 왼쪽 자식이라면 right_temp를 부모의 왼쪽 자식으로 설정
    else if (node == node->parent->left) {
        node->parent->left = right_temp;
    }
    // 그렇지 않으면 right_temp를 부모의 오른쪽 자식으로 설정
    else {
        node->parent->right = right_temp;
    }

    // right_temp의 왼쪽 자식을 node로 설정
    right_temp->left = node;
    
    // node의 부모를 right_temp로 설정
    node->parent = right_temp;
}

// 오른쪽 회전 함수
void rotate_right(RedBlackTree* tree, Node* node) {
    // node의 왼쪽 자식을 임시로 저장
    Node* left_temp = node->left;
    
    // node의 왼쪽 자식을 left_temp의 오른쪽 자식으로 설정
    node->left = left_temp->right;

    // left_temp의 오른쪽 자식이 NIL 노드가 아니라면, 그 부모를 node로 설정
    if (left_temp->right != tree->NIL_LEAF) {
        left_temp->right->parent = node;
    }

    // left_temp의 부모를 node의 부모로 설정
    left_temp->parent = node->parent;

    // node가 루트 노드라면 left_temp를 새로운 루트로 설정
    if (node->parent == NULL) {
        tree->root = left_temp;
    }
    // node가 부모의 오른쪽 자식이라면 left_temp를 부모의 오른쪽 자식으로 설정
    else if (node == node->parent->right) {
        node->parent->right = left_temp;
    }
    // 그렇지 않으면 left_temp를 부모의 왼쪽 자식으로 설정
    else {
        node->parent->left = left_temp;
    }

    // left_temp의 오른쪽 자식을 node로 설정
    left_temp->right = node;

    // node의 부모를 left_temp로 설정
    node->parent = left_temp;
}

void fix_insert(RedBlackTree* tree, Node* k) {
    // k의 부모 색깔이 빨간색인 동안 반복
    while (k->parent->color == RED) {
        // k의 부모가 할아버지 노드의 오른쪽 자식이면
        if (k->parent == k->parent->parent->right) {
            // 아저씨 노드를 할아버지 노드의 왼쪽 자식으로 설정
            Node* uncle = k->parent->parent->left;
            
            // 아저씨 노드의 색깔이 빨간색이면
            if (uncle->color == RED) {
                // 아저씨와 k의 부모 둘 다 검은색으로 변경하고 할아버지 노드를 빨간색으로 변경
                uncle->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;  // k를 할아버지 노드로 옮김
            } else {
                // k가 부모의 왼쪽 자식이면
                if (k == k->parent->left) {
                    k = k->parent;
                    rotate_right(tree, k);  // 오른쪽으로 회전
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotate_left(tree, k->parent->parent);  // 왼쪽으로 회전
            }
        } else {
            // 아저씨 노드를 할아버지 노드의 오른쪽 자식으로 설정
            Node* uncle = k->parent->parent->right;
            
            // 아저씨 노드의 색깔이 빨간색이면
            if (uncle->color == RED) {
                // 아저씨와 k의 부모 둘 다 검은색으로 변경하고 할아버지 노드를 빨간색으로 변경
                uncle->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;  // k를 할아버지 노드로 옮김
            } else {
                // k가 부모의 오른쪽 자식이면
                if (k == k->parent->right) {
                    k = k->parent;
                    rotate_left(tree, k);  // 왼쪽으로 회전
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotate_right(tree, k->parent->parent);  // 오른쪽으로 회전
            }
        }

        // k가 루트 노드면 반복문 종료
        if (k == tree->root) {
            break;
        }
    }
    // 루트 노드의 색깔을 검은색으로 설정
    tree->root->color = BLACK;
}

void insert(RedBlackTree* tree, int data) {
    Node* new_node = createNode(data, RED, NULL, tree); // 함수 호출 수정
    if (tree->root == tree->NIL_LEAF) {
        tree->root = new_node;
        tree->root->color = BLACK;
        return;
    }
    insert_node(tree, tree->root, new_node);
    fix_insert(tree, new_node); // 수정된 부분
}


// 트리를 출력하는 함수
void print_tree(RedBlackTree* tree, Node* node, char* indent, bool last) {
    if (node != tree->NIL_LEAF) { // node가 NIL_LEAF가 아닌 경우
        printf("%s", indent); // 들여쓰기 출력
        
        if (last) {
            printf("R----");
            strcat(indent, "     "); // indent에 "     " 추가
        } else {
            printf("L----");
            strcat(indent, "|    "); // indent에 "|    " 추가
        }
        
        // 노드 색상에 따라 문자열 설정
        char* color = node->color == BLACK ? "BLACK" : "RED";
        printf("%d (%s)\n", node->data, color); // 노드의 데이터와 색상 출력
        
        // 왼쪽과 오른쪽 자식 노드를 재귀적으로 출력
        print_tree(tree, node->left, indent, false);
        print_tree(tree, node->right, indent, true);
    }
}

int main() {
    // 레드블랙트리 초기화 및 노드 삽입 예시
    RedBlackTree* tree = createRBT();
    insert(tree, 5);
    insert(tree, 3);
    insert(tree, 8);
    insert(tree, 2);
    insert(tree, 4);
    insert(tree, 7);
    insert(tree, 9);
    
    // 트리 출력
    char initial_indent[100] = ""; // 초기 들여쓰기는 빈 문자열
    print_tree(tree, tree->root, initial_indent, true);
    
    return 0;
}