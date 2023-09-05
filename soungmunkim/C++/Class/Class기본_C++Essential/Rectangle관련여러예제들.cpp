/*----------- Classes example (1) Constructor vs. Default Constructor --------------*/
#include <iostream>
using namespace std;

class Rectangle {
    int width, height; // member variable (private)
    public:
    // public member functions
        Rectangle (); // default constructor (따로 constructor 설정할 경우 쓰고싶으면 이렇게 따로 설정해줘야함)
        Rectangle (int, int); // constructor
        int area() {return width * height;}
};

Rectangle::Rectangle (int a, int b){
    width = a;
    height = b;
}

Rectangle::Rectangle () {
    width = 5;
    height = 5;
}

int main() {
    Rectangle rect (3,4);
    Rectangle rectb;

    cout << "rect area: " << rect.area() << endl; // 12
    cout << "rectb area: " << rectb.area() << endl; // 25(default constructor로 계산됨)
    return 0;
}

/*----------- Classes example (2) Member Initialization --------------*/
#include <iostream>
using namespace std;

class Circle{
    double radius;
    public:
        Circle(double r) : radius(r) {} // constructor with Input으로 받은 r로 radius member 변수 초기화
        double area() {return radius*radius*3.14159265;}
};

class Cylinder{
    Circle base; //base라는 Circle instance를 만듦(base에 r을 넘겨줘야 함)
    double height; // Cylinder의 member 변수
    public: 
        // Cylinder constructor (r을받아 Circle base 초기화 + h를 받아서 height 초기화)
        Cylinder(double r, double h) : base(r), height(h) {}
        double volume() {return base.area() * height;}
};

int main() {
    Cylinder foo (10,20);
    cout << "foo's volum: " << foo.volume() << '\n'; // foo's volume: 6283.19
    return 0;
}

/*----------- Classes example (3) Friend functions --------------*/
#include <iostream>
using namespace std;

class Rectangle {
    int width, height;
    public:
        Rectangle() {} // default constructor
        Rectangle (int x, int y) : width(x), height(y) {} // constructor
        int area() {return width * height;}
        /*
        duplicate라는 함수에 Rectangle 클래스의 private 및 protected 멤버에 대한 
        직접적인 접근 권한을 부여하는 선언
        */
        friend Rectangle duplicate (const Rectangle&);
};

Rectangle duplicate (const Rectangle& param){
    Rectangle res; 
    // private이어도 friend 함수이기때문에 바로 이렇게 접근 가능
    res.width = param.width*2;
    res.height = param.height*2;
    return res;
}

int main() {
    Rectangle foo;
    Rectangle bar (2,3);
    foo = duplicate(bar);
    cout << foo.area() << '\n'; //24
    return 0;
}

/*----------- Classes example (4) Friend Class --------------*/
#include <iostream>
using namespace std;

class Square;

class Rectangle{
    int width, height;
    public:
        int area() {return (width * height);}
        void convert (Square a);
};

class Square{
    friend class Rectangle; // Rectangle의 friend class 선언
    private:
        int side;
    public:
        Square(int a) : side(a) {} // constructor
};

void Rectangle::convert (Square a){
    // Rectangle class의 member인 convert 함수인데 
    // Square의 private 변수인 side에 접근 가능 (friend class여서)
    width = a.side;
    height = a.side;
}

int main() {
    Rectangle rect;
    Square sqr (4);
    rect.convert(sqr);
    cout << rect.area(); // 16
    return 0;
}

/*----------- Classes example (5) Sub classes (상속 받는 것 예제) --------------*/
#include <iostream>
using namespace std;

class Polygon {
    protected:
        int width, height;
    public:
        void set_values(int a, int b){
            width = a; height = b;
        }
};

// Polygon 상속받을 subclass인 Rectangle
class Rectangle : public Polygon {
    public:
        int area() {return width * height;}
};
// Polygon 상속받을 subclass인 Triangle
class Triangle: public Polygon{
    public:
        int area() {return width * height / 2;}
};

int main() {
    Rectangle rect;
    Triangle trgl;
    rect.set_values(4,5);
    trgl.set_values(4,5);
    cout << rect.area() << '\n'; //20
    cout << trgl.area() << '\n'; //10

    return 0;
}

/*----------- Classes example (6) Multiple inheritance (상속 받는 것 예제) --------------*/
#include <iostream> // 표준 입력/출력을 위한 라이브러리 포함
using namespace std; // std 네임스페이스 사용 선언. 이를 통해 std::cout 등을 cout으로 간단하게 사용할 수 있음.

// 다각형 클래스 선언
class Polygon {
  protected: // 상속받은 클래스에서만 접근 가능한 멤버 변수들
    int width, height; // 다각형의 너비와 높이를 저장할 변수

  public: // 외부에서도 접근 가능한 멤버 함수들
    // 너비와 높이 값을 설정하는 함수
    void set_values (int a, int b)
      { width=a; height=b; }
};

// 사각형 클래스 선언. Polygon 클래스를 상속 받음.
class Rectangle: public Polygon {
  public: 
    // 사각형의 넓이를 계산하여 반환하는 함수
    int area()
      { return width*height; }
};

// 삼각형 클래스 선언. Polygon 클래스를 상속 받음.
class Triangle: public Polygon {
  public:
    // 삼각형의 넓이를 계산하여 반환하는 함수
    int area()
      { return width*height/2; } 
};

