#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "shapes.h"
#include <typeinfo>

using namespace std;

int main() {
  Shape* s1 = new Square(2, -4);
  Rectangle* s2 = new Rectangle(17, 3);
  Triangle* s3 = new Isoceles(4, 4);
  Shape* s4 = new Line(-4, 10);
  Shape* s5 = new Triangle(8, -30);
  Point* s6 = new Point(0, 0);

  s1->DrawSelf();
  s2->DrawSelf();
  s3->DrawSelf();
  s4->DrawSelf();
  s5->DrawSelf();
  s6->DrawSelf();

  delete s1;
  delete s2;
  delete s3;
  delete s4;
  delete s5;
  delete s6;

  return EXIT_SUCCESS;
}
