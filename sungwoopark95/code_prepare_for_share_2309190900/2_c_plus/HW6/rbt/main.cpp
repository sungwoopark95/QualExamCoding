#include <cstdlib>
#include <iostream>
#include "rbt.h"

using namespace std;

int main() {
  RBT rbt;
  rbt.Insert(8);
  rbt.Insert(18);
  rbt.Insert(5);
  rbt.Insert(15);
  rbt.Insert(17);
  rbt.Insert(25);
  rbt.Insert(40);
  rbt.Insert(80);

  cout << "========== Initial RBT ==========" << endl;
  rbt.Print();

  // find and delete the node whose key is 25
  RBT::Node* target = rbt.Search(rbt.GetRoot(), 25);
  if (target != NULL)
    rbt.Delete(target);

  cout << "======= After deleting 25 =======" << endl;
  rbt.Print();

  return 0;
}
