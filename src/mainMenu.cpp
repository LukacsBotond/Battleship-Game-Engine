#include <iostream>
#include <fstream>
#include <vector>
#include "BattleMap.h"
#include "gameHeader.h"
#include "ColorChange.h"
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

void MainMenu()
{
    printcolor(" MAIN MENU", color_orange);
    cout << endl;
    printcolor("Start game (start)", color_dark_green);
    printcolor("Settings (settings)", color_blue);
    printcolor("Tutorial(tutorial)", color_blue);
    printcolor("Exit (exit)", color_dark_red);
    cout << endl
         << endl;

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

//-ajanlott 15% hajo/ocean
float shipRatio()
{
    ifstream fin;
    fin.open("settings.txt");

    string sor;
    int MapHeight;
    int MapWidth;
    int NrDestrolyer;
    int NrCruiser;
    int NrBattleship;
    int NrAircarftC;
    vector<string> szavak;
    //skip HOST settings
    getline(fin, sor);

    //map settings read
    for (int i = 0; i < 6; i++)
    {
        getline(fin, sor);
        szavak = splitLine(sor);

        switch (i)
        {
        case 0:
            MapHeight = stoi(szavak.at(1));
            break;
        case 1:
            MapWidth = stoi(szavak.at(1));
            break;
        case 2:
            NrDestrolyer = stoi(szavak.at(1));
            break;
        case 3:
            NrCruiser = stoi(szavak.at(1));
            break;
        case 4:
            NrBattleship = stoi(szavak.at(1));
            break;
        case 5:
            NrAircarftC = stoi(szavak.at(1));
            break;
        default:
            break;
        }
    }
    int ocean = MapWidth * MapHeight;
    int ships = (NrDestrolyer * 2) + (NrCruiser * 3) + (NrBattleship * 4) + (NrAircarftC * 5);
    return (float)ships / ocean;
}

vector<string> splitLine(string line)
{
    vector<string> szavak;
    string szo = "";
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == ' ')
        {
            szavak.push_back(szo);
            szo = "";
        }
        else
        {
            szo += line[i];
        }
    }
    szavak.push_back(szo);
    return szavak;
}

bool checkValidOption(string option, string value)
{ //HOST csak 0/1 lehet
    if (option == "HOST")
    {
        if (value == "0" || value == "1")
        {
            return true;
        }
        else
        {
            printError("HOST option can only be 0 if you join 1 if you want someone to join");
            return false;
        }
    }
    //MapHeigth nagyobb mint 4 es kissebb mint 50
    if ((option == "MapHeigth" || option == "MapWidth"))
    {
        if (value >= "4" && value <= "20")
        {
            return true;
        }
        else
        {
            printError("The map should width/height should be in the range [4-20]");
            return false;
        }
    }
    if ((option == "NrDestroyer" || option == "NrCruiser" || option == "NrBattleship" || option == "NrAircraftCarrier"))
    {
        if (value >= "0")
        {
            return true;
        }
        else
        {
            printError("There can't be less than 0 ships");
        }
    }

    if (option == "AILevel")
    {
        if (value >= "0" && value <= "3")
        {
            return true;
        }
        else
        {
            printError("AI can only be: 0-off, 1-low, 2-med, 3-high");
            return false;
        }
    }
    return false;
}

void changeline(char *file, string option, string value)
{
    ifstream fin;
    ofstream fout;
    fout.open("tmp.txt");
    fin.open(file);
    string sor;
    if (fin.fail())
    {
        cout << file << " open error, returning to Settings" << endl;
        return;
    }
    if (!checkValidOption(option, value))
    {
        printError("Check your typing, write the full name of the option, like 'MapHeight' with an appropiate number");
        return;
    }

    while (getline(fin, sor))
    {
        vector<string> szavak = splitLine(sor);
        //megvan amit a felhasznalo keresett
        if (szavak.at(0) == option)
        {
            fout << option + ' ';
            fout << value;
        }
        else
        {
            fout << sor;
        }
        fout << "\n";
    }
    int result = rename("tmp.txt", file);
    if (result == 0)
    {
        printcolor("Settings successfully changed", color_green);
    }
    fin.close();
    fout.close();
}

void settings()
{
    printcolor("   SETTINGS", color_blue);
    cout << endl;
    string option;
    string value;
    char set[] = "settings.txt";
    cin.get();
    bool goodratio = false;
    bool acceptable = false;
    float reqRatio = 15;
    do
    {
        printcolor("Recomended ship ratio: 15%", color_orange);
        float currentRatio = shipRatio() * 10000;
        currentRatio = round(currentRatio);
        currentRatio /= 100;
        //10% ship or less
        if ((reqRatio - currentRatio) < (-5))
        {
            goodratio = false;
            acceptable = true;
            printcolor("Current ship ratio: " + to_string(currentRatio) + "% is to LOW, add more/bigger ships", color_yellow);
        }
        if ((reqRatio - currentRatio) > 10)
        {
            goodratio = false;
            acceptable = true;
            printcolor("Current ship ratio: " + to_string(currentRatio) + "% is to HIGH, add less/smaller ships", color_yellow);
        }
        if ((reqRatio - currentRatio) >= (-5) && (reqRatio - currentRatio) <= 10)
        {
            goodratio = true;
            acceptable = true;
            printcolor("Current ship ratio: " + to_string(currentRatio) + "% is in an acceptable range", color_green);
        }
        if (currentRatio > 100)
        {
            acceptable = false;
            printError("To much ship, there is not enough map space for this many ship!");
            printError("Remove some ships or make the map bigger!");
            printError("Can't start untill the ship ratio is under 100%!");
        }

        printcolor("Current settings", color_blue);
        printFile(set);
        //type: AI
        cout << "write the option you want replaced or exit to return to the Main Menu: " << endl;
        cout << " Or type 'Tutorial\n";
        cin >> option;
        if (option == "exit" || option == "EXIT")
        {
            if (!acceptable)
            {
                printError("You can't exit, the ship ratio is still over 100%!");
                continue;
            }
            else
            {
                if (goodratio)
                {
                    printcolor("the ship ratio is in a good ratio", color_green);
                }
                else
                {
                    printcolor("the ship ratio is in an acceptable ratio", color_yellow);
                }
            }
        }

        //type: 2
        cout << "\n\n\nwrite the new value for the option\n";
        cin >> value;
        changeline(set, option, value);
    } while (true);

    cout << "press anything to return to main Menu\n";
    cin.get();
}

//do when game is done so we know what to write
void tutorial()
{
    printcolor("   TUTORIAL\n", color_blue);
    cout << "press anything to return to main Menu\n";
    cin.get();
    cin.get();
}