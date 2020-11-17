#ifndef AI_H
#define AI_H

#include <iostream>
#include "BattleMap.h"

class AI : BattleMap
{
    public:
        AI(int hight, int width,int ships[4], int AILevel);
        void placeShips();  
    private:
       int NrDestroyer;
       int NrCruiser;
       int NrBattleship;
       int NrAircraftCarrier;
       int AILevel;
};

#endif