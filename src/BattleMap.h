#ifndef BATTLEMAP_H
#define BATTLEMAP_H

#include <string>
#include <iostream>

class AI;

//using namespace std;

class BattleMap
{
public:
    //Default konstruktor
    BattleMap();
    //set sized constructor
    BattleMap(int hight, int width);
    //Destruktor
    ~BattleMap();

    //hajo kezdo koordinata lerakasa es iranya (N/E/S/W)
    //Destroyer = D -2 hossz
    //Cruiser = C -3 hossz
    //Battleship = B -4 hossz
    //Airship = A -5 hossz
    //True/false ha sikerul/hiba van
    bool SetShip(int x, int y, char ship, char dir);

    //return 0 if miss
    //return 1 if hit a ship
    //return 2 if shooting the same spot or outisde the map
    //give an another chance this time
    //return 3 if last ship is destroyed

    //Player shoot AI
    int Shoot(int x, int y, AI* ai);

    //AI or player shoot player
    int Shoot(int x, int y, BattleMap &enemy);

    //returns the ration hit/miss
    float getRatio();

    //Egy adott karaktert berak a palyara
    //my == true- az en terkepem
    //false - ellenfel terkepe
    void SetMap(int x, int y, char data, bool My);

    //kiiratas
    //my = true -sajat
    //my = false -enemy
    void printMap(bool my);

protected:
    int getMapHeight();
    int getMapWidth();

    //don't check just return, CoordinatesExist()
    //must be called before it
    char getPosition(int x, int y, bool My);

    //befere a palyara true ha befer
    bool FitShip(int x, int y, char ship, char dir);
    //igaz ha letezik es ures, hamis ha nem letezik
    bool CoordinateExist(int x, int y);

    //ellenorzi, hogy a hajo hossza soran masik hajora kerul-e, false ha minden rendben
    bool ShipStached(int x, int y, int length, char dir);

    //Visszaadja a hajo hosszat, -1, ha nem megfelelo hajot adunk meg
    int getShipLength(char ship);

    //palya
    //"" = nincs loves vagy hajo a mezon, nem rajzolni ki
    //A/B/C/D = SHIP-only appear in MyMap
    //X = loves a mezon, de nem talalt
    //O = loves es talalt
    char **MyMap;
    char **EnemyMap;
    int MapHeight;
    int MapWidth;
    int HP = 0;
    int hits = 0;
    int total = 0;
    //AI* ai;
};

#endif