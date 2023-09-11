/*
[RBT or BST 알고리즘 이용해서 Set 구현하기]
g++ CFDS1_HW5_MySet_main.cpp CFDS1_HW5_MySet.cpp CFDS1_HW5_BST.cpp CFDS1_HW5_RBT.cpp -o MySet 

main.cpp는 하나만 있어야 함

< OutPut >
Size of the set is 6
Size of the set after inserts and erases is 5
Is number '32' exists in the set ? 0
Is number '22' exists in the set ? 0
Is number '100' exists in the set ? 1
*/

#include <cstdlib>
#include <iostream>
#include "CFDS1_HW5_MySet.h"

int main(int argc, char** argv) {
  MySet myset;

  myset.Insert(3);
  myset.Insert(3);
  myset.Insert(3);
  myset.Insert(7);
  myset.Insert(10);
  myset.Insert(23);
  myset.Insert(22);
  myset.Insert(8);

  std::cout << "Size of the set is " << myset.Size() << std::endl;

  myset.Erase(14);
  myset.Erase(3);
  myset.Erase(22);

  myset.Insert(23);
  myset.Insert(100);

  std::cout << "Size of the set after inserts and erases is "
    << myset.Size() << std::endl;

  std::cout << "Is number '32' exists in the set ? "
    << myset.Find(32) << std::endl;

  std::cout << "Is number '22' exists in the set ? "
    << myset.Find(22) << std::endl;

  std::cout << "Is number '100' exists in the set ? "
    << myset.Find(100) << std::endl;

  return EXIT_SUCCESS;
}