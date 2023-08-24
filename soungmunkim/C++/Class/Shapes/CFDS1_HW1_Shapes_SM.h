/*
[Draw shapes: 도형의 class 정의]

도형을 정의하는 shapes.cpp와 shapes.h를 아래와 같은 조건을 만족하도록 작성함.
1. 그림 1에서 아래쪽에 정의된 class는 위쪽에 정의된 class를 상속 받는 class임.
    다시 말해, Shape가 최상위 class이며 그 밑의 Point, Line, Triangle, Quadrilateral은 Shape를 상속 받는 class이다.
    마찬가지로, Equilateral, Isosceles, Scalene은 Triangle를 상속 받는다.
    Rectangle, Squre은 Quadrilateral를 상속 받는다.
2. Shape 클래스는 integer type member variable인 x.pos와 y.pos 가짐
3. Shape 클래스는 constructor  인자로 integer type 값 x와 y를 입력받아 member variable인 x.pos와 y.pos에 대입함
4. Shape 클래스는 DrawSelf 라는 virtual member function을 가지고 있으며, Shape 클래스를 상속 받는 모든 클래스들은 해당 function을 구현함.
5. DrawSelf function은 아무 인자를 받지 않으며 return type은 void.
6. DrawSelf function을 호출 시 "Draw {도형 종류} at ({member variable x.pos}, {member variable y.pos})"
    메시지를 화면에 출력함.
*/
#pragma once // 여러번 copy해서 들어가는 것을 방지하기 위한 것
/*--------- Super Class ----------*/
class Shape{
    public:
    Shape(int x, int y); // Constructor
    virtual void DrawSelf() = 0; //polymorphic method (shapes subclasses)
    
    protected:
    int x_pos;
    int y_pos;
};

/*--------- SubClasses ----------*/
class Point : public Shape {
    public:
    Point(int x, int y) : Shape(x, y) {} // Shape constructor로 pass함

    void DrawSelf();
};

class Line : public Shape {
    public:
    Line(int x, int y): Shape(x, y) {} // Shape constructor로 pass함

    void DrawSelf();
};

class Triangle : public Shape {
    public:
    Triangle(int x, int y): Shape(x, y) {} // Shape constructor로 pass함

    void DrawSelf();
};


class Quadrilateral : public Shape {
    public:
    Quadrilateral(int x, int y): Shape(x, y) {} // Shape constructor로 pass함

    void DrawSelf();
};


class Equilateral : public Triangle {
    public:
    Equilateral(int x, int y): Triangle(x, y) {} // Shape constructor로 pass함

    void DrawSelf();
};

class Isosceles : public Triangle {
    public:
    Isosceles(int x, int y): Triangle(x, y) {}

    void DrawSelf();
};

class Scalene : public Triangle {
    public:
    Scalene(int x, int y): Triangle(x, y) {}

    void DrawSelf();
};

class Rectangle : public Quadrilateral {
    public:
    Rectangle(int x, int y): Quadrilateral(x, y) {}

    void DrawSelf();
};

class Square : public Quadrilateral {
    public:
    Square(int x, int y): Quadrilateral(x, y) {}

    void DrawSelf();
};




