/*
* Shape 클래스는 constructor 인자로 integer type 값 x와 y를 입력 받아 member variable인 x pos와 y pos에 대입한다. 
* Shape 클래스는 DrawSelf 라는 virtual member function을 가지고 있으며, Shape 클래스를 상속 받는 모든 클래스들은 해당 function을 구현한다. 
* DrawSelf function은 아무 인자를 받지 않으며 return type은 void 이다. 
* DrawSelf function을 호출 시 ”Draw {도형 종류} at ({member variable x pos}, {member variable y pos})” 메시지를 화면에 출력한다. 출력 예시는 아래의 결과 화면을 참고한다.
*/
#pragma once
#include <string>
using namespace std;

// Fill in here
class Shape {
protected:
    int x_pos;
    int y_pos;
public:
    Shape(int x, int y);
    virtual void DrawSelf();
};

class Point : public Shape {
private:
    string name;
public:
    Point(int x, int y);
    void DrawSelf();
};

class Line : public Shape {
private:
    string name;
public:
    Line(int x, int y);
    void DrawSelf();
};

class Triangle : public Shape {
private:
    string name;
public:
    Triangle(int x, int y);
    void DrawSelf();
};

class Equilateral : public Triangle {
private:
    string name;
public:
    Equilateral(int x, int y);
    void DrawSelf();
};

class Isosceles : public Triangle {
private:
    string name;
public:
    Isosceles(int x, int y);
    void DrawSelf();
};

class Scalene : public Triangle {
private:
    string name;
public:
    Scalene(int x, int y);
    void DrawSelf();
};

class Quadrilateral : public Shape {
protected:
    string name;
public:
    Quadrilateral(int x, int y);
    void DrawSelf();
};

class Rectangle : public Quadrilateral {
public:
    Rectangle(int x, int y);
    void DrawSelf();
};

class Square : public Quadrilateral {
public:
    Square(int x, int y);
    void DrawSelf();
};
