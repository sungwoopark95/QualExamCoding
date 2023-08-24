/*
[Bears 관련하여 Class 만들기] this 사용한 것!!! (답)
Three different types of bears, Polar bear, Grizzly and Black bear

a) Instead of meanness, now calculate aggressiveness. 
    The degree of aggressiveness is weight * x, where x=1, 0.9, 0.7 for Polar, Grizzly and Black bears, respectively.
b) Consider a black mommabear, which can have two cubs as max. 
    When there are cubs, the ag- gressiveness becomes twice.
c) Total aggressiveness of mommabear 
    which can be calculated as the sum of the aggressiveness of mommabear and cubs.
d) As same as in the bear example, the bear class have 
    a. Weight (member variable)
    b. GetWeight 
    c. SetWeight
e) Additionally, have
    a. void PrintSelf(void)
    b. void AddCub(Bear *aCub) (Mommabear only, add cubs)
f) PrintSelf prints
     I am {Bear type}, Weight={weight}, Aggressiveness={aggressiveness}
or (in the case of mommabear)
     I am {Bear type} with {# of cubs} cub(s), Weight={weight},
     Aggressiveness={aggressiveness}, Total Aggressiveness={totalaggressiveness}
*/

#include "CFDS2_HW1_Bears.h"
#include <iostream>
/*** Constructor ***/
Bear::Bear(float aWeight) {
    weight = aWeight; // 생성자에서 전달받은 무게를 멤버 변수에 할당
}

/*** Accessors ***/
void Bear::SetWeight(float aWeight) {
    weight = aWeight; // 멤버 함수를 통해 무게를 설정
}

float Bear::GetWeight(void) {
    return(weight); // 멤버 함수를 통해 현재 무게를 반환
}

/*--------------Subclasses-----------------*/
/*** Polar Bear ***/
Polar::Polar(float aWeight) : Bear(aWeight) {}; // Polar 베어의 생성자. Bear의 생성자를 호출하여 초기화

float Polar::Aggressiveness(void){
    return weight * 1.0; // 폴라 베어의 공격성은 무게에 1.0을 곱한 값
}

void Polar::PrintSelf(void){
    // 폴라 베어의 정보 출력
    printf("I am Polar bear, Weight=%.0f, Aggressiveness=%.0f\n",
    this -> weight,
    this -> Aggressiveness());
}

/*** Grizzly Bear ***/
Grizzly::Grizzly(float aWeight) : Bear(aWeight) {} // 그리즐리 베어의 생성자

float Grizzly::Aggressiveness(void) {
    return weight * 0.9; // 그리즐리 베어의 공격성은 무게에 0.9를 곱한 값
}

void Grizzly::PrintSelf(void){
    // 그리즐리 베어의 정보 출력
    printf("I am Grizzly bear, Weight=%.0f, Aggressiveness=%.0f\n", 
    this -> weight,
    this -> Aggressiveness());
}

/*** Black Bear ***/
Black::Black(float aWeight) : Bear(aWeight) {} // 블랙 베어의 생성자

float Black::Aggressiveness(void){
    return weight * 0.7; // 블랙 베어의 공격성은 무게에 0.7을 곱한 값
}

void Black::PrintSelf(void){
    // 블랙 베어의 정보 출력
    printf("I am Black bear, Weight=%.0f, Aggressiveness=%.0f\n",
    this->weight,
    this->Aggressiveness());
}

/*--------------Black Mommabear-----------------*/
/*** Constructor ***/
Black_Momma::Black_Momma(float aWeight) : Black(aWeight) {
    num_cub = 0; // 새로운 블랙 맘마 베어는 아기 베어가 없으므로 0으로 초기화
    cubAggressiveness = 0.0; // 아기 베어의 공격성도 0으로 초기화
}

void Black_Momma::AddCub(Bear *aCub){
    num_cub += 1; // 아기 베어 추가시 개수 증가
    cubAggressiveness += aCub -> Aggressiveness(); // 아기 베어의 공격성을 더함
}

float Black_Momma::Aggressiveness(void){
    return(Black::Aggressiveness() * 2); // 블랙 맘마 베어의 공격성은 블랙 베어의 두 배
}

float Black_Momma::TotalAgressiveness(void){
    // 블랙 맘마 베어와 그의 아기 베어들의 총 공격성을 반환
    return ( this -> Aggressiveness() + cubAggressiveness);
}

void Black_Momma::PrintSelf(void){
    // 블랙 맘마 베어의 정보와 그의 아기 베어들의 정보를 출력
    printf("I am Black Mommabear with %d cub(s), Weight=%.0f, Aggressiveness=%.0f, Total Aggressiveness=%.0f\n",
    this -> num_cub,
    this -> weight,
    this -> Aggressiveness(),
    this -> TotalAgressiveness());
}
