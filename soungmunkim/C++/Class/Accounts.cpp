/*
[bank account]
은행 잔고에 정보들을 저장해야함
1. 각 account마다 current balance와 total number of transactions의 정보만 필요함
2. 3가지 종류의 account가 있음
    1) Normal: deposit and withdraw just affect the balance
        $5.00 monthly fee that ounts as a normal withdrawal transaction.
    2) Nickle 'n Dime: each withdrawal generates a $0.50 fee
        Both the withdrawal and the fee count as a transaction
    3) The Gambler: a withdrawal returns the requested amount of money,
        however the amount deducted from the balance is as follows:
            0.49 probability that no money will actually be substracted from the balance.
            0.51 probability that twice the amount actually withdrawn will be subtracted.

3, Constructor: initialize a new account
4. void Deposit(float amount): add the amount to the balance and increment the number of transactions.
5. void Withdraw(float amount): substract the amount to the balance and increment the number of transactions.
6. float GetBalance(): return the current balance
7. void EndMonth(): the account will be sent this message once a month,
    so it should levy any monthly fees at that time and print out the account monthly summary.
*/

/*---------------------- Account Header file -------------------------*/
class Account{
    public:
        Account(void); // constructor
        virtual void Withdraw (float amt); // virtual -> polymorphism (어떤 계좌냐에 따라 동작이 달라짐)
        virtual void Deposit (float amt); 
        virtual float GetBalance(void);

        /*
        subclass마다 다 다르게 동작하기 때문에 
        account class에서가 아닌 subclass에서 각각 implementation 하는 것 (overriding)
        */
        virtual void EndMonth(void) = 0; // pure virtual, force subclasses to implement
        
        protected:
            float balance;
            int transactions;
            void EndMonthUtil(void);

        // Class Function
        public:
            static void TestOneMonth(void); // global function
};

/*---------------------- Account cpp file -------------------------*/
#include <stdio.h>
#include <stdlib.h>
// #include "account.h"

// Constructor defined 하기
Account::Account(void){ // Account에 private(protected) 변수 설정
    balance  = 0.0;
    transactions = 0;
}

// Account class에서 Virtual function defined 하기
void Account::Withdraw(float amt) {
    balance = balance - amt;
    transactions++;
}
void Account::Deposit(float amt) {
    balance = balance + amt;
    transactions++;
}

float Account::GetBalance(void) {
    return balance;
}
/*
Factors same common behavior up which will occur in the subclasses' EndMonth()
*/
void Account::EndMonthUtil(void){
    printf("transactions:%d balance:%f\n", transactions, balance); // print out the account monthly summary
    transactions = 0;
}

// pure virtual function인 EndMonth function을 subclasses에서 defined하기
// 이 예제에서는 header file에 안 넣고 cpp file에 넣음
/*++++++++++++++++ SubClasses ******************/
/*The Monthly Fee type of account*/
class MonthlyFee : public Account {
    void EndMonth(void);
};
/*The Nickle 'n' Dime type of account*/
class NickleNDime : public Account{
    void EndMonth(void);
};
/*The Gambler type of account*/
class Gambler : public Account {
    void Withdraw (float amt);
    void EndMonth(void) {
        EndMonthUtil(); // Gambler account는 따로 적용되는 Monthly fee가 없음 -> 바로 Print out
    }
};

// 각 subclass에서 EndMonth implementation
void MonthlyFee::EndMonth(void){
    Withdraw(5.00);
    Account::EndMonthUtil();    // normal withdrawal transaction에서 $5 monthly fee을 적용한 후 print out
}
void NickleNDime::EndMonth(void){
    Withdraw(transactions * 0.50);  // withdrawal은 transaction으로 간주하여 매번 0.5 fee을 적용한 후 Print out
    Account::EndMonthUtil();
}

// static 함수: 해당 함수는 해당 소스 파일에서만 사용 가능함
static int RandomNum(int num){
    return rand() % num;    // random number 생성
}

/*
0.49 확률로 balance에서 돈 안 뺌 (withdrawal)
0.51 확률로 amount의 2배를 뺌 (withdrawal)
*/
void Gambler::Withdraw(float amt) {
    if (RandomNum(100) <= 50)
        Account::Withdraw(2 * amt); // 0-50 => 51%
    else
        Account::Withdraw(0.00); //51-100 => 49%
}

/*++++++++++++++++ Support Functions ******************/
// Account type을 갖고 있는 pointer gambler, nicklendime, monthlyfee account들을 랜덤하게 생성함
// return 할 때 pointer을 return (앞에 *가 붙어있음)
static Account *RandomAccount(void) {
    switch (RandomNum(3)) {
        case 0: return(new Gambler); // 동적 할당
                break;
        case 1: return(new NickleNDime);
                break;
        case 2: return(new MonthlyFee);
                break;
    }
    return(0);
}

// NUMACCOUNTS인 것들을 다 20으로 바꿔주는 것
#define NUMACCOUNTS 20
/*
This is a static class function, so you call it like regular function,
except with Account:: before the function name.
*/
void Account::TestOneMonth(void){
    // account[NUMACCOUNTS]는 account type (즉, 만들어질 각 특정 account들은 기본 account type임)
    Account* accounts[NUMACCOUNTS];
    int accountNum;
    int day;

    /* Create a bunch of accounts of various types */
    // for loop을 통해 randomly 특정 account을 만들고 depost을 100불 넣음
    // 만들어지는 특정 account가 기본 account type이기 때문에 deposit()에 접근 가능
    for (accountNum = 0; accountNum < NUMACCOUNTS; accountNum++){
        accounts[accountNum] = RandomAccount();
        accounts[accountNum]->Deposit(100);
    }

    /* do a months worth of random transactions */
    // 만들어지는 특정 account가 기본 account type이기 때문에 deposit(), withdraw()에 접근 가능
    for (day=1; day<=31; day++){
        accountNum = RandomNum(NUMACCOUNTS); // select an account at random
        if (RandomNum(2)) // deposit or withdraw
            accounts[accountNum]->Deposit(RandomNum(100)); // polymorphism
        else
            accounts[accountNum]->Withdraw(RandomNum(100)); // polymorphism
    }

    // 각 account마다 account number, transaction balance print out 시킴
    // 만들어지는 특정 account가 기본 account type이기 때문에 EndMonth()에 접근 가능
    for (accountNum=0; accountNum < NUMACCOUNTS; accountNum++){
        printf("account:%d", accountNum);
        accounts[accountNum]->EndMonth();
    }
}

/*---------------------- Main cpp file -------------------------*/
// #include "account.h"

// int type이기 때문에 0 return
int main(void){
    Account::TestOneMonth(); // Invoke the static class function return 0;
    return 0;
}