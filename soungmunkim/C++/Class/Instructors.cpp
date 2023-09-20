/* Instructor 관련 class 
3 types of instructors: Faculty, Lecturer, Grad student
    -> 3 quantities: number of unread e-mail messages, age, and number of eccentricities
         -> no unread mail과 no eccentricities로 처음에 초기화해야함
    -> 2 measures of current mood
        1) stress: number of unread messages 
            never more than 1000
            -> Grad students: stress is double of unread messages
                                maximum stress is 2000
        2) respect: age - number of eccentricities
            respect can never be negative
            -> Faculty: age + number of accentricities

1) Unread email increased
2) 90% -> no change in the number of eccentricities
    10% -> number of eccentricities will randomly go up or down by one
3) new unread mail my cause the instructor's Stress factor to become 
    larger than their Respect factor that makes the instructor unhappy
    -> Faculty react by gaining 10 eccentricities
    -> Lecturers react by accidentally deleting half their unread mail
    -> Grad students react by reading all of their unread mail
    -> Grad student's accentricities to go up or down by one randomly
    -> The coping mechanism is activated at most once for each batch of incoming mail
*/

/*---------------------- Instructor Header file -------------------------*/

// 필요한 헤더 파일 포함
#include <stdlib.h>  // 기본 C 라이브러리 함수들을 위한 헤더
#include <iostream>  // 입출력 관련 함수들을 위한 헤더
#include <ctime>

using namespace std;  // 표준 네임스페이스 사용

// 상수 정의
const int kMaxStress = 1000;  // 스트레스 최댓값을 나타내는 상수

// Instructor 클래스 정의 시작
class Instructor {
    public:
        // 생성자 선언
        Instructor(int anAge);  

        // 메서드 선언
        void GetMail(int);  
        virtual int Stress() const;  // 가상 함수
        virtual int Respect() const;  // 가상 함수

        // 정적 멤버 함수 선언
        static void TestOneMonth();

    protected:  
        // 보호된 멤버 변수들
        int unreadMail;  // 읽지 않은 메일의 수
        int age;  // 나이
        int eccentricities;  // 기발함의 정도

        // 보호된 멤버 함수
        void RandomEccentric();  // 기발함의 정도를 조정하는 함수

        // 순수 가상 함수 (추상 클래스를 만들기 위함)
        virtual void Cope() = 0;

    private:
        // private 멤버 함수들 (클래스 외부에서 접근 불가능)
        static Instructor* RandomInstructor();  // 랜덤한 강사 생성 함수
        static int RandomNum(int num);  // 주어진 범위 내의 랜덤 숫자 반환 함수
};

/*---------------------- Instructor cpp file -------------------------*/

// Instructor 클래스의 생성자 정의
Instructor::Instructor(int anAge){
    age = anAge;
    unreadMail = 0;  // 초기값 설정
    eccentricities = 0;  // 초기값 설정
}

// 스트레스를 계산하여 반환하는 함수
int Instructor::Stress() const {
    if (unreadMail <= kMaxStress)
        return unreadMail;
    else
        return kMaxStress;  // 최댓값 제한
}

// 존경받는 정도를 계산하여 반환하는 함수
int Instructor::Respect() const {
    int stress = age - eccentricities;
    if (stress >= 0)
        return stress;
    else
        return 0;  // 최솟값 제한
}

// 메일을 받는 함수. 메일 수에 따라 스트레스 변화 및 다른 행동 발생 가능
void Instructor::GetMail(int numMessages) {
    unreadMail += numMessages;
    if((rand() % 10) == 0)  // 10% 확률
        RandomEccentric();  // 기발함의 정도를 조정
    if(Stress() > Respect())  // 스트레스가 존경받는 정도보다 높으면
        Cope();  // 대처 메서드 호출 (하위 클래스에서 정의됨)
}

// 기발함의 정도를 무작위로 조정하는 함수
void Instructor::RandomEccentric() {
    int delta;

    if((rand() % 2) == 0)  // 50% 확률
        delta = 1;
    else
        delta = -1;

    eccentricities += delta;  // 기발함 조정
    if(eccentricities < 0)
        eccentricities = 0;  // 기발함의 최솟값 제한
}
/******************** sub classess *******************/
/* Grad Student */
// GradStudent 클래스 정의 (Instructor 클래스를 상속받음)
class GradStudent : public Instructor {
    public:
        // 생성자 정의. 부모 클래스의 생성자를 호출
        GradStudent(int anAge) : Instructor(anAge) {}; 

