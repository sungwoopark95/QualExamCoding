#pragma once

// Fill in
class Shape {
  protected :
  float len;
  public :
  Shape(int x) : len(x) {};
  virtual float area()=0;
  void print();
};

class Square : public Shape {
    public :
    Square(int x) : Shape(x){};
    float area();
    void print();
};

class Equilateral : public Shape{
    public :
    Equilateral(int x) : Shape(x){};
    float area();
    void print();

};