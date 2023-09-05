
/*--------------------------- Class Public vs. Private----------------------*/
class MyClass{
    public: // public access specifier
        int x; // public attribute
    private: // private access specifier
        int y; // private attribute
};

int main() {
    MyClass myObj;
    myObj.x = 25; // Allowed (public)
    // myObj.y = 50; // Not allowed (private이어서 접근 못 함)
    return 0;
}
/*--------------------------- Class Box 예제 ----------------------*/
#include <iostream>
using namespace std;

class Box{
    public:
        double length;
        void setWidth(double wid);
        double getWidth(void);
    // protected 여야 subclass에서 접근 가능
    protected: //private:
        double width;
};

// member function definitions (member function 안에서 세팅하는 건 다 괜찮음)
double Box::getWidth(void){
    return width;
}
void Box::setWidth(double wid){
    width = wid;
}

// Main function
int main() {
    Box box;
    // set box length without member function
    box.length = 10.0; // length는 public이므로 접근 가능
    cout << "Length of box: " << box.length << endl;

    // set box width without member fucntion
    // box.width = 10.0; // width는 private이므로 접근이 안 됨
}
/*--------------------------- Subclass SmallBox 예제 ----------------------*/
class SmallBox:Box{ // SmallBox는 Box에서 derived 됨
    public:
        void setSmallWidth(double wid);
        double getSmallWidth(void);
};

// Member functions of child class
double SmallBox::getSmallWidth(void){
    return width;
}

void SmallBox::setSmallWidth(double wid){
    width = wid;
}

int main() {
    SmallBox box;
    box.setSmallWidth(5.0);
    cout << "Width of box: " << box.getSmallWidth() << endl;
}


