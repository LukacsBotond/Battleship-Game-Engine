#include <iostream>
#include <fstream>
#include "BattleMap.h"
#include "gameHeader.h"
#include "ColorChange.h"
#include <stdio.h>
#include <string.h>

using namespace std;

void MainMenu()
{

    printcolor(" MAIN MENU", color_orange);
    cout<<endl;
    printcolor("Start game (start)",color_dark_green);
    printcolor("Settings (settings)",color_blue );
    printcolor("Tutorial(tutorial)",color_blue);
    printcolor("Exit (exit)", color_dark_red);
    cout<< endl << endl;

    bool loop = true;
    while (loop)
    {
        string command = askUser();
        if (command == "start" || command == "START" || command == "Start")
        {
            loop = false;
            startGame();
        }
        if (command == "settings" || command == "SETTINGS" || command == "Settings")
        {
            settings();
        }
        if (command == "tutorial" || command == "TUTORIAL" || command == "Tutorial")
        {
            tutorial();
        }
        if (command == "exit" || command == "EXIT" || command == "Exit")
        {
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

void printFile(string file)
{
    ifstream fin;
    fin.open(file);
    if (fin.fail())
    {
        cout << file << " open error, returning to Main Menu" << endl;
        MainMenu();
    }
    string sor;
    while (getline(fin, sor))
    {
        cout << sor << endl;
    }
    fin.close();
}

void changeline(char *file, string oldline, string newline)
{
    ifstream fin;
    ofstream fout;
    fout.open("tmp.txt");
    fin.open(file);
    string sor;
    if (fin.fail())
    {
        cout << file << " open error, returning to Main Menu" << endl;
        MainMenu();
    }
    while (getline(fin, sor))
    {
        if (oldline == sor)
        {
            fout << newline;
        }
        else
        {
            fout << sor;
        }
        fout<<"\n";
    }
    int result = rename("tmp.txt", file);
    if (result == 0)
    {
        printcolor("Settings successfully changed",color_green);
    }
    fin.close();
    fout.close();
}

void settings()
{
    printcolor("   SETTINGS", color_blue);

    string oldline;
    string newline;
    char set[] = "settings.txt";
    cin.get();
    do
    {
        printcolor("Current settings",color_blue);
        printFile(set);
        cout << "write the line you want replaced or exit to return to the Main Menu: " << endl;
        getline(cin, oldline);
        if (oldline == "exit" || oldline == "EXIT")
        {
            cout << "Returning to main menu\n";
            break;
        }
        cout << "\n\n\nwrite the new Line\n";
        getline(cin, newline);
        changeline(set, oldline, newline);
    } while (true);

    cout << "press anything to return to main Menu\n";
    cin.get();
}

//do when game is done so we know what to write
void tutorial()
{
    printcolor("   TUTORIAL\n",color_blue);
    cout << "press anything to return to main Menu\n";
    cin.get();
    cin.get();
}