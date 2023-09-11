/*
linked list로 BST 구현하기
*/

#include <iostream>
#include "bst.h"

using namespace std;

// 키를 이용해 BST에 노드를 삽입하는 함수
void BST::Insert(int key) {
  Node* z = new Node(key);  // 새 노드 생성

  Node* x = this->root;     // 루트 노드로 시작
  Node* y = NULL;           // 부모 노드를 추적하기 위한 변수

  // 적절한 위치를 찾을 때까지 트리를 탐색
  while (x != NULL) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  // 찾은 위치에 새 노드 삽입
  z->parent = y;

  if (y == NULL) {
    root = z; // 트리가 비어 있는 경우
  }
  else if (z->key < y->key) {
    y->left = z; // 왼쪽 자식으로 삽입
  }
  else {
    y->right = z; // 오른쪽 자식으로 삽입
  }
}

// u의 위치에 v를 이식하는 함수
void BST::transplant(Node* u, Node* v){
  if (u->parent == NULL) {
    root = v; // u가 루트인 경우
  } else if (u == u->parent->left) {
    u->parent->left = v; // u가 왼쪽 자식인 경우
  } else{
    u->parent->right = v; // u가 오른쪽 자식인 경우
  }

  if (v != NULL) {
    v->parent = u->parent; // v의 부모 설정
  }
}

// 주어진 노드를 BST에서 삭제하는 함수
void BST::Delete(Node* z) {
  Node* y;

  if (z->left == NULL) {
    transplant(z, z->right); // 왼쪽 자식이 없는 경우
  }
  else if (z->right == NULL) {
    transplant(z, z->left); // 오른쪽 자식이 없는 경우
  }
  else {
    y = Minimum(z->right); // 후계자 찾기
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

// 전위 순회를 수행하는 함수
void BST::Preorder(Node* node) {
  if (node != NULL) {
    cout << node->key << " ";
    Preorder(node->left);
    Preorder(node->right);
  } 
}

// 중위 순회를 수행하는 함수
void BST::Inorder(Node* node) {
  if (node != NULL) {
    Inorder(node->left);
    cout << node->key << " ";
    Inorder(node->right);
  } 
}

// 후위 순회를 수행하는 함수
void BST::Postorder(Node* node) {
  if (node != NULL) {
    Postorder(node->left);
    Postorder(node->right);
    cout << node->key << " ";
  } 
}

// 키를 이용해 노드를 찾는 함수
BST::Node* BST::Search(Node* node, int key) {
  if (node == NULL || key == node->key) {
    return node; // 키를 찾았거나 노드가 없는 경우
  }

  if (key < node->key)
    return Search(node->left, key); // 왼쪽 서브트리에서 탐색
  else
    return Search(node->right, key); // 오른쪽 서브트리에서 탐색
}

// 최대값을 가진 노드를 반환하는 함수
BST::Node* BST::Maximum(Node* node) {
  while (node->right != NULL) {
    node = node->right; // 가장 오른쪽 노드로 이동
  }
  return node;
}

// 최소값을 가진 노드를 반환하는 함수
BST::Node* BST::Minimum(Node* node) {
  while (node->left != NULL) {
    node = node->left; // 가장 왼쪽 노드로 이동
  }
  return node;
}

// 주어진 노드의 후계자를 찾는 함수
BST::Node* BST::Successor(Node* x) {
  if (x->right != NULL) {
    return Minimum(x->right); // 오른쪽 서브트리의 최소값
  }

  Node* y = x->parent;
  while (y != NULL && x == y->right) {
    x = y;
    y = y->parent; // 부모 노드로 이동
  }
  return y;
}

// 주어진 노드의 선행자를 찾는 함수
BST::Node* BST::Predecessor(Node* x) {
  if (x->left != NULL) {
    return Maximum(x->left); // 왼쪽 서브트리의 최대값
  }

  Node* y = x->parent;
  while (y != NULL && x == y->left) {
    x = y;
    y = y->parent; // 부모 노드로 이동
  }
  return y;
}

// 트리를 시각적으로 출력하는 보조 함수
void BST::_print(Node* root, string indent, bool last) {
  if (root != NULL) {
    cout << indent;
    if (last) {
      cout << "└────";
      indent += "     ";
    } else {
      cout << "├────";
      indent += "|    ";
    }

    cout << root->key << endl;

    _print(root->left, indent, false);
    _print(root->right, indent, true);
  }
}

// 트리를 시각적으로 출력하는 함수
void BST::Print() {
  if (GetRoot() != NULL)
    _print(GetRoot(), "", true);
}

