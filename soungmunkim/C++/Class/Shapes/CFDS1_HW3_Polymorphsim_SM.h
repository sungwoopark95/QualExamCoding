#pragma once
/*--------- Super Class ----------*/
class Shape{
    public:
    Shape(float length); // Constructor

    // area는 이미 member variable side에 접근 가능함
    virtual float area() = 0; // Polymorphism
    
    // shape일 때에도 Print가 되어야 함 (기본 세팅에서)
    // 따라서, pure virtual이 아닌 그냥 virtual 사용해야 함
    virtual void print() {
        printf("This is Shape. Area is %f\n", area());
    }; // Polymorphism
    
    protected:
    float side;
};

/*--------- SubClasses ----------*/
class Square : public Shape{
    public:
    Square(float length) : Shape(length) {} // Shape constructor로 패스

    float area();
    void print();
};

class Equilateral : public Shape{
    public:
    Equilateral(float length) : Shape(length) {} // Shape constructor로 패스

    float area();
    void print();
};