        // 멤버 함수 오버라이드
        int Stress() const;
        void Cope();  
};

// GradStudent 클래스에서의 Stress 함수. 부모 클래스보다 2배의 스트레스를 가짐
int GradStudent::Stress() const {
    return (2 * Instructor::Stress());
}

// GradStudent 클래스에서의 Cope 함수
void GradStudent::Cope() {
    unreadMail = 0;  // 모든 메일을 읽음
    RandomEccentric();  // 기발함의 정도 조정
}

/* Lecturer */
// Lecturer 클래스 정의 (Instructor 클래스를 상속받음)
class Lecturer : public Instructor {
    public:
        // 생성자 정의. 부모 클래스의 생성자를 호출
        Lecturer(int anAge) : Instructor(anAge) {};

        // 멤버 함수 오버라이드
        void Cope();  
};

// Lecturer 클래스에서의 Cope 함수. 읽지 않은 메일의 수를 반으로 줄임
void Lecturer::Cope() {
    unreadMail = unreadMail / 2;
}

/* Professor */
// Professor 클래스 정의 (Instructor 클래스를 상속받음)
class Professor : public Instructor {
    public:
        // 생성자 정의. 부모 클래스의 생성자를 호출
        Professor(int anAge) : Instructor(anAge) {};

        // 멤버 함수 오버라이드
        int Respect() const;
        void Cope();  
};

// Professor 클래스에서의 Respect 함수
int Professor::Respect() const {
    return (age + eccentricities);
}

// Professor 클래스에서의 Cope 함수. 기발함의 정도를 크게 증가
void Professor::Cope() {
    eccentricities += 10;
}

/*---------------------- 추가된 것 -------------------------*/
// 주어진 범위 내의 랜덤 숫자를 반환하는 함수
int Instructor::RandomNum(int num){
    return rand() % num;
}

// 랜덤한 강사 객체를 생성하는 함수
Instructor* Instructor::RandomInstructor() {
    switch (RandomNum(3)) {  // 0, 1, 2 중 랜덤한 숫자 반환
        case 0: return(new GradStudent(RandomNum(30)));
        case 1: return(new Professor(RandomNum(50)));
        case 2: return(new Lecturer(RandomNum(70)));
    }
    return(0);  // 해당사항 없음
}

const int NUMINSTRUCTORS = 100;  // 강사 수를 나타내는 상수

// 한 달간 각 강사의 반응을 시뮬레이션하는 함수
void Instructor::TestOneMonth() {
    Instructor* instructors[NUMINSTRUCTORS];
    int instructorNum;
    int day;

    // 모든 강사들에게 초기 메일 보내기
    for (instructorNum = 0; instructorNum < NUMINSTRUCTORS; instructorNum++) {
        instructors[instructorNum] = RandomInstructor();  // 랜덤한 강사 생성
        instructors[instructorNum]->GetMail(100);  // 메일 보내기
    }

    // 한 달 동안 각 날짜마다 메일 보내기 또는 제거
    for (day = 1; day <= 31; day++) {
        instructorNum = RandomNum(NUMINSTRUCTORS);  // 랜덤한 강사 선택
        if (RandomNum(2))
            instructors[instructorNum]->GetMail(RandomNum(100));  // 메일 보내기
        else
            instructors[instructorNum]->GetMail(-RandomNum(100));  // 메일 제거
    }

    // 각 강사의 스트레스와 존경받는 정도를 출력
    for (instructorNum = 0; instructorNum < NUMINSTRUCTORS; instructorNum++) {
        cout << "Instructor:" << instructorNum << " Stress: " << instructors[instructorNum]->Stress() << ", Respect: " << instructors[instructorNum]->Respect() << endl;
        delete instructors[instructorNum];  // 동적 할당된 메모리 해제
    }
}

/*---------------------- Main cpp file -------------------------*/ 

int main() {
    srand(static_cast<unsigned int>(time(0)));  // 랜덤 시드 초기화
    Instructor::TestOneMonth();  // 한 달 시뮬레이션 실행
    return 0;
}