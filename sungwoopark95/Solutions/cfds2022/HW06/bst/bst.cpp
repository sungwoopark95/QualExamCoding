#include <iostream>
#include "bst.h" // BST 클래스와 관련된 선언을 포함하는 헤더 파일을 포함시킵니다.

using namespace std;

void BST::Insert(int key) {
    Node* z = new Node(key); // 새로운 노드를 생성하고 key 값을 할당합니다.

    Node* x = this->root; // 현재 BST의 루트를 x에 할당합니다.
    Node* y = NULL; // y는 x의 부모 노드를 추적하기 위한 포인터입니다.

    // 삽입할 위치를 찾기 위해 트리를 순회합니다.
    while (x != NULL) {
        y = x; 
        if (z->key < x->key) {
            x = x->left; // 왼쪽 자식으로 이동
        } else {
            x = x->right; // 오른쪽 자식으로 이동
        }
    }

    z->parent = y; // z의 부모를 y로 설정합니다.

    // y가 NULL이면 트리가 비어 있으므로 z를 루트로 설정합니다.
    if (y == NULL) {
        root = z;
    }
    else if (z->key < y->key) {
        y->left = z; // z를 y의 왼쪽 자식으로 설정
    }
    else {
        y->right = z; // z를 y의 오른쪽 자식으로 설정
    }
}

void BST::transplant(Node* u, Node* v) {
    // u가 루트 노드라면 v를 새로운 루트로 설정합니다.
    if (u->parent == NULL) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v; // u가 왼쪽 자식이면 v를 왼쪽 자식으로 설정
    } else {
        u->parent->right = v; // u가 오른쪽 자식이면 v를 오른쪽 자식으로 설정
    }

    if (v != NULL) {
        v->parent = u->parent; // v의 부모를 u의 부모로 설정
    }
}

void BST::Delete(Node* z) {
    Node* y;

    // z의 왼쪽 자식이 없는 경우, z의 오른쪽 자식을 z의 위치로 이동시킵니다.
    if (z->left == NULL) {
        transplant(z, z->right);
    }
    // z의 오른쪽 자식이 없는 경우, z의 왼쪽 자식을 z의 위치로 이동시킵니다.
    else if (z->right == NULL) {
        transplant(z, z->left);
    }
    else {
        // z의 오른쪽 서브트리에서 가장 작은 값을 가진 노드를 찾습니다.
        y = Minimum(z->right);
        if (y->parent != z) {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

void BST::Preorder(Node* node) {
    // 노드가 NULL이 아닌 경우, 현재 노드를 출력하고 왼쪽 서브트리와 오른쪽 서브트리를 순회합니다.
    if (node != NULL) {
        cout << node->key << " ";
        Preorder(node->left);
        Preorder(node->right);
    } 
}

void BST::Inorder(Node* node) {
    // 노드가 NULL이 아닌 경우, 왼쪽 서브트리를 순회하고 현재 노드를 출력한 후 오른쪽 서브트리를 순회합니다.
    if (node != NULL) {
        Inorder(node->left);
        cout << node->key << " ";
        Inorder(node->right);
    } 
}

void BST::Postorder(Node* node) {
    // 노드가 NULL이 아닌 경우, 왼쪽 서브트리와 오른쪽 서브트리를 순회한 후 현재 노드를 출력합니다.
    if (node != NULL) {
        Postorder(node->left);
        Postorder(node->right);
        cout << node->key << " ";
    } 
}

BST::Node* BST::Search(Node* node, int key) {
    // 노드가 NULL이거나 노드의 키 값이 찾는 키 값과 같은 경우, 현재 노드를 반환합니다.
    if (node == NULL || key == node->key) {
        return node;
    }

    // 찾는 키 값이 현재 노드의 키 값보다 작은 경우, 왼쪽 서브트리에서 검색을 계속합니다.
    if (key < node->key)
        return Search(node->left, key);
    // 그렇지 않은 경우, 오른쪽 서브트리에서 검색을 계속합니다.
    else
        return Search(node->right, key);
}

BST::Node* BST::Maximum(Node* node) {
    // 오른쪽 자식을 따라 최대값을 찾습니다. BST에서 오른쪽 서브트리에는 항상 더 큰 값들이 있습니다.
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

BST::Node* BST::Minimum(Node* node) {
    // 왼쪽 자식을 따라 최소값을 찾습니다. BST에서 왼쪽 서브트리에는 항상 더 작은 값들이 있습니다.
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

BST::Node* BST::Successor(Node* x) {
    // x의 오른쪽 서브트리의 최소값이 후속자입니다.
    if (x->right != NULL) {
        return Minimum(x->right);
    }

    // 오른쪽 서브트리가 없는 경우, x의 부모를 따라 위로 올라가면서 후속자를 찾습니다.
    Node* y = x->parent;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

BST::Node* BST::Predecessor(Node* x) {
    // x의 왼쪽 서브트리의 최대값이 전임자입니다.
    if (x->left != NULL) {
        return Maximum(x->left);
    }

    // 왼쪽 서브트리가 없는 경우, x의 부모를 따라 위로 올라가면서 전임자를 찾습니다.
    Node* y = x->parent;
    while (y != NULL && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

void BST::_print(Node* root, string indent, bool last) {
    // 현재 노드가 NULL이 아닌 경우에만 출력합니다.
    if (root != NULL) {
        cout << indent;
        // 마지막 노드인 경우와 그렇지 않은 경우에 따라 출력 형식을 다르게 합니다.
        if (last) {
            cout << "└────";
            indent += "     ";
        } else {
            cout << "├────";
            indent += "|    ";
        }

        cout << root->key << endl;

        // 왼쪽과 오른쪽 자식 노드를 재귀적으로 출력합니다.
        _print(root->left, indent, false);
        _print(root->right, indent, true);
    }
}

void BST::Print() {
    // 루트 노드가 NULL이 아닌 경우에만 트리를 출력합니다.
    if (GetRoot() != NULL)
        _print(GetRoot(), "", true);
}
