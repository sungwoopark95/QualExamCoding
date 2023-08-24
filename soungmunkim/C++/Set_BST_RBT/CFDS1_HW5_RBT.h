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
*/

#pragma once

#include <string>

// node의 색상을 나타내는 열거형 (빨간색 또는 검은색)
enum Color {
  COLOR_BLACK,
  COLOR_RED
};

// RBT (Red-Black Tree) 클래스를 정의합니다.
class RBT {
public:
  // 중첩된 Node 클래스를 정의합니다.
  class Node {
  public:
    // 생성자: 주어진 매개변수로 Node 객체를 초기화합니다.
    Node(int key, Node* parent, Node* left, Node* right, enum Color color) {
      this->key = key;
      this->parent = parent;
      this->left = left;
      this->right = right;
      this->color = color;
    }
  
    int key;        // 노드의 키 값을 저장합니다.
    Node* parent;   // 부모 노드에 대한 포인터입니다.
    Node* left;     // 왼쪽 자식 노드에 대한 포인터입니다.
    Node* right;    // 오른쪽 자식 노드에 대한 포인터입니다.
    enum Color color; // 노드의 색상을 저장합니다.
  };

  // Constructor
  RBT();

  // 주어진 키 값을 트리에 삽입합니다.
  void Insert(int key);
  // 지정된 노드를 트리에서 삭제합니다.
  void Delete(Node* z);

  // 트리를 전위 순회하는 함수입니다.
	void Preorder(Node* node);
  // 트리를 중위 순회하는 함수입니다.
	void Inorder(Node* node);
  // 트리를 후위 순회하는 함수입니다.
	void Postorder(Node* node);

  // 지정된 키 값을 가진 노드를 찾습니다.
  Node* Search(Node* node, int key);

  // 트리에서 최대 키 값을 가진 노드를 찾습니다.
  Node* Maximum(Node* node);
  // 트리에서 최소 키 값을 가진 노드를 찾습니다.
  Node* Minimum(Node* node);

  // 지정된 노드의 후속자를 찾습니다.
  Node* Successor(Node* x);
  // 지정된 노드의 선행자를 찾습니다.
  Node* Predecessor(Node* x);

  // 루트 노드를 반환하는 함수입니다.
  Node* GetRoot() { return this->root; }

  // 트리를 시각적으로 출력하는 함수입니다.
  void Print();

private:
  Node* root;  // 트리의 루트 노드에 대한 포인터입니다.
  Node* Tnil;  // NIL 노드를 나타내는 포인터입니다. (트리의 끝을 표시)

  // 삽입 후 트리의 균형을 유지하기 위해 색상을 조정하고 필요한 경우 회전을 수행합니다.
  void InsertFixUp(Node* k);
  // 지정된 노드를 기준으로 왼쪽 회전을 수행합니다.
  void LeftRotate(Node* x);
  // 지정된 노드를 기준으로 오른쪽 회전을 수행합니다.
  void RightRotate(Node* x);
  // 삭제 후 트리의 균형을 유지하기 위해 색상을 조정하고 필요한 경우 회전을 수행합니다.
  void DeleteFixUp(Node* x);
  // 두 노드의 위치를 교환합니다.
  void Transplant(Node* u, Node* v);

  // 트리를 시각적으로 출력하는 보조 함수입니다.
  void _print(Node* root, std::string indent, bool last);
};
