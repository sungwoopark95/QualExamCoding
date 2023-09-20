#pragma once

// Fill in
class Shape {
protected:
    int side;
public:
    Shape(int x);
    virtual float area() = 0; // pure virtual function
    void print();
};

class Square : public Shape {
public:
    Square(int x);
    float area();
    void print();
};

class Equilateral : public Shape {
public:
    Equilateral(int x);
    float area();
    void print();
};
