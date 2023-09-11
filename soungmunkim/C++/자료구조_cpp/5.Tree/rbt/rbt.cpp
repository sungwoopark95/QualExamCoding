#include <iostream>
#include "rbt.h"

using namespace std;

// RBT 클래스의 생성자
RBT::RBT() {
  // Tnil(센티널 노드)를 생성하고 모든 값을 초기화합니다.
  Tnil = new Node(0, NULL, NULL, NULL, COLOR_BLACK); // 키 값이 0인 검은색의 센티널 노드 생성
  root = Tnil; // 루트 노드를 센티널 노드(Tnil)로 초기화
}

// RBT에 노드를 삽입하는 함수
void RBT::Insert(int key) {
  // 새로운 노드 z를 생성합니다. 이 노드의 색깔은 빨간색입니다.
  Node* z = new Node(key, NULL, Tnil, Tnil, COLOR_RED); 

  Node* x = this->root; // 현재 루트부터 시작해서
  Node* y = NULL; // y는 x의 부모 노드를 추적하기 위한 변수

  // 삽입할 위치를 찾습니다.
  while (x != Tnil) { // x가 센티널 노드가 아닐 때까지
    y = x; // y는 x의 부모
    if (z->key < x->key) { // 삽입할 키가 현재 노드의 키보다 작으면
      x = x->left; // 왼쪽 자식으로 이동
    } else { // 아니면
      x = x->right; // 오른쪽 자식으로 이동
    }
  }

  z->parent = y; // z의 부모를 y로 설정

  // y가 NULL인 경우(트리가 비어 있는 경우)
  if (y == NULL) {
    root = z; // 루트를 z로 설정
  } else if (z->key < y->key) { // z의 키가 y의 키보다 작으면
    y->left = z; // y의 왼쪽 자식으로 z를 설정
  } else { // 아니면
    y->right = z; // y의 오른쪽 자식으로 z를 설정
  }

  // z의 부모가 NULL인 경우(z가 루트인 경우)
  if (z->parent == NULL){
    z->color = COLOR_BLACK; // z의 색깔을 검은색으로 변경
    return; // 함수 종료
  }

  // z의 할아버지 노드가 NULL인 경우
  if (z->parent->parent == NULL) {
    return; // 함수 종료
  }

  InsertFixUp(z); // RBT 속성을 유지하기 위해 삽입 후 조정 작업 실행
}

