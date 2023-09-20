#include <stdio.h>
#include <stdlib.h>
#include "account.h"
#include <typeinfo>

#define NUMACCOUNTS 20

Account::Account(void){
    balance = 0.0;
    transactions = 0;
}

void Account::Withdraw(float amt) {
    balance-=amt;
    transactions++;
}

void Account::Deposit(float amt){
    balance+=amt;
    transactions++;
}

float Account::Getbalance(void){
    return balance;
}

void Account::EndMonthUtil(void){
    printf("tranactions:%d balance:%f\n", transactions, balance);
    transactions=0;
}

void Account::TestVirtual(void){
    printf("TestVirtual : This is Account.\n");
}




class MonthlyFee : public Account {
    void EndMonth(void);
    void TestVirtual(void);
};

void MonthlyFee::EndMonth(void){
    Withdraw(5.00);
    Account::EndMonthUtil();
}
void MonthlyFee::TestVirtual(void){
    printf("TestVirtual : This is MonthlyFee.\n");
}





class NickleNDime : public Account {
    void EndMonth(void);
    void TestVirtual(void);
};

void NickleNDime::EndMonth(void){
    Withdraw(0.50*transactions);
    Account::EndMonthUtil();
}
void NickleNDime::TestVirtual(void){
    printf("TestVirtual : This is NickleNDime.\n");
}





class Gambler : public Account {
    void Withdraw(float amt);
    void EndMonth(void){EndMonthUtil();} //simple한건 그냥 바로 여기서 코드 작성해도 됨
    void TestVirtual(void);
};

static int RandomNum(int num){
    return (rand()%num); //0~num-1사이의 값으로 한정
}

void Gambler::Withdraw(float amt){
    if (RandomNum(100)<=50) {
        Account::Withdraw(2*amt);
    }
    else {
        Account::Withdraw(0.00);
    }
}
void Gambler::TestVirtual(void){
    printf("TestVirtual : This is Gambler.\n");
}

static Account* RandomAccount(void) {
    switch (RandomNum(3)) {
        case 0: return(new Gambler);
                break;
        case 1: return(new NickleNDime);
                break;
        case 2: return(new MonthlyFee);
                break;
    }
    return(0);
}


void Account::TestOneMonth(void){
    Account* accounts[NUMACCOUNTS]; //각각의 element가 account를 나타내는 포인터
    int accountNum;
    int day;

    for (accountNum=0; accountNum<NUMACCOUNTS; accountNum++){
        accounts[accountNum] = RandomAccount();
        accounts[accountNum] -> Deposit(100);
    }

    for (day=1; day<=31; day++){
        accountNum=RandomNum(NUMACCOUNTS);
        
        // int d=RandomNum(2);
        // int d_amt=RandomNum(100);
        // if (d)
        //     accounts[accountNum]->Deposit(d_amt);
        // else
        //     accounts[accountNum]->Withdraw(d_amt);
        if (RandomNum(2)){
            accounts[accountNum]->Deposit(RandomNum(100));
        }
        else {
            accounts[accountNum]->Withdraw(RandomNum(100));
        }
    }
    for (accountNum=0; accountNum<NUMACCOUNTS; accountNum++){
        printf("account : %d [%s]", accountNum, typeid(*accounts[accountNum]).name());
        // printf("account : %d", accountNum);
        accounts[accountNum]->EndMonth();
    }
    for (accountNum=0; accountNum<NUMACCOUNTS; accountNum++){
        accounts[accountNum]->TestVirtual();
    }
}