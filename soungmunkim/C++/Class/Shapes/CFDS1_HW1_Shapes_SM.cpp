/*
[Draw shapes; 도형의 class 정의]

도형의 클래스들을 정의하고 각 도형을 입력받은 위치에 그리는 프로그램을 작성하는 것.
도형의 instance를 생성하고 도형을 그리도록 함수를 호출하는 소스 파일인 main.cpp가 제공됨.

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
#include <iostream>
#include "CFDS1_HW1_Shapes_SM.h"
using namespace std;


/*** Constructor ***/
Shape :: Shape(int x, int y){
    x_pos = x; // member variable인 x_pos, y_pos에 넣기
    y_pos = y;
}
// Drawsef()는 polymorphic 하므로 어떤 class를 만났느냐에 따라 output 다르게 설정
void Point :: DrawSelf(){
    printf("Draw %s at (%d, %d)\n", "Point", x_pos, y_pos);
} 

void Line :: DrawSelf(){
    printf("Draw %s at (%d, %d)\n", "Line", x_pos, y_pos);
}

void Triangle :: DrawSelf(){
    printf("Draw %s at (%d, %d)\n", "Triangle", x_pos, y_pos);
}

void Quadrilateral :: DrawSelf(){
    printf("Draw %s at (%d, %d)\n", "Quadrilateral", x_pos, y_pos);
}

void Equilateral :: DrawSelf(){
    printf("Draw %s at (%d, %d)\n", "Equilateral", x_pos, y_pos);
}

void Isosceles :: DrawSelf(){
    printf("Draw %s at (%d, %d)\n", "Isosceles", x_pos, y_pos);
}

void Scalene :: DrawSelf(){
    printf("Draw %s at (%d, %d)\n", "Scalene", x_pos, y_pos);
}

void Rectangle :: DrawSelf(){
    printf("Draw %s at (%d, %d)\n", "Rectangle", x_pos, y_pos);
}

void Square :: DrawSelf(){
    printf("Draw %s at (%d, %d)\n", "Square", x_pos, y_pos);
}