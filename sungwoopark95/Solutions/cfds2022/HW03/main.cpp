#include <cstdlib>
#include <iostream>
#include "mycode.h"

int main() {
  Square sq(5.0f);
  Equilateral eq(4.0f);

  sq.print();
  eq.print();

  Shape *s1 = &sq;
  Shape *s2 = &eq;

  s1->print();
  s2->print();

  return EXIT_SUCCESS;
}
