/*
[Shapes의 area 구하기] header, cpp, main.cpp 합쳐놓은 것 (Ans 참고!)

1. Shape 클래스는 single-precision floating-point number 1개를 
    constructor의 Input으로 받음 (도형 한 변의 길이)
2. Shape 클래스는 single-precision floating-point type을 return하는
    area라는 virtual 함수를 가짐
3. Sqaure 클래스와 Equilateral 클래스는 Shape 클래스를 상속받음
4. print 함수는 앞서 정의한 area 함수를 이용하여 문자열 출력함

area of square = (side)^2
area of equilatera = sqrt(3/4) * (side)^2

[output]
>> g++ CFDS1_HW3_Polymorphism.cpp -o CFDS1_HW3_Polymorphism
>> ./CFDS1_HW3_Polymorphism 
This is Square. Area is 0.250000
This is Equilateral. Area is 6.928203
This is Shape. Area is 0.250000
This is Shape. Area is 6.928203
/*--------------- header ---------------*/
#include <cstdlib>
#include <iostream>
#include <math.h>

// superclass
class Shape {
    public: 
        Shape(float x);
        // float x는 전달 받을 필요 없으므로 ()으로 해도 가능 

        virtual float area () = 0; // Pure polymorphism (subclass에만 할당)
        void print();

    protected:
        float side;
};
// subclasses
class Equilateral : public Shape {
    public:
        Equilateral(float x) : Shape(x) {}
        float area();
        void print();
};

class Square : public Shape {
    public:
        Square(float x) : Shape(x) {}
        float area();
        void print();
};

/*--------------- cpp file ---------------*/
Shape :: Shape(float x) {
    side = x;
}

void Shape :: print() {
    printf("This is Shape. Area is %f\n", area());
}

float Equilateral :: area() {
    return sqrt(3.0f) / 4 * side * side;
}

void Equilateral :: print() {
    printf("This is Equilateral. Area is %f\n", area());
}

float Square :: area() {
    return side * side;
}

void Square :: print() {
    printf("This is Square. Area is %f\n", area());
}

/*--------------- main cpp file ---------------*/
int main() {
    Square sq(0.5f);
    Equilateral eq(4.0f);

    sq.print();
    eq.print();

    Shape *s1 = &sq;
    Shape *s2 = &eq;

    s1->print();
    s2->print();

    return EXIT_SUCCESS;
}