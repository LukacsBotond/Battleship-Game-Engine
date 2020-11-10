#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "BattleMap.h"

using namespace std;

void MainMenu();
string askUser();
void tutorial();
void startGame();

//returns the ratio to ship/ocean
float shipRatio();

//egy megadott nevu fajlt kiir kepernyore
void printFile(string file);

//szavakra bont egy sort
vector<string> splitLine(string line);

//settingsnel hasznalt az opcio megadja, hogy mit allitunk es a value az uj ertek
void changeLine(char *file, string option, string value);
void settings();

//place all of the same type ship on the map,
//ship a megszokott D/C/B/A
//NrShip -mennyi van abbol a hajobol
void placeShips(BattleMap &Player, char ship, int NrShip);



void MainLoop(BattleMap Player);

#endif
