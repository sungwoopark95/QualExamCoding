/*
[BST 구현]
< Methods >
1. insert
2. delete
3. preorder (subtrees 프린트 전에 root print
    / inorder(left subtrees -> root -> right subtrees) 
    / postorder(subtrees 프린트 한 후 root print)
4. search
5. maximum / minimum
6. successor / presuccessor
7. getroot
    (root node 반환 함수)
8. transplant

< Output >
========== Initial BST ==========
└────8
     ├────5
     └────18
          ├────15
          |    └────17
          └────25
               └────40
                    └────80
======= After deleting 25 =======
└────8
     ├────5
     └────18
          ├────15
          |    └────17
          └────40
               └────80
*/

#include <iostream>
#include "CFDS1_HW5_BST.h"

using namespace std;
/*----------------------------- BST Insertion 함수 ---------------------------*/
// 이진 탐색 트리에 키 값을 삽입하는 함수
void BST::Insert(int key) {
  // 삽입할 새 노드를 생성하고 초기화합니다.
  Node* z = new Node(key);

  Node* x = this->root; // 현재 노드를 루트로 시작 (new node z와 비교 먼저 할 root node 설정)
  Node* y = NULL;       // 이전 노드(부모 노드)를 저장하기 위한 변수

  // 적절한 위치를 찾아 삽입할 노드의 위치를 결정 (leaf node까지 내려가면서 insert 할 곳 찾음)
  while (x != NULL) {
    y = x; // y는 x의 부모 노드가 됩니다.
    if (z->key < x->key) { // 삽입할 키가 현재 노드의 키보다 작으면 왼쪽으로 이동
      x = x->left;
    } else { // 그렇지 않으면 오른쪽으로 이동
      x = x->right;
    }
  }

  // z의 부모 노드를 y로 설정합니다.
  z->parent = y;

  // y가 NULL인 경우, 트리가 비어있으므로 z를 루트로 설정합니다.
  if (y == NULL) {
    root = z;
  }
  // 삽입할 키가 y의 키보다 작으면 왼쪽 자식으로 삽입합니다. (노드 insert 후 연결 과정)
  else if (z->key < y->key) {
    y->left = z;
  }
  // 그렇지 않으면 오른쪽 자식으로 삽입합니다.
  else {
    y->right = z;
  }
}

/*------------------------- BST Deletion 함수 (Transplant 포함) -------------------------*/
// 노드의 위치를 교환하는 함수
void BST::transplant(Node* u, Node* v) {
  // u가 root node면 v를 새로운 root로 설정합니다.
  if (u->parent == NULL) {
    root = v;
  } 
  // u가 왼쪽 자식 노드면 v를 왼쪽 자식 노드로 설정합니다.
  else if (u == u->parent->left) {
    u->parent->left = v;
  } 
  // u가 오른쪽 자식 노드면 v를 오른쪽 자식 노드로 설정합니다.
  else {
    u->parent->right = v;
  }

  // v가 NULL이 아닌 경우, v의 부모를 u의 부모로 설정합니다.
  if (v != NULL) {
    v->parent = u->parent;
  }
}

