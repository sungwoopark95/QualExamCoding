#include <stdio.h>
#include <stdlib.h>
#include "instructor.h"
#include <typeinfo>

#define NUM_INS (10)

Instructor::Instructor(void){
    unreadMail = 0;
    age = 0;
    eccentricities = 0;
}

int Instructor::Stress(void){
    int stress = unreadMail;
    if (stress > 1000 ){
        stress = 1000;
    }
    return stress;
}

int Instructor::Respect(void){
    int respect = age - eccentricities;
    if (respect <0){
        respect=0;
    }
    return respect;
}

void Instructor::GetMail(int amt){
    unreadMail+=amt;    

    if (rand()%100<10){
        if (rand()%2==0) {
            eccentricities+=1;
        }
        else {
            eccentricities-=1;
        }
    }
    if (Stress()>Respect()){
    this->Cope(); //is it woring?
    }
}

int Instructor::checkMail(void){
    return unreadMail;
}


class Faculty : public Instructor{

    public :
    Faculty(void);
    int Respect(void);
    void Cope(void);
};

Faculty::Faculty(void):Instructor(){
    age = 50;
}

int Faculty::Respect(void){
    return (age+eccentricities);
}

void Faculty::Cope(void) {
    eccentricities+=10;
}



class Lecturer : public Instructor{
    public :
    Lecturer(void);
    void Cope(void);
};

Lecturer::Lecturer(void):Instructor(){
    age=40;
}

void Lecturer::Cope(void){
    unreadMail/=2;
} 


class Grad : public Instructor{
    public :
    Grad(void);
    int Stress(void);
    void Cope(void);   
};

Grad::Grad(void):Instructor(){
    age=30;
}

int Grad::Stress(void){
    return (2*Instructor::Stress());
}

void Grad::Cope(void){
    unreadMail=0;
    if (rand()%2==0) {
        eccentricities+=1;
    }
    else {
        eccentricities-=1;
    }
}



static int RandomNum(int num){
    return (rand()%num); //0~num-1사이의 값으로 한정
}

static Instructor* RandomInstructor(void) {
    switch (RandomNum(3)) {
        case 0: return(new Faculty);
                break;
        case 1: return(new Lecturer);
                break;
        case 2: return(new Grad);
                break;
    }
    return(0);
}

void Instructor::Test(void){
    
    Instructor* instructors[NUM_INS]; //각각의 element가 account를 나타내는 포인터
    int insNum;
    int day;

    for (insNum=0; insNum<NUM_INS; insNum++){
        instructors[insNum] = RandomInstructor();
    }

    for (day=1; day<=31; day++){
        insNum=RandomNum(NUM_INS);
        instructors[insNum]->GetMail(day*10);
    }
    for (insNum=0; insNum<NUM_INS; insNum++){
        printf("instructor : %d [%s] Unread: %d, Eccen:%d Stress: %d, Respect: %d\n", 
            insNum, typeid(*instructors[insNum]).name(), instructors[insNum]->unreadMail, instructors[insNum]->eccentricities, instructors[insNum]->Stress(), instructors[insNum]->Respect());
        // printf("account : %d", insNum);
 }
}