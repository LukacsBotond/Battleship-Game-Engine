#include <iostream>
#include "BattleMap.h"
#include "gameHeader.h"

using namespace std;

void MainMenu()
{

    cout << "     Main Menu" << endl
         << endl;
    cout << "Start game (start)" << endl;
    cout << "Settings (settings)" << endl;
    cout << "Tutorial(tutorial)" << endl;
    cout << "Exit (exit)" << endl
         << endl;

    bool loop = true;
    while(loop){
        string command = askUser();
        if (command == "start" || command == "START" || command == "Start")
        {
            loop = false;
            startGame();
        }
        if (command == "settings" || command == "SETTINGS" || command == "Settings")
        {
            loop = false;
            settings();
        }
        if (command == "tutorial" || command == "TUTORIAL" || command == "Tutorial")
        {
            loop = false;
            tutorial();
        }
        if (command == "exit" || command == "EXIT" || command == "Exit")
        {
            loop = false;
            cout << " Goodbye\n";
            exit(0);
        }
    }
}

string askUser()
{
    string command;
    cout << "Please add the command in parentheses to enter the submenu \n";
    cin >> command;
    return command;
}

void settings()
{
    cout << "   SETTINGS\n";
    cout << "press anything to return to main Menu\n";
    cin.get();
    cin.get();
    MainMenu();
}

//do when game is done so we know what to write
void tutorial()
{
    cout << "   TUTORIAL\n";
    cout << "press anything to return to main Menu\n";
    cin.get();
    cin.get();
    MainMenu();
}