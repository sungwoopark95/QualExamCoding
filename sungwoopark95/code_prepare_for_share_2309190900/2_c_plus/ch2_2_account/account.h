
class Account {
    public:
    Account(void);
    virtual void Withdraw(float amt);
    virtual void Deposit(float amt);
    virtual float Getbalance(void);
    virtual void EndMonth(void)=0; //pure virtual, force subclasses to implement

    virtual void TestVirtual(void); //virtual로 선언하지 않으면, polymorphism이 제대로 작동하지 않을 수 있음


    protected:
    float balance;
    int transactions;
    void EndMonthUtil(void);

    public:
    static void TestOneMonth(void);
};