#pragma once

/*
NewBear
세 가지 다른 종류의 곰을 고려합니다: 폴라 베어, 그리즐리 베어, 블랙 베어.
공격성 순위: 폴라 베어 > 그리즐리 베어 > 블랙 베어
*/

#include <string>

class Bear {
    public:
    // Bear(){}; // 기본 생성자 (현재는 주석 처리되어 있음)
    Bear(float aWeight); // 생성자. 무게를 인자로 받음.

    virtual void PrintSelf(void) = 0; // 순수 가상 함수. 각 서브 클래스에서 구현해야 함.
    void SetWeight(float aWeight); // 무게를 설정하는 멤버 함수
    float GetWeight(void); // 무게를 반환하는 멤버 함수
    virtual float Aggressiveness(void) {
        return 0.0;} // 순수 다형성 메서드. 기본적으로 0.0을 반환하지만, 서브 클래스에서 오버라이드 될 것임.

    protected:
    float weight; // protected로 선언되어 서브 클래스에서 접근 가능. 
                  // Mommabear도 다른 클라이언트처럼 접근자를 사용해야 함.

};

/*--------------Subclasses-----------------*/
// 폴라 베어 클래스
class Polar : public Bear {
    public:
    Polar(float aWeight); // 생성자
   
    float Aggressiveness(void); // 공격성을 반환하는 멤버 함수
    void PrintSelf(); // 정보를 출력하는 멤버 함수
};

// 그리즐리 베어 클래스
class Grizzly : public Bear {
    public:
    Grizzly(float aWeight); // 생성자

    float Aggressiveness(void); // 공격성을 반환하는 멤버 함수
    void PrintSelf(); // 정보를 출력하는 멤버 함수
};

// 블랙 베어 클래스
class Black : public Bear {
    public:
    Black(float aWeight); // 생성자

    float Aggressiveness(void); // 공격성을 반환하는 멤버 함수
    void PrintSelf(); // 정보를 출력하는 멤버 함수
};

/*--------------BlackMommabear-----------------*/
// 블랙 맘마 베어 클래스. 블랙 베어 클래스를 상속받음.
class Black_Momma : public Black {
    public:
    Black_Momma(float aWeight); // 생성자

    void AddCub(Bear *aCub); // 아기 곰을 추가하는 멤버 함수
    virtual float Aggressiveness(void); // 공격성을 반환하는 멤버 함수
    float TotalAgressiveness(void); // 총 공격성을 반환하는 멤버 함수
    void PrintSelf(); // 정보를 출력하는 멤버 함수

    protected:
    int num_cub; // 아기 곰의 수
    float cubAggressiveness; // 아기 곰들의 공격성 합계
};
