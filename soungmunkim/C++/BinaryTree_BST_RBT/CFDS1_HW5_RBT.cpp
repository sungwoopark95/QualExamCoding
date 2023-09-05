/*
[RBT 구현]

< Methods>
1. Insert
2. Delete
3. Traversal
    preorder
    inorder
    postorder
4. Search
5. Successor/Predecessor
6. Balance Tree
7. Print

< Output >
========== Initial RBT ==========
R----17 (BLACK)
     L----8 (RED)
     |    L----5 (BLACK)
     |    R----15 (BLACK)
     R----25 (RED)
          L----18 (BLACK)
          R----40 (BLACK)
               R----80 (RED)
======= After deleting 25 =======
R----17 (BLACK)
     L----8 (RED)
     |    L----5 (BLACK)
     |    R----15 (BLACK)
     R----40 (RED)
          L----18 (BLACK)
          R----80 (BLACK)
*/

#include <iostream>
#include "CFDS1_HW5_RBT.h"

using namespace std;

// Constructor: 레드-블랙 트리를 초기화합니다.
RBT::RBT() {
  // Tnil = Black의 NIL 노드로 초기
  // Red Black Tree에서는 외부 노드(NIL 노드)를 사용하여 트리의 끝을 나타냅니다.
  Tnil = new Node(0, NULL, NULL, NULL, COLOR_BLACK);
  root = Tnil; // 초기 루트는 NIL입니다.
}