// RBT에서 노드를 삭제하는 함수
void RBT::Delete(Node* z) {
  Node* x;
  Node* y = z; // 삭제될 노드 또는 이동될 노드
  int y_original_color = y->color; // y의 원래 색깔 저장

  // z의 왼쪽 자식이 센티널 노드인 경우
  if (z->left == Tnil) {
    x = z->right;
    Transplant(z, z->right);
  } else if (z->right == Tnil) { // z의 오른쪽 자식이 센티널 노드인 경우
    x = z->left;
    Transplant(z, z->left);
  } else { // 두 자식 노드가 모두 센티널 노드가 아닌 경우
    y = Minimum(z->right); // z의 오른쪽 서브트리의 최소값 노드 찾기
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
  
  delete z; // z 노드 메모리 해제

  // y의 원래 색깔이 검은색이면 RBT 속성을 유지하기 위한 조정 필요
  if (y_original_color == COLOR_BLACK){
    DeleteFixUp(x);
  }
}

// 전위 순회 함수
void RBT::Preorder(Node* node) {
  if (node != Tnil) { // 노드가 센티널 노드가 아니면
    cout << node->key << " "; // 노드의 키 출력
    Preorder(node->left); // 왼쪽 서브트리로 재귀
    Preorder(node->right); // 오른쪽 서브트리로 재귀
  } 
}

// 중위 순회 함수
void RBT::Inorder(Node* node) {
  if (node != Tnil) { // 노드가 센티널 노드가 아니면
    Inorder(node->left); // 왼쪽 서브트리로 재귀
    cout << node->key << " "; // 노드의 키 출력
    Inorder(node->right); // 오른쪽 서브트리로 재귀
  } 
}

// 후위 순회 함수
void RBT::Postorder(Node* node) {
  if (node != Tnil) { // 노드가 센티널 노드가 아니면
    Postorder(node->left); // 왼쪽 서브트리로 재귀
    Postorder(node->right); // 오른쪽 서브트리로 재귀
    cout << node->key << " "; // 노드의 키 출력
  } 
}

// 노드를 키 값으로 검색하는 함수
RBT::Node* RBT::Search(Node* node, int key) {
  // 만약 현재 노드의 키와 검색하려는 키가 같다면 현재 노드 반환
  if (key == node->key) {
    return node;
  }
  // 현재 노드가 nil(트리의 끝)이라면 NULL 반환
  else if (node == Tnil) {
    return NULL;
  }

  // 검색하려는 키가 현재 노드의 키보다 작다면 왼쪽 서브트리에서 재귀적으로 검색
  if (key < node->key)
    return Search(node->left, key);
  // 그렇지 않다면 오른쪽 서브트리에서 재귀적으로 검색
  else
    return Search(node->right, key);
}

// 트리에서 최대 키 값을 가진 노드를 찾아서 반환하는 함수
RBT::Node* RBT::Maximum(Node* node) {
  // 오른쪽 자식이 nil이 될 때까지 오른쪽으로 이동
  while (node->right != Tnil) {
    node = node->right;
  }
  return node;
}

// 트리에서 최소 키 값을 가진 노드를 찾아서 반환하는 함수
RBT::Node* RBT::Minimum(Node* node) {
  // 왼쪽 자식이 nil이 될 때까지 왼쪽으로 이동
  while (node->left != Tnil) {
    node = node->left;
  }
  return node;
}

// 주어진 노드의 다음 노드(후속자)를 찾아서 반환하는 함수
RBT::Node* RBT::Successor(Node* x) {
  // 만약 x의 오른쪽 자식이 존재한다면, 오른쪽 서브트리의 최소 키 값을 가진 노드가 후속자
  if (x->right != Tnil) {
    return Minimum(x->right);
  }

  // x의 오른쪽 자식이 없다면, x의 부모를 따라가며 후속자를 찾는다.
  Node* y = x->parent;
  while (y != Tnil && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

// 주어진 노드의 이전 노드(선속자)를 찾아서 반환하는 함수
RBT::Node* RBT::Predecessor(Node* x) {
  // 만약 x의 왼쪽 자식이 존재한다면, 왼쪽 서브트리의 최대 키 값을 가진 노드가 선속자
  if (x->left != Tnil) {
    return Maximum(x->left);
  }

  // x의 왼쪽 자식이 없다면, x의 부모를 따라가며 선속자를 찾는다.
  Node* y = x->parent;
  while (y != Tnil && x == y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}


void RBT::InsertFixUp(Node* z) {
  Node* y;
  while (z->parent->color == COLOR_RED) {
    if (z->parent == z->parent->parent->right) {
      y = z->parent->parent->left;
      if (y->color == COLOR_RED) {
        // case 1
        y->color = COLOR_BLACK;
        z->parent->color = COLOR_BLACK;
        z->parent->parent->color = COLOR_RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          // case 2
          z = z->parent;
          RightRotate(z);
        }
        // case 3
        z->parent->color = COLOR_BLACK;
        z->parent->parent->color = COLOR_RED;
        LeftRotate(z->parent->parent);
      }
    } else {
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
  root->color = COLOR_BLACK;
}

void RBT::LeftRotate(Node* x) {
  Node* y = x->right;
  x->right = y->left;
  if (y->left != Tnil) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == NULL) {
    this->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void RBT::RightRotate(Node* x) {
  Node* y = x->left;
  x->left = y->right;
  if (y->right != Tnil) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == NULL) {
    this->root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

void RBT::DeleteFixUp(Node* x) {
  Node* w;
  while (x != root && x->color == COLOR_BLACK) {
    if (x == x->parent->left) {
      w = x->parent->right;
      if (w->color == COLOR_RED) {
        w->color = COLOR_BLACK;
        x->parent->color = COLOR_RED;
        LeftRotate(x->parent);
        w = x->parent->right;
      }

      if (w->left->color == COLOR_BLACK && w->right->color == COLOR_BLACK) {
        w->color = COLOR_RED;
        x = x->parent;
      } else {
        if (w->right->color == COLOR_BLACK) {
          w->left->color = COLOR_BLACK;
          w->color = COLOR_RED;
          RightRotate(w);
          w = x->parent->right;
        } 

        w->color = x->parent->color;
        x->parent->color = COLOR_BLACK;
        w->right->color = COLOR_BLACK;
        LeftRotate(x->parent);
        x = root;
      }
    } else {
      w = x->parent->left;
      if (w->color == COLOR_RED) {
        w->color = COLOR_BLACK;
        x->parent->color = COLOR_RED;
        RightRotate(x->parent);
        w = x->parent->left;
      }

      if (w->left->color == COLOR_BLACK && w->right->color == COLOR_BLACK) {
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

void RBT::Transplant(Node* u, Node* v){
  if (u->parent == NULL) {
    root = v;
  }
  else if (u == u->parent->left){
    u->parent->left = v;
  }
  else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

void RBT::_print(Node* root, string indent, bool last) {
  if (root != Tnil) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "     ";
    } else {
      cout << "L----";
      indent += "|    ";
    }

    string sColor =
      (root->color == COLOR_BLACK) ? "BLACK" : "RED";
    cout << root->key << " (" << sColor << ")" << endl;
    _print(root->left, indent, false);
    _print(root->right, indent, true);
  }
}

void RBT::Print() {
  if (GetRoot() != NULL)
    _print(GetRoot(), "", true);
}
