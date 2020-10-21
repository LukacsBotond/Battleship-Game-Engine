#include <iostream>
#include "BattleMap.h"

using namespace std;

void startGame()
{

    //start game

    BattleMap Ures(8, 8);

    //random shooting and ships, delete later
    /*     Ures.SetMap(5,0,'X');
    Ures.SetMap(1,1,'D');
    Ures.SetMap(0,1,'D'); */

    Ures.SetShip(0, 0, 'B', 'S');
    Ures.SetShip(0, 0, 'A', 'E');
    //Ures.SetShip(4,4,'A','W');
    //Ures.SetShip(4,4,'A','N');
    Ures.SetShip(4, 4, 'D', 'N');
    //random stuff ends

    cout << Ures;

}