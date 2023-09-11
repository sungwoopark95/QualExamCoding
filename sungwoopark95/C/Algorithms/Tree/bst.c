#include <stdio.h>
#include <stdlib.h>

// Node 구조체 정의
typedef struct Node {
    int key;                  // 노드에 저장될 값
    struct Node* left;        // 왼쪽 자식 노드
    struct Node* right;       // 오른쪽 자식 노드
    struct Node* parent;      // 부모 노드
} Node;

// BST 구조체 정의
typedef struct BST {
    Node* root;               // BST의 루트 노드
} BST;

// 새로운 Node를 생성하는 함수
Node* create_node(int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    return new_node;
}

// 새로운 BST를 생성하는 함수
BST* create_bst() {
    BST* tree = (BST*)malloc(sizeof(BST));
    tree->root = NULL;
    return tree;
}

// BST에 새로운 노드를 삽입하는 함수
void insert(BST* tree, int key) {
    Node* z = create_node(key);    // 삽입할 노드 생성
    Node* y = NULL;                // y는 x의 부모 노드를 가리킬 것임
    Node* x = tree->root;          // 루트에서 시작
    // 삽입할 위치를 찾기 위해 트리를 탐색
    while (x != NULL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;                 // z의 부모를 y로 설정
    if (y == NULL) {               // 트리가 비어있으면 z를 루트로 설정
        tree->root = z;
    } else if (z->key < y->key) {  // z의 키가 y의 키보다 작으면 왼쪽 자식으로 설정
        y->left = z;
    } else {                       // 그렇지 않으면 오른쪽 자식으로 설정
        y->right = z;
    }
}

// u를 v로 대체하는 연산
void transplant(BST* tree, Node* u, Node* v) {
    // u가 루트 노드인 경우
    if (u->parent == NULL) {
        tree->root = v;
    // u가 왼쪽 자식인 경우
    } else if (u == u->parent->left) {
        u->parent->left = v;
    // u가 오른쪽 자식인 경우
    } else {
        u->parent->right = v;
    }
    // v가 None이 아닌 경우
    if (v != NULL) {
        v->parent = u->parent;
    }
}

// 노드 z를 삭제하는 연산
void delete(BST* tree, Node* z) {
    if (z->left == NULL) {
        transplant(tree, z, z->right);
    } else if (z->right == NULL) {
        transplant(tree, z, z->left);
    } else {
        Node* y = minimum(z->right);
        if (y->parent != z) {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

// 중위 순회
void inorder(Node* node) {
    if (node) {
        inorder(node->left);
        printf("%d ", node->key);
        inorder(node->right);
    }
}

// 전위 순회
void preorder(Node* node) {
    if (node) {
        printf("%d ", node->key);
        preorder(node->left);
        preorder(node->right);
    }
}

// 후위 순회
void postorder(Node* node) {
    if (node) {
        postorder(node->left);
        postorder(node->right);
        printf("%d ", node->key);
    }
}

// key 값을 가진 노드를 탐색
Node* search(Node* node, int key) {
    while (node != NULL && key != node->key) {
        if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}

// 주어진 노드를 기준으로 가장 큰 키 값을 가진 노드를 찾는 연산
Node* maximum(Node* node) {
    while (node->right) {
        node = node->right;
    }
    return node;
}

// 주어진 노드를 기준으로 가장 작은 키 값을 가진 노드를 찾는 연산
Node* minimum(Node* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

// x의 후계자를 찾는 연산
Node* successor(Node* x) {
    if (x->right) {
        return minimum(x->right);
    }
    Node* y = x->parent;
    while (y && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

// x의 선조자를 찾는 연산
Node* predecessor(Node* x) {
    if (x->left) {
        return maximum(x->left);
    }
    Node* y = x->parent;
    while (y && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

// 트리를 시각적으로 출력
void print_tree(Node* node, int level) {
    if (node) {
        for (int i = 0; i < level * 4; i++) {
            printf(" ");
        }
        printf("%d\n", node->key);
        if (node->left || node->right) {
            print_tree(node->left, level + 1);
            print_tree(node->right, level + 1);
        }
    }
}

// 트리 전체를 출력
void print(BST* tree) {
    print_tree(tree->root, 0);
}