#ifndef AI_H
#define AI_H

#include <iostream>
#include "BattleMap.h"

class AI : BattleMap
{
public:
    //ships[]-nr of each ship type
    //ships[0]-Destroyer
    //ships[1]-Cruiser
    //ships[2]-Battleship
    //ships[3]-AircraftCarrier
    AI(int hight, int width, int ships[4], int AILevel);
    void AIplaceShips();
    void placeShipType(int type);

    int shootAI(BattleMap Player);
    char getPosition(int x, int y, bool My){
        return BattleMap::getPosition(x,y,My);
    }

    void SetMap(int x, int y, char data, bool My){
        BattleMap::SetMap(x,y,data,My);
    }

    float getRatio(){
        return BattleMap::getRatio();
    }

    void printMap(bool my)
    {
        BattleMap::printMap(my);
    }

private:
    int shootEasy(BattleMap Player);
    int shootMedium(BattleMap Player);
    int shootHard(BattleMap Player);

    int lastShotX=0;
    int lastShotY=0;
    int ships[4];
    int AILevel;
};

#endif