#include <iostream>
#include "BattleMap.h"
#include "ColorChange.h"
#include "gameHeader.h"
#include "AI.h"
#include "Multiplayer.h"
#include <fstream>
#include <vector>
#include <cmath>
#include "windows.h"

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

    int multiplayer = 0;
    int HOST = 1;
    int MapHeigth = 8;
    int MapWidth = 8;
    int NrDestroyer = 1;
    int NrCruiser = 1;
    int NrBattleship = 1;
    int NrAircraftCarrier = 1;
    int AILevel = 3;

    //HOST vagy Client
    getline(fin, sor);
    szavak = splitLine(sor);
    //kliens mod, a settings a hosttol erkezik, nincs miert tovabb olvasni
    if (szavak.at(1) == "0")
    {
        

        HOST = 0;
        //if multiplayer,receive the coordinates from the host
        MapHeigth = stoi(recvMessage());
        cout << "MapHeigth:" << MapHeigth << endl;
        MapWidth = stoi(recvMessage());
        cout << "MapWidth:" << MapWidth << endl;
        NrDestroyer = stoi(recvMessage());
        cout << "NrDestroyer:" << NrDestroyer << endl;
        NrCruiser = stoi(recvMessage());
        cout << "NrCruiser:" << NrCruiser << endl;
        NrBattleship = stoi(recvMessage());
        cout << "NrBattleship:" << NrBattleship << endl;
        NrAircraftCarrier = stoi(recvMessage());
        cout << "NrAircraftCarrier:" << NrAircraftCarrier << endl;
        AILevel = stoi(recvMessage());
        cout << "AI:" << AILevel << endl;
        //
        fin.close();
    }
    //Host mod, a beallitasok elkuldese a hostnak es jatek inicializalasa a sajat
    //beallitasokbol
    else
    {
        HOST = 1;
        float ratio = shipRatio() * 10000;
        ratio = round(ratio);
        ratio /= 100;
        //cout << "Currens ship ratio: " << ratio << endl;
        if (ratio > 100 || ratio <= 0)
        {
            printError("Error there are no ships, or more ships than ocean");
            printError("You will be redirected to settings to change that");
            settings();
        }
        while (getline(fin, sor))
        {
            szavak = splitLine(sor);

            if (szavak.at(0) == "Multiplayer")
            {
                if (stoi(szavak.at(1)) == 1)
                {
                    multiplayer = 1;
                }
            }

            if (szavak.at(0) == "MapHeigth")
            {
                MapHeigth = stoi(szavak.at(1));
                //if multiplayer,than send out the settings to other player
                if (multiplayer)
                {
                    sendSetting(szavak.at(1));
                    Sleep(10);
                }
            }
            if (szavak.at(0) == "MapWidth")
            {
                MapWidth = stoi(szavak.at(1));
                if (multiplayer)
                {
                    sendSetting(szavak.at(1));
                    Sleep(10);
                }
            }
            if (szavak.at(0) == "NrDestroyer")
            {
                NrDestroyer = stoi(szavak.at(1));
                if (multiplayer)
                {
                    sendSetting(szavak.at(1));
                    Sleep(10);
                }
            }
            if (szavak.at(0) == "NrCruiser")
            {
                NrCruiser = stoi(szavak.at(1));
                if (multiplayer)
                {
                    sendSetting(szavak.at(1));
                    Sleep(10);
                }
            }
            if (szavak.at(0) == "NrBattleship")
            {
                NrBattleship = stoi(szavak.at(1));
                if (multiplayer)
                {
                    sendSetting(szavak.at(1));
                    Sleep(10);
                }
            }
            if (szavak.at(0) == "NrAircraftCarrier")
            {
                NrAircraftCarrier = stoi(szavak.at(1));
                if (multiplayer)
                {
                    sendSetting(szavak.at(1));
                    Sleep(10);
                }
            }
            
           
            if (szavak.at(0) == "AILevel")
            {
                AILevel = stoi(szavak.at(1));
                if (multiplayer)
                {
                    sendSetting(szavak.at(1));
                    Sleep(10);
                }
            }
        }
        //TODO send all those to the Client
    }
    fin.close();
    //start initialization
    BattleMap Player(MapHeigth, MapWidth);
    BattleMap* Player_p;
    Player_p = &Player;
    //Place the Destroyers

    placeShips(*Player_p, 'D', NrDestroyer);
    placeShips(*Player_p, 'C', NrCruiser);
    placeShips(*Player_p, 'B', NrBattleship);
    placeShips(*Player_p, 'A', NrAircraftCarrier);
    //Shoot AI
    if (AILevel != 0)
    {
        int ships[4] = { NrDestroyer, NrCruiser, NrBattleship, NrAircraftCarrier };
        AI ai(MapHeigth, MapWidth, ships, AILevel);
        AI* ai_p;
        ai_p = &ai;
        ai_p->AIplaceShips();
        MainLoopAI(*Player_p, *ai_p);
    }
    //TODO PvP
    else
    {
        //throw out_of_range("Not implemented yet");
        MainLoop(*Player_p, HOST);
    }
}

void placeShips(BattleMap& Player, char ship, int NrShip)
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