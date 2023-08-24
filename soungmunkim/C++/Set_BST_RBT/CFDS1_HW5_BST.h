/*
binary tree (작은 값: left subtree, 큰 값: right subtree) 에서 search 하는 알고리즘
    모든 노드가 left, right, p(value)를 가지고 있음

< Methods >
1. insert
2. delete
    transplant
3. traversal
    preorder (subtrees 프린트 전에 root print
    inorder(left subtrees -> root -> right subtrees) 
    postorder(subtrees 프린트 한 후 root print)
4. search
5. successor / presuccessor
    maximum / minimum
7. print
    get root (root node 반환 함수)
*/


#pragma once

#include <string>

// BST(Binary Search Tree) 클래스를 정의합니다.
class BST {
public:
  // 중첩된 Node 클래스를 정의합니다.
  class Node {
  public:
    // 생성자: 키 값을 인수로 받아 Node 객체를 초기화합니다.
    Node(int key) {
      this->key = key;     // 현재 객체의 key에 인수로 받은 key 값을 할당합니다.
      this->parent = NULL; // 부모 노드를 NULL로 초기화합니다.
      this->left = NULL;   // 왼쪽 자식 노드를 NULL로 초기화합니다.
      this->right = NULL;  // 오른쪽 자식 노드를 NULL로 초기화합니다.
    }
  
    int key;        // 노드의 키 값을 저장합니다.
    Node* parent;   // 부모 노드에 대한 포인터입니다.
    Node* left;     // 왼쪽 자식 노드에 대한 포인터입니다.
    Node* right;    // 오른쪽 자식 노드에 대한 포인터입니다.
  };

  // 기본 생성자: BST 객체를 초기화합니다.
	BST() : root(NULL) {};

  // 키 값을 이진 탐색 트리에 삽입하는 함수입니다.
	void Insert(int key);
  // 지정된 노드를 이진 탐색 트리에서 삭제하는 함수입니다.
  void Delete(Node* z);

  // 이진 탐색 트리를 전위 순회하는 함수입니다.
	void Preorder(Node* node);
  // 이진 탐색 트리를 중위 순회하는 함수입니다.
	void Inorder(Node* node);
  // 이진 탐색 트리를 후위 순회하는 함수입니다.
	void Postorder(Node* node);

  // 지정된 키 값을 가진 노드를 이진 탐색 트리에서 찾는 함수입니다.
	Node* Search(Node* node, int key);

  // 이진 탐색 트리에서 최대 키 값을 가진 노드를 찾는 함수입니다.
	Node* Maximum(Node* node);
  // 이진 탐색 트리에서 최소 키 값을 가진 노드를 찾는 함수입니다.
	Node* Minimum(Node* node);

  // 지정된 노드의 후속자(successor)를 찾는 함수입니다.
	Node* Successor(Node* x);
  // 지정된 노드의 선행자(predecessor)를 찾는 함수입니다.
	Node* Predecessor(Node* x);

  // 이진 탐색 트리의 루트 노드를 반환하는 함수입니다.
	Node* GetRoot() { return root; }

  // 이진 탐색 트리를 출력하는 함수입니다.
	void Print();

private:
  // 두 노드 위치를 교환하는 함수입니다.
  void transplant(Node* u, Node* v);
  // 이진 탐색 트리를 재귀적으로 출력하는 보조 함수입니다.
	void _print(Node* root, std::string indent, bool last);

  // 이진 탐색 트리의 루트 노드에 대한 포인터입니다.
	Node* root;
};
