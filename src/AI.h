#ifndef AI_H
#define AI_H

#include <iostream>
#include <list>

struct COORDINATE
{
    int x;
    int y;
};


class BattleMap;

class AI : BattleMap
{
public:
    //ships[]-nr of each ship type
    //ships[0]-Destroyer
    //ships[1]-Cruiser
    //ships[2]-Battleship
    //ships[3]-AircraftCarrier
    AI(int height, int width, int ships[4], int AILevel) : BattleMap(height, width)
    {
        //cout << "AI constructor: " << height << " " << width << endl;
        this->ships[0] = ships[0];
        this->ships[1] = ships[1];
        this->ships[2] = ships[2];
        this->ships[3] = ships[3];
        this->AILevel = AILevel;
    }
    ~AI()
    {
        std::cout << "AI got deleted" << std::endl;
        //BattleMap::~BattleMap();
    }
    void AIplaceShips();

    int shootAI(BattleMap &Player);
    char getPosition(int x, int y, bool My)
    {
        return BattleMap::getPosition(x, y, My);
    }

    void SetMap(int x, int y, char data, bool My)
    {
        BattleMap::SetMap(x, y, data, My);
    }

    float getRatio()
    {
        return BattleMap::getRatio();
    }

    void printMap(bool my)
    {
        BattleMap::printMap(my);
    }

private:
    int shootEasy(BattleMap &Player);
    int shootMedium(BattleMap &Player);
    int shootHard(BattleMap &Player);

    int shootAround(BattleMap &Player);
    bool hole(int x,int y);

    void placeShipType(int type);

    void pushCoordinate(int x,int y);

    std::list<COORDINATE> hitCoordinates;
    int lastShotX = 0;
    int lastShotY = 0;
    int ships[4];
    int AILevel;
};

#endif