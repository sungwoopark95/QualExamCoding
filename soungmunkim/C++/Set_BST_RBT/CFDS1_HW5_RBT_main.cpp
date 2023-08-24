/* [RBT 구현]
g++ CFDS1_HW5_RBT_main.cpp CFDS1_HW5_RBT.cpp -o RBT

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

#include <cstdlib>
#include <iostream>
#include "CFDS1_HW5_RBT.h"

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