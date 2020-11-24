#include <iostream>
#include "BattleMap.h"
#include "ColorChange.h"
#include "gameHeader.h"
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

bool checkNumber(string x)
{
    for (int i = 0; i < x.length(); i++)
    {
        if (!isdigit(x[i]))
        {
            return false;
        }
    }
    return true;
}

int playerShootAI(BattleMap Player, AI ai)
{
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
        ret = Player.Shoot(stoi(x), stoi(y), ai);
    } while (ret == 2);
    return ret;
}

//loop till the game ends
void MainLoop(BattleMap Player)
{
    int ret;
    while (true)
    {
        ret = playerShoot(Player);
        if (ret == 3) //no ship remains
        {
            cout << Player.getRatio() << endl;
            EndGame();
        }
        //TODO get the shot coordinates from the other side
    }
    EndGame();
}

void MainLoopAI(BattleMap Player, AI ai)
{
    int ret;
    while (true)
    {
        ret = playerShoot(Player);
        if (ret == 3) //no ship remains
        {
            printcolor("PLAYER WON", color_orange);
            cout << Player.getRatio() << endl;
            EndGame();
        }
        //AI shoot
        ret = ai.shootAI(Player);
        if (ret == 3) //no ship remains
        {
            printcolor("AI WON", color_orange);
            cout << ai.getRatio() << endl;
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
