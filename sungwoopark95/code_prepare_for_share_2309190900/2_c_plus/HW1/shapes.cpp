#include "shapes.h"
#include <stdio.h>
#include <typeinfo>

#include <iostream>
// // Fill in here


void Point::DrawSelf(void){ std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")" << std::endl; }
void Line::DrawSelf(void){ std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")" << std::endl; }
void Triangle::DrawSelf(void){ std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")" << std::endl; }
void Quadrilateral::DrawSelf(void){ std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")" << std::endl; }
void Equilateral::DrawSelf(void){ std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")" << std::endl; }
void Isoceles::DrawSelf(void){ std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")" << std::endl; }
void Scalene::DrawSelf(void){ std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")" << std::endl; }
void Rectangle::DrawSelf(void){ std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")" << std::endl; }
void Square::DrawSelf(void){ std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")" << std::endl; }


// class Point : public Shape {
//     public:
//     Point(int x, int y) : Shape(x, y){};
//     void DrawSelf(void) {
//         std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")\n" << std::endl;
//     };
// };

// class Line : public Shape {
//     public:
//     Line(int x, int y) : Shape(x, y){};
//     void DrawSelf(void) {
//         std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")\n" << std::endl;
//     };
// };

// class Triangle : public Shape {
//     public:
//     Triangle(int x, int y) : Shape(x, y){};
//     void DrawSelf(void) {
//         std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")\n" << std::endl;
//     };
// };

// class Quadrilateral : public Shape {
//     public:
//     Quadrilateral(int x, int y) : Shape(x, y){};
//     void DrawSelf(void) {
//         std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")\n" << std::endl;
//     };
// };

// class Equilateral : public Triangle {
//     public:
//     Equilateral(int x, int y) : Triangle(x, y){};
//     void DrawSelf(void) {
//         std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")\n" << std::endl;
//     };
// };

// class Isosceles : public Triangle {
//     public:
//     Isosceles(int x, int y) : Triangle(x, y){};
//     void DrawSelf(void) {
//         std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")\n" << std::endl;
//     };
// };

// class Scalene : public Triangle {
//     public:
//     Scalene(int x, int y) : Triangle(x, y){};
//     void DrawSelf(void) {
//         std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")\n" << std::endl;
//     };
// };

// class Rectangle : public Quadrilateral {
//     public:
//     Rectangle(int x, int y) : Quadrilateral(x, y){};
//     void DrawSelf(void) {
//         std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")\n" << std::endl;
//     };
// };

// class Square : public Quadrilateral {
//     public:
//     Square(int x, int y) : Quadrilateral(x, y){};
//     void DrawSelf(void) {
//         std::cout << "Draw " << typeid(*this).name() << " at (" << this->x_pos << ", " <<y_pos<< ")\n" << std::endl;
//     };
// };