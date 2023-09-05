/*
[BST 구현]
g++ CFDS1_HW5_BST_main.cpp CFDS1_HW5_BST.cpp -o BST

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

#include <cstdlib>
#include <iostream>
#include "CFDS1_HW5_BST.h"

using namespace std;

int main() {
	BST bst;
  bst.Insert(8);
  bst.Insert(18);
  bst.Insert(5);
  bst.Insert(15);
  bst.Insert(17);
  bst.Insert(25);
  bst.Insert(40);
  bst.Insert(80);

  cout << "========== Initial BST ==========" << endl;
  bst.Print();

  // find and delete the node whose key is 25
  BST::Node* target = bst.Search(bst.GetRoot(), 25);
  if (target != NULL)
    bst.Delete(target);

  cout << "======= After deleting 25 =======" << endl;
  bst.Print();

	return 0;
}