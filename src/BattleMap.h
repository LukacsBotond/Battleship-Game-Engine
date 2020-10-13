#ifndef BATTLEMAP_H
#define BATTLEMAP_H
#include <string>
#include <iostream>

using namespace std;

class BattleMap
{
public:
    //Default konstruktor
    BattleMap();
    //set sized constructor
    BattleMap(int hight,int width);
    //Destruktor
    ~BattleMap();

    //igaz ha letezik es ures, hamis ha nem letezik
    bool CoordinateExist(int x,int y);
    void SetMap(int x,int y,char data);
    
    int getMapHeight();
    int getMapWidth();

    //kiiratas
    friend ostream &operator<<(ostream &os, const BattleMap &what);

private:
    //palya
    //0 = nincs loves vagy hajo a mezon, nem rajzolni ki
    //X = loves a mezon, de nem talalt
    //O = loves es talalt 
    char** Map;
    int MapHeight;
    int MapWidth;
    int HPDestrolyer=2;
    int HPCruiser=3;
    int HPBattleship=4;
    
};
#endif