// 이진 탐색 트리에서 노드를 삭제하는 함수
void BST::Delete(Node* z) {
  Node* y;

  // z의 왼쪽 자식이 없는 경우
  if (z->left == NULL) {
    transplant(z, z->right);
  } 
  // z의 오른쪽 자식이 없는 경우
  else if (z->right == NULL) {
    transplant(z, z->left);
  } 
  // z의 양쪽 자식이 모두 있는 경우
  else {
    // z의 right subtree에서 가장 작은 node (= successor)를 찾습니다.
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
/*----------------------------- BST Traversal 함수 ---------------------------*/
// preorder traversal
void BST::Preorder(Node* node) {
  if (node != NULL) {
    cout << node->key << " "; // 현재 노드 출력
    Preorder(node->left);     // 왼쪽 서브트리 순회
    Preorder(node->right);    // 오른쪽 서브트리 순회
  } 
}

// inorder traversal
void BST::Inorder(Node* node) {
  if (node != NULL) {
    Inorder(node->left);      // 왼쪽 서브트리 순회
    cout << node->key << " "; // 현재 노드 출력
    Inorder(node->right);     // 오른쪽 서브트리 순회
  } 
}

// postorder traversal
void BST::Postorder(Node* node) {
  if (node != NULL) {
    Postorder(node->left);    // 왼쪽 서브트리 순회
    Postorder(node->right);   // 오른쪽 서브트리 순회
    cout << node->key << " "; // 현재 노드 출력
  } 
}

/*----------------------------- BST Search(Find) 함수 ---------------------------*/
// 지정된 키 값을 가진 노드를 찾는 함수
BST::Node* BST::Search(Node* node, int key) {
  // 노드가 NULL이거나 키 값이 현재 노드의 키와 같으면 해당 노드를 반환합니다.
  if (node == NULL || key == node->key) {
    return node;
  }

  // 찾는 키 값이 현재 노드의 키보다 작으면 왼쪽 서브트리에서 탐색을 계속합니다.
  if (key < node->key)
    return Search(node->left, key);
  // 그렇지 않으면 오른쪽 서브트리에서 탐색을 계속합니다.
  else
    return Search(node->right, key);
}

/*----------------------------- BST Maximum Node 찾는 함수 ---------------------------*/
// 최대 키 값을 가진 노드를 찾는 함수
BST::Node* BST::Maximum(Node* node) {
  // 오른쪽 자식 노드가 없을 때까지 오른쪽으로 이동합니다.
  while (node->right != NULL) {
    node = node->right;
  }
  return node; // 최대 키 값을 가진 노드 반환
}

/*----------------------------- BST Minimum Node 찾는 함수 ---------------------------*/
// 최소 키 값을 가진 노드를 찾는 함수
BST::Node* BST::Minimum(Node* node) {
  // 왼쪽 자식 노드가 없을 때까지 왼쪽으로 이동합니다.
  while (node->left != NULL) {
    node = node->left;
  }
  return node; // 최소 키 값을 가진 노드 반환
}

/*----------------------------- BST Find Successor 함수 ---------------------------*/
// 지정된 노드의 후속자(successor)를 찾는 함수
BST::Node* BST::Successor(Node* x) {
  // x의 오른쪽 자식이 있다면, right subtree의 최소 값을 가진 노드가 후속자입니다.
  if (x->right != NULL) {
    return Minimum(x->right);
  }

  Node* y = x->parent;
  // x가 오른쪽 자식 노드라면, 위로 이동하면서 처음으로 왼쪽 자식 노드가 되는 노드의 부모를 찾습니다.
  while (y != NULL && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

/*----------------------------- BST Find Predecessor 찾는 함수 ---------------------------*/
// 지정된 노드의 선행자(predecessor)를 찾는 함수
BST::Node* BST::Predecessor(Node* x) {
  // x의 왼쪽 자식이 있다면, left subtree의 최대 값을 가진 노드가 선행자입니다.
  if (x->left != NULL) {
    return Maximum(x->left);
  }

  Node* y = x->parent;
  // x가 왼쪽 자식 노드라면, 위로 이동하면서 처음으로 오른쪽 자식 노드가 되는 노드의 부모를 찾습니다.
  while (y != NULL && x == y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}

/*----------------------------- BST Print 함수 ---------------------------*/
// 이진 탐색 트리를 시각적으로 출력하는 보조 함수
void BST::_print(Node* root, string indent, bool last) {
  if (root != NULL) {
    cout << indent;
    if (last) {
      cout << "└────"; // 마지막 노드의 경우 이 형태로 출력
      indent += "     "; // 들여쓰기 갱신
    } else {
      cout << "├────"; // 중간 노드의 경우 이 형태로 출력
      indent += "|    "; // 들여쓰기 갱신
    }

    cout << root->key << endl; // 현재 노드의 키 값을 출력

    _print(root->left, indent, false); // 왼쪽 서브트리 출력
    _print(root->right, indent, true); // 오른쪽 서브트리 출력
  }
}

// 이진 탐색 트리를 시각적으로 출력하는 함수
void BST::Print() {
  if (GetRoot() != NULL) // 루트 노드가 NULL이 아니면
    _print(GetRoot(), "", true); // 루트 노드부터 트리를 출력
}

