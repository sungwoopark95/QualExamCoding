
class Instructor {
    public :
    Instructor(void);
    virtual int Stress(void);
    virtual int Respect(void);
    void GetMail(int);
    virtual void Cope(void)=0;
    int checkMail(void);
    

    // protected :
    int unreadMail;
    int age;
    int eccentricities;

    // public :
    static void Test(void);
};