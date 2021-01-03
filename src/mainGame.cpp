#include <iostream>
#include "BattleMap.h"
#include "AI.h"
#include "ColorChange.h"
#include "gameHeader.h"
#include "Multiplayer.h"
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

bool checkNumber(string x)
{
    for (unsigned int i = 0; i < x.length(); i++)
    {
        if (!isdigit(x[i]))
        {
            return false;
        }
    }
    return true;
}

int playerShootAI(BattleMap& Player, AI& ai)
{
    cout << "PlayerShoot\n";
    cout << endl;

    string x, y;
    int ret;
    do
    { //en lovok amig valamit eltalat
        Player.printMap(true);
        Player.printMap(false);
        cout << "Type in the coordinates for target" << endl;
        cin >> x >> y;
        if (!checkNumber(x) || !checkNumber(y))
        {
            printError("Coordinate is not a number");
            continue;
        }
        //shoot ai
        ret = Player.Shoot(stoi(x), stoi(y), &ai);
    } while (ret == 2);
    return ret;
}

//loop till the game ends
//NOT DONE
void MainLoop(BattleMap& Player, int HOST)
{
    printcolor("Game  rted", color_orange);
    int ret, i = 0;
    bool IShoot = false;
    //HOST get the firts shot
    string x, y, message, temp,hitOrMiss,game;
    string coordinate[2];
    if (HOST == 1) {
        IShoot = true;
    }

    while (true)
    {
        //shooter runs in this part
        if (IShoot) {
            cout << "Type in the coordinates for target" << endl;
            cin >> x >> y;
            //TODO send the coordinates to the other side
            sendMessage(x, y);
            //TODO wait for recv is hit/miss won

            game = recvMessage();
            if (game == "You won")
            {
                printcolor("YOU WON", color_orange);
                EndGame();
            }

            hitOrMiss = recvMessage();
            if (hitOrMiss == "Hit")
            {
                IShoot = !IShoot;
            }
            //TODO SET own enemy map accordingly to result
            Player.printMap(true);
           // Player.printMap(false);
            //TODO increase hit/miss accordilngly

            //TODO if won
            //EndGame();
        }//the other is in this part
        else {
            //TODO recv coordinates

            message = recvMessage();
            //cout << message;
            stringstream coord(message);

            while (getline(coord, temp, '.'))
            {
                coordinate[i] = temp;  // koordinatak kinyerese az uzenetbol
                i++;
            }

            //ret = Player.Shoot(4,4);
            ret = Player.Shoot(stoi(coordinate[0]), stoi(coordinate[1]));

            if (ret == 3)
            {
                printcolor("OPONENT WON", color_orange);
                sendSetting("You won");
                EndGame();
            }
            else
            {
                sendSetting("Still playing");
                Sleep(10);
            }

            if (ret == 1)
            {
                sendSetting("Hit");
                IShoot = !IShoot;
            }
            else
            {
                sendSetting("Miss");
            }

            Player.printMap(true);
            // Player.printMap(false);

             //TODO return hit/miss/won

             //TODO if won
             //EndGame();
        }
        //Change roles
        IShoot = !IShoot;
        i = 0;
    }
    EndGame();
}

void MainLoopAI(BattleMap& Player, AI& ai)
{
    BattleMap* Player_p;
    AI* ai_p;
    Player_p = &Player;
    ai_p = &ai;
    printcolor("Game started", color_orange);
    int ret;
    while (true)
    {
        ret = playerShootAI(*Player_p, *ai_p);
        if (ret == 3) //no ship remains
        {
            printcolor("PLAYER WON", color_orange);
            cout << (float)Player_p->getRatio() * 100 << "%" << endl;
            EndGame();
        }
        //AI shoot
        ret = ai_p->shootAI(*Player_p);
        if (ret == 3) //no ship remains
        {
            printcolor("AI WON", color_orange);
            cout << ai_p->getRatio() << endl;
            EndGame();
        }
    }
    EndGame();
}

void EndGame()
{
    cout << "Do you want to play again? (y/n)" << endl;
    char choice;
    string where;
    cin >> choice;
    //want to play again
    if (choice == 'y')
    {
        cout << "type 'settings' to go back and change settings if you are the host" << endl;
        cout << "type 'start' to start with the same settings"
            << "but you need to set the ships again" << endl;
        cin >> where;
        if (where == "settings")
        {
            settings();
        }
        if (where == "start")
        {
            startGame();
        }
    }
    else
    { //leave the game
        //TODO tell the other side I left
        cout << "GOODBYE" << endl;
        exit(0);
    }
}