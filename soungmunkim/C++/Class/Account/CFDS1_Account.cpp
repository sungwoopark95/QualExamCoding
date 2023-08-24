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

#include <stdio.h>
#include <stdlib.h>
#include "CFDS1_Account.h"

Account::Account(void) {
    balance = 0.0;
    transactions = 0;
}

void Account::Withdraw (float amount){
    balance = balance - amount;
    transactions++;
}

void Account::Deposit (float amount){
    balance = balance + amount;
    transactions++;
}

float Account::GetBalance(void){
    return(balance);
}

/*
subclasses인 EndMonth() 구현 (작동이 다 다름 = polymorphism)
*/
void Account::EndMonth (void){
    printf("transactions:%d balance:%f\n", transactions, balance);
    transactions = 0;
}

// The Monthly Fee type of account.
class MonthlyFee : public Account{
    void EndMonth(void);
};
// The Nickle 'n' Dime type of account.
class NickleNDime : public Account {
    void EndMonth(void);
};

// The Gambler type of account.
class Gambler : public Account {
    void Withdraw(float amount);
    void EndMonth(void) { EndMonthUtil();}
};

void MonthlyFee::EndMonth(void) {
    Withdraw(5.00);
    Account::EndMonthUtil();
}

void NickleNDime::EndMonth(void){
    Withdraw(transactions * 0.50);
    Account::EndMonthUtil();
}

static int RandomNum(int num) {
    return (rand() % num);
}

void Gambler::Withdraw (float amount) {
    if (RandomNum(100) <= 50)
    // 51%
        Account::Withdraw(2 * amount);
    else // 49%
        Account::Withdraw(0.00);
}

/*----------Support Functions --------------*/
static Account *RandomAcount(void) {
    switch (RandomNum(3)){
        case 0: return(new Gambler);
                break;
        case 1: return(new NickleNDime);
                break;
        case 2: return(new MonthlyFee);
                break;
    }
    return(0);
}

