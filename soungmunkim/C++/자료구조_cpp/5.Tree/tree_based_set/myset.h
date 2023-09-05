#pragma once

#include "bst.h"
#include "rbt.h"

class MySet : public BST {
public:
  void Insert(int data);
  void Erase(int data);
  
  bool Find(int data);
  size_t Size();
};
