#include <cstdlib>
#include <iostream>
#include <math.h>
#include "mycode.h"
using namespace std;

// Fill in
Shape::Shape(int x) {
    side = x;
}

void Shape::print() {
    printf("This is Shape. Area is %.6f\n", this->area());
}

// virtual function -> superclass의 pointer로 subclass를 가리키면, subclass의 것을 그대로 따라감
// non-virtual function -> superclass의 pointer로 subclass를 가리키면 superclass의 것을 따라감

Square::Square(int x) : Shape(x) {}

float Square::area() {
    return (side * side);
}

void Square::print() {
    printf("This is Square. Area is %.6f\n", this->area());
}

Equilateral::Equilateral(int x) : Shape(x) {}

float Equilateral::area() {
    return (sqrt(3) / 4) * (side * side);
}

void Equilateral::print() {
    printf("This is Equilateral. Area is %.6f\n", this->area());
}
