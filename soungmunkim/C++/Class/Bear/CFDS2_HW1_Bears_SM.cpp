/*
[Bears 관련하여 Class 만들기]
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

#include <stdio.h>
#include <cmath>
#include "CFDS2_HW1_Bears_SM.h"

// Constructor
// 처음 instance 생길 때 해당 aWeight 값으로 초기화
Bear::Bear(float aWeight) { 
    Weight = aWeight;
}
// 현재 weight 값 return
float Bear::GetWeight() {
    return (Weight);
}

// ojbect안 변수를 바꾸고 싶을 때 사용 (aWeight값 바꾸고 싶을 때)
void Bear::SetWeight(float aWeight) {
    Weight = aWeight;
}

// Polar Bear 
float Polar::Aggressiveness() {
    return (Weight * 1);
}
void Polar::PrintSelf() {
    printf("I am Polar bear, weight=%.0f, Aggressiveness=%.0f\n", Weight, Aggressiveness());
}

// Grizzly Bear
float Grizzly::Aggressiveness() {
    return (Weight * 0.9);
}
void Grizzly::PrintSelf() {
    printf("I am Grizzly bear, weight=%.0f, Aggressiveness=%.0f\n", Weight, Aggressiveness());
}

// Black Bear
float Black::Aggressiveness() {
    return (Weight * 0.7);
}
void Black::PrintSelf() {
    printf("I am Black bear, weight=%.0f, Aggressiveness=%.0f\n", Weight, Aggressiveness());
}

// Black Mommma Bear
// input받은 aCub을 variable cub에 할당함
void Black_Momma::AddCub(Bear *aCub) {
    cub = aCub;
    // cub이 할당될때마다 cub 개수 늘리고 cub의 공격성 계산해서 추가하기
    num_cub += 1;
    cubAggressiveness += cub->Aggressiveness();

}

Bear* Black_Momma::GetCub() {
    return (cub);
}

// black momma 가  two cubs을 최대로 가짐
// cubs가 있으면 aggressiveness 2배
float Black_Momma::Aggressiveness() {
    return (Black::Aggressiveness() * 2);
}

float Black_Momma::TotalAggressiveness() {

    return (Aggressiveness() + cubAggressiveness);
}

void Black_Momma::PrintSelf() {
    printf("I am Black Mommabear with %d cub(s), Weight=%.0f, Aggressiveness=%.0f, Total Aggressiveness=%.0f\n", num_cub, Weight, Aggressiveness(), TotalAggressiveness());
}