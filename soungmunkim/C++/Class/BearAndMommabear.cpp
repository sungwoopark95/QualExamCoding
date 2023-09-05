#include <iostream>

/*---------------------- Bear Header file -------------------------*/
/*
현재 source file이 여러번 copy되어 들어갈 수 있기 때문에 그걸 방지하기 위해 사용
*/
// #pragma once 

class Bear {
    public:
        Bear(float aWeight); // Overloading constructor
        
        void SetWeight(float aWeight); // Weight
        float GetWeight(void); // accessors (member 변수의 값을 반환)

        /*
        virtual -> polymorphism 일 때 사용함
        polymorphism -> method 이름은 같지만 behavior은 다른 것
        어떤 class에 있는지에 따라 다르게 적용 됨
        여기서는 Meanness()가 bear에서는 weight이었고 mammabear에서는 *2로 동작해야 해서 polymorphism임
        */
        virtual float Meanness(void); // polymorphic

    protected:
        float weight;
};

/*---------------------- Bear cpp file -------------------------*/
#include <stdio.h>
// #include "bear.h"

// object을 생성하는 Operator (return 값 없음)
/*** Constructor ***/
Bear::Bear(float aWeight) { weight = aWeight;} // private weight 변수에 할당

/*** Accessor ***/
// object인 변수 값을 바꾸고 싶을 때 사용
void Bear::SetWeight(float aWeight){
    weight = aWeight;
}
float Bear::GetWeight(void){
    return(weight);
}
/*** Meanness ***/
float Bear::Meanness(void){
    if (weight <= 100)
        return(weight * 2);
    else   
        return(weight * 3);
}

/*---------------------- Mommabear header file -------------------------*/
// #pragma once
// #include "bear.h" // bear class을 상속받아야 하므로 class 구조 담고 있는 header file 가져오기

// 보통 Public으로 상속받음
class Mommabear : public Bear {
    public:
        Mommabear(float aWeight); // constructor
    
    /*
    class pointer:
    class는 설계도이기 때문에 class pointer을 해주면 
    class에 있는 attributes을 다 접근 가능
    */
    void SetCub(Bear *aCub); // Bear type을 갖고 있는 cCub이라는 pointer 변수
    Bear *GetCub(void); // Bear type을 갖고 있는 GetCub pointer 함수
    virtual float Meanness(void); // Meannes method의 behavior가 다르게 동작해야하기 때문

    float TotalMeanness(void);

    protected:
        Bear *cub; // bear class pointer (bear type을 갖고 는 cub pointer 변수)

    public:
        static void TestBears(void); // global function 같은 것
};

/*---------------------- Mommabear cpp file -------------------------*/
// #include <stdio.h>
// #include "mommabear.h"

/*** Constructor ***/
// class :: class member

/* mommabear의 constructor은 bear(float aWeight)와 같게 쓸 거기 때문에 
bear class에 있는 constructor로 넘김
*/
Mommabear::Mommabear(float aWeight) : Bear(aWeight) { // pass along to the Bear constructor
    cub = NULL; // 추가적인 것 (constructor): 처음엔 cub이 없다고 초기화함
}

/*** Accessors ***/
// bear type을 가지고 있는 Pointer cub을 반환할 것 
// (외부에서 얻은 bear type인 aCub의 주소를 얻게 됨)
Bear* Mommabear::GetCub(void){
    return cub;
}

// 외부에 있는 bear type인 aCub의 주소를 Pointer variable인 cub에 저장함
void Mommabear::SetCub(Bear *aCub){
    cub = aCub;
}

/*** Meanness ***/
/* Use the inherited meanness and then multiply by 2 */
// bear class에 있는 meanness method을 불러와서 곱하기 2하는 것
float Mommabear::Meanness(void){
    return Bear::Meanness() * 2;
}

/* The totalMeanness is just the mom's meanness + the cub's */
float Mommabear::TotalMeanness(void){
    float cubMeanness;
    if (cub != NULL)
        // cub은 pointer variable + bear type이니까 bear 안에 있는 Meanness()에 접근하여 가져옴
        cubMeanness = cub -> Meanness();
    else 
        cubMeanness = 0.0;
    return Meanness() + cubMeanness; // 엄마 Meanness + cub Meanness
}

void Mommabear::TestBears(void){
    Bear* cub;                 // bear type인 cub pointer variable 만들기
    Mommabear* mom;            // mommabear type인 mom pointer variable 만들기
    cub = new Bear(50);        // bear type인 cub pointer variable이 Bear(50) 가르킴 (즉 Bear weight가 50 저장)
    mom = new Mommabear(300);  // mommabear type인 mom pointer variable이 mommabear(300)을 가르킴

    printf("%g\n", cub->Meanness()); // bear class 안에 있는 Meanness()에 접근하여 cub이 저장한 weight 50이 반영된 결과가 나옴
    /* prints 50*2 - 100 (실수 프린트하기 위해)*/
    printf("%g\n", mom->Meanness()); // bear class 안에 있는 Meanness()에 접근하여 mom이 저장한 weight 300이 반영된 결과가 나옴
    /* prints 300*3*2 - 1800 (실수 프린트하기 위해)*/

    mom->SetCub(cub);           // mommabear class에 있는 SetCub()에 접근하여 bear type을 갖고 있는 cub 만듦
    cub->SetWeight(75);         // bear type 갖고 있는 cub이 bear class안에 있는 SetWeight()에 접근하여 75 반영한 결과 값 저장
    printf("%g\n", mom->TotalMeanness());
}

/*---------------------- Main cpp file -------------------------*/
// #include "bear.h"
// #include "mommabear.h"

int main(void){
    /*
    static class function으로 global 함수로 만들었기 때문에
    따로
    Mommabear* mom;
    mom = new Mommabear();
    mom->TestBears() 안 해도 사용 가능
    */
    Mommabear::TestBears(); // Invoke the static class function return 0;
}