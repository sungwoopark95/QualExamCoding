/*
[Shapes의 area 구하기]

1. Shape 클래스는 single-precision floating-point number 1개를 
    constructor의 Input으로 받음 (도형 한 변의 길이)
2. Shape 클래스는 single-precision floating-point type을 return하는
    area라는 virtual 함수를 가짐
3. Sqaure 클래스와 Equilateral 클래스는 Shape 클래스를 상속받음
4. print 함수는 앞서 정의한 area 함수를 이용하여 문자열 출력함

area of square = (side)^2
area of equilatera = sqrt(3/4) * (side)^2

[output]
>>> g++ CFDS1_HW3_Polymorphism_main.cpp CFDS1_HW3_Polymorphism_SM.cpp -o Polymorphism
>>> ./Polymorphism                                                                   
This is Square. Area is 0.250000
This is Equilateral. Area is 6.928203
This is Square. Area is 0.250000
This is Equilateral. Area is 6.928203
*/

#include <iostream>
#include <cmath>
#include "CFDS1_HW3_Polymorphsim_SM.h"

/*** Constructor ***/
Shape :: Shape(float length) {
    side = length; // member variable인 one_length에 넣기
}

float Square :: area() {
    float sq_ans = pow(side, 2);

    return sq_ans;
}

void Square :: print() {
    printf("This is Square. Area is %f\n", area());
}

float Equilateral :: area() {
    float eq_ans = (sqrt(3)/4) * pow(side, 2);
    
    return eq_ans;
}

void Equilateral :: print() {
    printf("This is Equilateral. Area is %f\n", area());
}

