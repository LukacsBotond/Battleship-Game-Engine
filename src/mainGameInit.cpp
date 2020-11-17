#include <iostream>
#include "BattleMap.h"
#include "ColorChange.h"
#include "gameHeader.h"
#include "AI.h"
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

//start game
//setup settings
void startGame()
{
    //initialize settings
    ifstream fin;

    fin.open("settings.txt");
    if (fin.fail())
    {
        printError("Failed to read the settings file, exiting");
        fin.close();
        exit(0);
    }
    string sor;
    vector<string> szavak;

    int MapHeigth = 8;
    int MapWidth = 8;
    int NrDestroyer = 1;
    int NrCruiser = 1;
    int NrBattleship = 1;
    int NrAircraftCarrier = 1;
    string IP = "127.0.0.1";
    int PORT = 54000;
    int AILevel = 1;

    //HOST vagy Client
    getline(fin, sor);
    szavak = splitLine(sor);
    //kliens mod, a settings a hosttol erkezik, nincs miert tovabb olvasni
    if (szavak.at(1) == "0")
    {
        //TODO Hosttol megkapni a beallitasokat
        fin.close();
    }
    //Host mod, a beallitasok elkuldese a hostnak es jatek inicializalasa a sajat
    //beallitasokbol
    else
    {
        float ratio = shipRatio() * 10000;
        ratio = round(ratio);
        ratio /= 100;
        cout << "Currens ship ratio: " << ratio << endl;
        if (ratio > 100 || ratio <= 0)
        {
            printError("Error there are no ships, or more ship that ocean");
            printError("You will be redirected to settings to change that");
            settings();
        }
        while (getline(fin, sor))
        {
            szavak = splitLine(sor);
            if (szavak.at(0) == "MapHeigth")
            {
                MapHeigth = stoi(szavak.at(1));
            }
            if (szavak.at(0) == "MapWidth")
            {
                MapWidth = stoi(szavak.at(1));
            }
            if (szavak.at(0) == "NrDestroyer")
            {
                NrDestroyer = stoi(szavak.at(1));
            }
            if (szavak.at(0) == "NrCruiser")
            {
                NrCruiser = stoi(szavak.at(1));
            }
            if (szavak.at(0) == "NrBattleship")
            {
                NrBattleship = stoi(szavak.at(1));
            }
            if (szavak.at(0) == "NrAircraftCarrier")
            {
                NrAircraftCarrier = stoi(szavak.at(1));
            }
            if (szavak.at(0) == "HOSTIP")
            {
                IP = stoi(szavak.at(1));
            }
            if (szavak.at(0) == "Port")
            {
                PORT = stoi(szavak.at(1));
            }
            if (szavak.at(0) == "AILEVEL")
            {
                AILevel = stoi(szavak.at(1));
            }
        }

        //TODO send all those to the Client
    }
    fin.close();
    //start initialization
    BattleMap Player(MapHeigth, MapWidth);
    //Place the Destroyers
    Player.printMap(true);
    placeShips(Player, 'D', NrDestroyer);
    placeShips(Player, 'C', NrCruiser);
    placeShips(Player, 'B', NrBattleship);
    placeShips(Player, 'A', NrAircraftCarrier);
    if (AILevel != 0)
    {
        int ships[4]={NrDestroyer,NrCruiser, NrBattleship,NrAircraftCarrier};
        AI ai(MapHeigth, MapWidth,ships,AILevel);
        

        MainLoopAI(Player,ai);
    }
    else
    {
        MainLoop(Player);
    }
}

void placeShips(BattleMap &Player, char ship, int NrShip)
{
    //there is no ships to be set
    if (NrShip <= 0)
    {
        return;
    }

    switch (ship)
    {
    case 'D':
        printcolor("Please set the head position of the Destroyers", color_blue);
        break;
    case 'C':
        printcolor("Please set the head position of the Cruisers", color_blue);
        break;
    case 'B':
        printcolor("Please set the head position of the Battleships", color_blue);
        break;
    case 'A':
        printcolor("Please set the head position of the AircraftCarriers", color_blue);
        break;
    default:
        break;
    }
    cout << " with x,y coordinates \n"
         << "top - left it 0-0 x = horizontal pozition y = vertical position "
         << "and N/E/S/W for the ship direction\n"
         << "You will need to type it for each ship, one at a time\n"
         << "Type it in one line values separated by space" << endl;
    string ShipX;
    string ShipY;
    char Dir = 'N';
    int i = 0;
    while (i != NrShip)
    {
        cout << "Please type the values: ";
        cin >> ShipX >> ShipY >> Dir;
        if (!checkNumber(ShipX) || !checkNumber(ShipY))
        {
            printError("Coordinate is not a number");
            continue;
        }
        if (Player.SetShip(stoi(ShipX), stoi(ShipY), ship, Dir))
        {
            i++;
            Player.printMap(true);
        }
        cout << endl;
    }
}