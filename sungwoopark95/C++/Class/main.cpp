#include <cstdlib>
#include <iostream>
#include "mycode.h"

int main() {
  Square sq(5.0f);
  Equilateral eq(4.0f);

  sq.print(); // This is Square. Area is 25.000000
  eq.print(); // This is Equilateral. Area is 6.928203

  Shape *s1 = &sq;
  Shape *s2 = &eq;

  s1->print(); // This is Shape. Area is 25.000000
  s2->print(); // This is Shape. Area is 6.928203

  return EXIT_SUCCESS;
}
