#include <cstdlib>
#include <iostream>
#include "bst.h"

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
