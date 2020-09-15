#ifndef STATICS_H
#define STATICS_H

/*
This class will be responsible for taking data from the Game Setting screen and passing to
any other in-game object that need them.
*/

class Statics {
private:
    int MONEY_MAX, HOUSES_MAX, HOTELS_MAX, STARTING_AMOUNT;

public:
    Statics(
        //default settings
        int _money_max = 20580,
        int _starting_amount = 1500,
        int _houses_max = 32,
        int _hotels_max = 12
    )
    {
        //values input in starting screen. 
        MONEY_MAX = _money_max;
        HOUSES_MAX = _houses_max;
        HOTELS_MAX = _hotels_max;
        STARTING_AMOUNT = _starting_amount;
    }

    int getMONEY_MAX() { return MONEY_MAX; }
    int getHOUSES_MAX() { return HOUSES_MAX; }
    int getHOTELS_MAX() { return HOTELS_MAX; }
    int getSTARTING_AMOUNT() { return STARTING_AMOUNT; }

};

#endif
