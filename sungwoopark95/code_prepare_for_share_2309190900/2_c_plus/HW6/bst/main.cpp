#include <cstdlib>
#include <iostream>
#include "bst.h"

using namespace std;

int main() {
	BST bst;
  bst.Insert(8); cout<<"insert done"<<endl;
  bst.Insert(18);cout<<"insert done"<<endl;
  bst.Insert(5);cout<<"insert done"<<endl;
  bst.Insert(15);cout<<"insert done"<<endl;
  bst.Insert(17);cout<<"insert done"<<endl;
  bst.Insert(25);cout<<"insert done"<<endl;
  bst.Insert(40);cout<<"insert done"<<endl;
  bst.Insert(80);cout<<"insert done"<<endl;

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
