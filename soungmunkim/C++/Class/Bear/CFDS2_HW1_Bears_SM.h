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
#pragma once

/*--------- Super Class ----------*/
class Bear {
    public:
    Bear(float aWeight); // constructor
    float GetWeight();
    void SetWeight(float aWeight);
    virtual float Aggressiveness() = 0;
    virtual void PrintSelf() = 0;

    protected:
    float Weight;
};

/*--------- Sub Classes ----------*/
class Polar : public Bear {
    public: 
    Polar(float aWeight): Bear(aWeight) {};

    float Aggressiveness();
    void PrintSelf();
};

class Grizzly: public Bear {
    public:
    Grizzly(float aWeight): Bear(aWeight) {};

    float Aggressiveness();
    void PrintSelf();
};

class Black : public Bear {
    public: 
    Black(float aWeight): Bear(aWeight) {};

    float Aggressiveness();
    void PrintSelf();
};

class Black_Momma : public Black {
    public:
    Black_Momma(float aWeight): Black(aWeight) {
        cub = NULL;
        num_cub = 0;
        cubAggressiveness = 0.0;
    };

    void AddCub(Bear *aCub);
    Bear *GetCub();
    float Aggressiveness();
    float TotalAggressiveness();
    void PrintSelf();

    protected:
    Bear *cub;
    int num_cub;
    float cubAggressiveness;
};

