#include <iostream>
#include "shapes.h"
using namespace std;

// Fill in here
Shape::Shape(int x, int y) {
    x_pos = x;
    y_pos = y;
}

void Shape::DrawSelf() {}

Point::Point(int x, int y) : Shape(x, y) {
    // 상속받은 superclass의 생성자는 : superclass(item)으로 해주어야
    name = "Point";
}

void Point::DrawSelf() {
    cout << "Draw " << name << " at (" << x_pos << ", " << y_pos << ")" << endl;
}

Line::Line(int x, int y) : Shape(x, y) {
    // 상속받은 superclass의 생성자는 : superclass(item)으로 해주어야
    name = "Line";
}

void Line::DrawSelf() {
    cout << "Draw " << name << " at (" << x_pos << ", " << y_pos << ")" << endl;
}

Triangle::Triangle(int x, int y) : Shape(x, y) {
    // 상속받은 superclass의 생성자는 : superclass(item)으로 해주어야
    name = "Triangle";
}

void Triangle::DrawSelf() {
    cout << "Draw " << name << " at (" << x_pos << ", " << y_pos << ")" << endl;
}

Equilateral::Equilateral(int x, int y) : Triangle(x, y) {
    name = "Equilateral";
}

void Equilateral::DrawSelf() {
    cout << "Draw " << name << " at (" << x_pos << ", " << y_pos << ")" << endl;
}

Isosceles::Isosceles(int x, int y) : Triangle(x, y) {
    name = "Isosceles";
}

void Isosceles::DrawSelf() {
    cout << "Draw " << name << " at (" << x_pos << ", " << y_pos << ")" << endl;
}

Scalene::Scalene(int x, int y) : Triangle(x, y) {
    name = "Scalene";
}

void Scalene::DrawSelf() {
    cout << "Draw " << name << " at (" << x_pos << ", " << y_pos << ")" << endl;
}

Quadrilateral::Quadrilateral(int x, int y) : Shape(x, y) {
    name = "Quadrilateral";
}

void Quadrilateral::DrawSelf() {
    cout << "Draw " << name << " at (" << x_pos << ", " << y_pos << ")" << endl;
}

Rectangle::Rectangle(int x, int y) : Quadrilateral(x, y) {
    name = "Rectangle";
}

void Rectangle::DrawSelf() {
    cout << "Draw " << name << " at (" << x_pos << ", " << y_pos << ")" << endl;
}

Square::Square(int x, int y) : Quadrilateral(x, y) {
    name = "Square";
}

void Square::DrawSelf() {
    cout << "Draw " << name << " at (" << x_pos << ", " << y_pos << ")" << endl;
}
