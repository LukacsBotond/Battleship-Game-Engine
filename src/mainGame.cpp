#include <iostream>
#include "BattleMap.h"
#include "ColorChange.h"
#include "gameHeader.h"
#include <fstream>
#include <vector>

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
    placeShips(Player, 'C', NrDestroyer);
    placeShips(Player, 'B', NrDestroyer);
    placeShips(Player, 'A', NrDestroyer);
    /*
    Player.SetShip(0, 0, 'B', 'S');
    Player.SetShip(1, 1, 'A', 'E');
    Player.SetShip(4, 4, 'D', 'N');
    //random stuff ends
*/
}

void placeShips(BattleMap &Player, char ship, int NrShip)
{
    if (NrShip == 0)
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

    int ShipX = 0;
    int ShipY = 0;
    char Dir = 'N';
    int i = 0;
    while (i != NrShip)
    {
        cout << "Please type the values: ";
        cin >> ShipX >> ShipY >> Dir;
        if (Player.SetShip(ShipX, ShipY, ship, Dir))
        {
            i++;
            Player.printMap(true);
        }
        cout << endl;
    }
}
