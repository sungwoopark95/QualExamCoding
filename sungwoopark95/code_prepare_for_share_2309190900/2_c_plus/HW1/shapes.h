#pragma once

// Fill in here
#include "shapes.h"
#include <stdio.h>
#include <typeinfo>

#include <iostream>
// Fill in here
using namespace std;

class Shape {
    protected:
    int x_pos;
    int y_pos;

    public:
    Shape();
    Shape(int x, int y) : x_pos(x), y_pos(y){};
    virtual void DrawSelf(void)=0;
};


class Point : public Shape {
    public:
    Point(int x, int y) : Shape(x, y){};
    void DrawSelf(void);
};

class Line : public Shape {
    public:
    Line(int x, int y) : Shape(x, y){};
    void DrawSelf(void);
};

class Triangle : public Shape {
    public:
    Triangle(int x, int y) : Shape(x, y){};
    void DrawSelf(void);
};

class Quadrilateral : public Shape {
    public:
    Quadrilateral(int x, int y) : Shape(x, y){};
    void DrawSelf(void);
};

class Equilateral : public Triangle {
    public:
    Equilateral(int x, int y) : Triangle(x, y){};
    void DrawSelf(void);
};

class Isoceles : public Triangle {
    public:
    Isoceles(int x, int y) : Triangle(x, y){};
    void DrawSelf(void);
};

class Scalene : public Triangle {
    public:
    Scalene(int x, int y) : Triangle(x, y){};
    void DrawSelf(void);
};

class Rectangle : public Quadrilateral {
    public:
    Rectangle(int x, int y) : Quadrilateral(x, y){};
    void DrawSelf(void);
};

class Square : public Quadrilateral {
    public:
    Square(int x, int y) : Quadrilateral(x, y){};
    void DrawSelf(void);
};