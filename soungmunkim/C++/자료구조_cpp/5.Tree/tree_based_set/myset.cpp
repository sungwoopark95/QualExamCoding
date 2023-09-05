#include "myset.h"

void MySet::Insert(int data) {
  // TODO: insert 'data' into set
  if(Find(data) == false){
    BST::Insert(data);
  }
}

void MySet::Erase(int data) {
  // TODO: erase 'data' from set
  Node* del = Search(GetRoot(), data);
  Delete(del);
}

bool MySet::Find(int data) {
  // TODO: return true if 'data' exists in the set
  if(Search(GetRoot(), data) == NULL) {
    return false;
  }
  return true;
}

size_t MySet::Size() {
  int size_t;
  // TODO: return number of elements in the set
  int min = BST::Minimum(BST::GetRoot())->key;
  int max = BST::Maximum(BST::GetRoot())->key;
  for (int i=min; i<=max; i++){
    BST::Node* target = BST::Search(BST::GetRoot(), i);
      if (target != NULL) size_t++;
  }
  return size_t;
}