#include <iostream>
#include "BattleMap.h"
#include "ColorChange.h"
#include <fstream>

using namespace std;

//start game
void startGame()
{
    //initialize settings
    ifstream fin;
    fin.open("settings.txt");
    if(fin.fail()){
        printError("Failed to read the settings file, exiting");
        fin.close();
        exit(0);
    }
    string sor;
    //
    getline(fin,sor);

    
    

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