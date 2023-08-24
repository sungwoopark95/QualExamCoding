/*
The account is an abstract "superclass" with the default characteristics of a bank account.
It maintains a "balance" and a "current number of transactions".
It does not have a full implementation of "EndMonth()" behavior which should be filled in by its "subclasses".
*/
// #include <iostream>

class Account {
    public:
    Account(void);
    virtual void Withdraw (float amount);
    virtual void Deposit (float amount);
    virtual float GetBalance (void);
    virtual void EndMonth (void) = 0; // pure virtual, force subclasses to implement

    protected:
    float balance;
    int transactions;
    void EndMonthUtil (void);

    // class function
    public:
    static void TestOneMonth (void); // Test code를 class에 넣음
};