/*---------------------------- RBT Insert 함수 -------------------------------- */
// tree에 key를 insert하는 함수입니다.
void RBT::Insert(int key) {
  // new node를 생성하고 초기화합니다. 새로 들어오는 노드의 색상은 항상 RED로 설정됩니다.
  Node* z = new Node(key, NULL, Tnil, Tnil, COLOR_RED);

  Node* x = this->root; // 새로운 node z와 비교될 root인 x
  Node* y = NULL; // z의 parent 될 node

  // Insert할 위치를 찾습니다. (일반 BST의 Insert 알고리즘과 동일)
  while (x != Tnil) { // sentinel(끝)까지 내려가기
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  // 삽입 위치를 찾았으므로 z의 부모를 y로 설정합니다.
  z->parent = y;

  // 삽입할 위치에 따라 z를 y의 왼쪽 또는 오른쪽 자식으로 설정합니다.
  if (y == NULL) { // tree가 비어있으면
    root = z;
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }

  // 새로운 노드가 root node이거나 할아버지 노드가 없는 경우
  if (z->parent == NULL || z->parent->parent == NULL) {
    z->color = COLOR_BLACK; // root node는 항상 Black입니다.
    return;
  }

  // Insertion 후 Red Black Tree의 규칙을 위반하지 않도록 조정합니다.
  InsertFixUp(z); // balance 유지
}

/*---------------------------- RBT Delete 함수 -------------------------------- */
// Node를 삭제하는 함수입니다.
void RBT::Delete(Node* z) {
  // 삭제 연산을 수행하기 전에 y의 원래 색상을 저장합니다. 
  // 이 정보는 후에 트리의 균형을 복구하는 데 사용됩니다.
  Node* y = z;
  int y_original_color = y->color;

  Node* x;

  // 삭제할 노드 z의 자식 노드의 수에 따라 다른 처리를 합니다.
  if (z->left == Tnil) { // case 2
    x = z->right;
    Transplant(z, z->right);
  } else if (z->right == Tnil) { // case 2
    x = z->left;
    Transplant(z, z->left);
  } else { // case 3
    y = Minimum(z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    } else {
      Transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    Transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }

  delete z;  // z 노드를 메모리에서 삭제합니다.

  // 삭제된 노드의 색상이 Black이었다면 Red Black Tree의 규칙을 위반하지 않도록 트리를 조정합니다.
  if (y_original_color == COLOR_BLACK){ // balance 조정
    DeleteFixUp(x);
  }
}

/*---------------------------- RBT Traversal 함수 -------------------------------- */
// 트리를 preorder 순회하는 함수입니다.
void RBT::Preorder(Node* node) {
  if (node != Tnil) {
    cout << node->key << " ";
    Preorder(node->left);
    Preorder(node->right);
  } 
}

// 트리를 inorder 순회하는 함수입니다.
void RBT::Inorder(Node* node) {
  if (node != Tnil) {
    Inorder(node->left);
    cout << node->key << " ";
    Inorder(node->right);
  } 
}

// 트리를 postorder 순회하여 모든 노드의 키를 출력합니다.
void RBT::Postorder(Node* node) {
  if (node != Tnil) {
    Postorder(node->left);
    Postorder(node->right);
    cout << node->key << " ";
  } 
}

/*---------------------------- RBT Search(Find) 함수 -------------------------------- */
// 주어진 key값을 가진 node를 tree에서 검색합니다.
RBT::Node* RBT::Search(Node* node, int key) {
  if (key == node->key) {
    return node;
  } else if (node == Tnil) {
    return NULL;
  }

  if (key < node->key)
    return Search(node->left, key);
  else
    return Search(node->right, key);
}

/*---------------------------- RBT Successor/Predecessor 찾는 함수 -------------------------------- */
// 주어진 노드를 기준으로 tree에서 최대 키 값을 가진 노드를 찾습니다.
RBT::Node* RBT::Maximum(Node* node) {
  while (node->right != Tnil) {
    node = node->right;
  }
  return node;
}

// 주어진 노드를 기준으로 tree에서 최소 키 값을 가진 노드를 찾습니다.
RBT::Node* RBT::Minimum(Node* node) {
  while (node->left != Tnil) {
    node = node->left;
  }
  return node;
}

// 주어진 노드의 successor를 찾습니다. 
// successor는 주어진 노드보다 큰 키 중 가장 작은 키를 가진 노드입니다.
RBT::Node* RBT::Successor(Node* x) {
  if (x->right != Tnil) {
    return Minimum(x->right);
  }

  Node* y = x->parent;
  while (y != Tnil && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

// 주어진 노드의 predecessor를 찾습니다. 
// predecessor는 주어진 노드보다 작은 키 중 가장 큰 키를 가진 노드입니다.
RBT::Node* RBT::Predecessor(Node* x) {
  if (x->left != Tnil) {
    return Maximum(x->left);
  }

  Node* y = x->parent;
  while (y != Tnil && x == y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}

/*---------------------------- RBT Balance 유지 함수 -------------------------------- */
// Insertion 연산 후 Red Black Tree의 규칙을 위반하지 않도록 트리를 조정합니다.
/*      Insert Fix up 함수      */
void RBT::InsertFixUp(Node* z) {
  Node* y;

  // Parent node가 Red인 경우만 조정이 필요합니다.
  while (z->parent->color == COLOR_RED) {
    // Parent node가 할아버지 노드의 오른쪽 자식인 경우
    if (z->parent == z->parent->parent->right) {
      y = z->parent->parent->left; // 삼촌 노드
      if (y->color == COLOR_RED) {

        // case 1: 삼촌 노드가 Red인 경우
        y->color = COLOR_BLACK;
        z->parent->color = COLOR_BLACK;
        z->parent->parent->color = COLOR_RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {

          // case 2: 삼촌 노드가 Black이고, z가 왼쪽 자식인 경우
          z = z->parent;
          RightRotate(z);
        }

        // case 3: 삼촌 노드가 Black이고, z가 오른쪽 자식인 경우
        z->parent->color = COLOR_BLACK;
        z->parent->parent->color = COLOR_RED;
        LeftRotate(z->parent->parent);
      }
    } else {

      // Parent node가 할아버지 노드의 왼쪽 자식인 경우
      // (위의 코드와 대칭적입니다.)
      y = z->parent->parent->right;

      if (y->color == COLOR_RED) {
        y->color = COLOR_BLACK;
        z->parent->color = COLOR_BLACK;
        z->parent->parent->color = COLOR_RED;
        z = z->parent->parent;	
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          LeftRotate(z);
        }
        z->parent->color = COLOR_BLACK;
        z->parent->parent->color = COLOR_RED;
        RightRotate(z->parent->parent);
      }
    }
    if (z == root) {
      break;
    }
  }
  root->color = COLOR_BLACK; // Root node는 항상 Black이어야 합니다.
}

/*     Left Rotate 함수      */
// 주어진 노드 x 주위로 Left Rotate을 수행합니다.
void RBT::LeftRotate(Node* x) {
  Node* y = x->right; // y는 x의 오른쪽 자식입니다.
  x->right = y->left; // y의 left subtree를 x의 right subtree로 이동합니다.
  
  if (y->left != Tnil) {
    y->left->parent = x; 
  }
  y->parent = x->parent;
  
  // x가 root였던 경우 y를 new root로 만듭니다.
  if (x->parent == NULL) {
    this->root = y;
  } else if (x == x->parent->left) { // x가 왼쪽 자식이었던 경우
    x->parent->left = y;
  } else { // x가 오른쪽 자식이었던 경우
    x->parent->right = y;
  }
  
  y->left = x; // y의 왼쪽 자식으로 x를 연결합니다.
  x->parent = y; // x의 부모를 y로 업데이트합니다.
}

/*     Right Rotate 함수      */
// 주어진 노드 x 주위로 Right Rotate 연산을 수행합니다.
void RBT::RightRotate(Node* x) {
  Node* y = x->left; // y는 x의 왼쪽 자식입니다.
  x->left = y->right; // y의 right subtree를 x의 left subtree로 이동합니다.
  
  if (y->right != Tnil) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  
  // x가 root였던 경우 y를 new root로 만듭니다.
  if (x->parent == NULL) {
    this->root = y;
  } else if (x == x->parent->right) { // x가 오른쪽 자식이었던 경우
    x->parent->right = y;
  } else { // x가 왼쪽 자식이었던 경우
    x->parent->left = y;
  }
  
  y->right = x; // y의 오른쪽 자식으로 x를 연결합니다.
  x->parent = y; // x의 부모를 y로 업데이트합니다.
}

/*     Delete Fixup 함수      */
// Delete 연산 후 Red Black Tree의 규칙을 위반하지 않도록 트리를 조정합니다.
void RBT::DeleteFixUp(Node* x) {
  Node* w;
  
  // x가 Root node가 아니며 Black인 경우에만 조정이 필요합니다.
  while (x != root && x->color == COLOR_BLACK) {
    if (x == x->parent->left) {
      w = x->parent->right; // w는 x의 형제 노드입니다.
      
      if (w->color == COLOR_RED) {
        w->color = COLOR_BLACK; // 형제 노드 w의 색상을 Black으로 변경합니다.
        x->parent->color = COLOR_RED; // Parent node의 색상을 Red로 변경합니다.
        LeftRotate(x->parent); // x의 Parent node를 중심으로 Left Rotate을 수행합니다.
        w = x->parent->right; // 형제 노드 w를 다시 설정합니다.
      }
      
      // w의 두 자식 모두 Black인 경우
      if (w->left->color == COLOR_BLACK && w->right->color == COLOR_BLACK) {
        w->color = COLOR_RED;
        x = x->parent;
      } else {

        // w의 오른쪽 자식만 Black인 경우
        if (w->right->color == COLOR_BLACK) {
          w->left->color = COLOR_BLACK;
          w->color = COLOR_RED;
          RightRotate(w);
          w = x->parent->right;
        } 
        
        // w의 오른쪽 자식이 Red인 경우
        w->color = x->parent->color;
        x->parent->color = COLOR_BLACK;
        w->right->color = COLOR_BLACK;
        LeftRotate(x->parent);
        x = root; // x를 root로 설정하여 루프를 종료합니다.
      }
    } else {
      // x가 오른쪽 자식인 경우 (위의 경우와 대칭적입니다.)
      // (이 부분은 x가 오른쪽 자식일 때의 처리를 나타냅니다.)
      w = x->parent->left;
      
      if (w->color == COLOR_RED) {
        w->color = COLOR_BLACK;
        x->parent->color = COLOR_RED;
        RightRotate(x->parent);
        w = x->parent->left;
      }
      
      if (w->right->color == COLOR_BLACK && w->right->color == COLOR_BLACK) {
        w->color = COLOR_RED;
        x = x->parent; 
      } else {
        if (w->left->color == COLOR_BLACK) {
          w->right->color = COLOR_BLACK;
          w->color = COLOR_RED;
          LeftRotate(w);
          w = x->parent->left;
        } 

        w->color = x->parent->color;
        x->parent->color = COLOR_BLACK;
        w->left->color = COLOR_BLACK;
        RightRotate(x->parent);
        x = root;
      }
    } 
  }
  x->color = COLOR_BLACK;
}

/*     Transplant 함수 for Delete 함수    */
// 노드 u와 v의 위치를 교체합니다. 이 함수는 Delete 연산에서 사용됩니다.
void RBT::Transplant(Node* u, Node* v) {
  if (u->parent == NULL) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

/*---------------------------- RBT Print 함수 -------------------------------- */
// 트리를 출력하는 데 사용되는 보조 함수입니다. recursively으로 호출되어 트리의 구조와 노드의 색상을 표시합니다.
void RBT::_print(Node* root, string indent, bool last) {
  if (root != Tnil) {
    cout << indent;
    if (last) {
      cout << "R----";  // 오른쪽 자식을 나타냅니다.
      indent += "     ";
    } else {
      cout << "L----";  // 왼쪽 자식을 나타냅니다.
      indent += "|    ";
    }
    
    // 조건이 true이면 black 아니면 red를 반환
    string sColor = (root->color == COLOR_BLACK) ? "BLACK" : "RED";
    cout << root->key << " (" << sColor << ")" << endl;
    _print(root->left, indent, false);
    _print(root->right, indent, true);
  }
}

// 트리를 시각적으로 출력하는 함수입니다.
void RBT::Print() {
  if (GetRoot() != NULL) {
    _print(GetRoot(), "", true);
  }
}