int main () { // 메인 함수 시작
  Rectangle rect; // 사각형 객체 생성
  Triangle trgl; // 삼각형 객체 생성
  
  // Polygon 포인터를 사용하여 사각형 객체의 주소를 저장
  Polygon * ppoly1 = &rect;
  // Polygon 포인터를 사용하여 삼각형 객체의 주소를 저장
  Polygon * ppoly2 = &trgl;
  
  // 포인터를 통해 사각형 객체의 너비와 높이 설정
  ppoly1->set_values (4,5);
  // 포인터를 통해 삼각형 객체의 너비와 높이 설정
  ppoly2->set_values (4,5);
  
  // 사각형의 넓이를 출력
  cout << rect.area() << '\n';
  // 삼각형의 넓이를 출력
  cout << trgl.area() << '\n';
  
  return 0; // 프로그램 종료. 0 반환.
}

/*----------- Classes example (7) Virtual member (Polymorphism 예제) --------------*/
// virtual members (가상 멤버에 관한 예제)
#include <iostream> // 표준 입력/출력 라이브러리 포함
using namespace std; // std 네임스페이스 사용 선언

// 다각형 클래스 선언
class Polygon {
  protected: // 상속받은 클래스에서만 접근 가능
    int width, height; // 다각형의 너비와 높이

  public: // 외부에서 접근 가능
    // 너비와 높이 값을 설정하는 함수
    void set_values (int a, int b)
      { width=a; height=b; }
    
    // 가상 함수로 다각형의 넓이를 반환. 기본적으로 0을 반환.
    virtual int area () // virtual 함수 (각 subclass마다 구현이 다름)
      { return 0; }
};

// 사각형 클래스. Polygon 클래스를 상속.
class Rectangle: public Polygon {
  public:
    // 사각형의 넓이를 반환하는 함수. 가상 함수를 오버라이드.
    int area ()
      { return width * height; }
};

// 삼각형 클래스. Polygon 클래스를 상속.
class Triangle: public Polygon {
  public:
    // 삼각형의 넓이를 반환하는 함수. 가상 함수를 오버라이드.
    int area ()
      { return (width * height / 2); }
};

// 메인 함수 시작
int main () {
  Rectangle rect;  // 사각형 객체 생성
  Triangle trgl;   // 삼각형 객체 생성
  Polygon poly;    // 일반 다각형 객체 생성

  // Polygon 포인터를 사용하여 각 객체의 주소 저장
  Polygon * ppoly1 = &rect;
  Polygon * ppoly2 = &trgl;
  Polygon * ppoly3 = &poly;
  
  // 각 포인터를 통해 너비와 높이 설정
  ppoly1->set_values (4,5);
  ppoly2->set_values (4,5);
  ppoly3->set_values (4,5);

  // 각 객체의 넓이를 출력 (virtual 함수의 각 다른 역할)
  cout << ppoly1->area() << '\n'; // 사각형의 넓이 출력
  cout << ppoly2->area() << '\n'; // 삼각형의 넓이 출력
  cout << ppoly3->area() << '\n'; // Polygon의 기본 area() 함수가 호출되어 0 출력
  
  return 0; // 프로그램 종료
}

/*----------- Classes example (8) Dynamic allocation and Polymorphism (Pure Polymorphism 예제) --------------*/
// 동적 할당 및 다형성을 활용한 예제
#include <iostream>   // 표준 입출력 라이브러리를 포함합니다.
using namespace std;  // std 네임스페이스 사용

class Polygon {       // 다각형 클래스 정의
  protected:
    int width, height;  // 보호된 멤버 변수: 너비와 높이
  public:
    // 생성자: 너비와 높이를 초기화합니다.
    Polygon (int a, int b) : width(a), height(b) {}
    
    // pure virtual function: subclasses에서 반드시 구현해야 합니다.
    virtual int area (void) =0;
    
    // 멤버 함수: 면적을 출력합니다.
    void printarea()
      { cout << this->area() << '\n'; }  // 현재 객체의 면적 계산 함수를 호출하여 결과를 출력
};

// 사각형 클래스: 다각형을 상속받습니다.
class Rectangle: public Polygon {
  public:
    // 사각형의 생성자: 다각형의 생성자를 호출하여 너비와 높이를 초기화합니다.
    Rectangle(int a,int b) : Polygon(a,b) {}
    
    // 면적 계산 함수 오버라이드: 사각형의 면적을 반환합니다.
    int area()
      { return width*height; }
};

// 삼각형 클래스: 다각형을 상속받습니다.
class Triangle: public Polygon {
  public:
    // 삼각형의 생성자: 다각형의 생성자를 호출하여 너비와 높이를 초기화합니다.
    Triangle(int a,int b) : Polygon(a,b) {}
    
    // 면적 계산 함수 오버라이드: 삼각형의 면적을 반환합니다.
    int area()
      { return width*height/2; }
};

// 메인 함수
int main () {
  // 다각형 포인터를 사용하여 사각형 객체 dynamic allocation
  Polygon * ppoly1 = new Rectangle (4,5);
  
  // 다각형 포인터를 사용하여 삼각형 객체 dynamic allocation
  Polygon * ppoly2 = new Triangle (4,5);
  
  // 면적을 출력합니다.
  ppoly1->printarea();  // 사각형의 면적을 출력
  ppoly2->printarea();  // 삼각형의 면적을 출력
  
  // 동적으로 할당된 메모리 해제
  delete ppoly1;
  delete ppoly2;
  
  return 0;  // 프로그램 종료
}
