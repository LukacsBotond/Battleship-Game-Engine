#include <iostream>
#include "BattleMap.h"
#include "ColorChange.h"

using namespace std;

//alapjaraton 8*8-as palyat keszit
BattleMap::BattleMap()
{
    this->MapHeight = 8;
    this->MapWidth = 8;
    //make Map
    this->MyMap = new char *[MapHeight];
    for (int i = 0; i < MapHeight; i++)
    {
        this->MyMap[i] = new char[MapWidth];
    }
    this->EnemyMap = new char *[MapHeight];
    for (int i = 0; i < MapHeight; i++)
    {
        this->EnemyMap[i] = new char[MapWidth];
    }
    //ne legyen benne semmi
    for (int i = 0; i < MapHeight; i++)
    {
        for (int j = 0; j < MapWidth; j++)
        {
            this->EnemyMap[i][j] = ' ';
            this->MyMap[i][j] = ' ';
        }
    }
}

//akkora palyat keszit amekkorat akarsz
BattleMap::BattleMap(int Height, int Width)
{
    if (Height < 5)
    {
        printError("height to small, 5 will be used");
        this->MapHeight = 4;
    }
    else
        this->MapHeight = Height;
    if (Width < 5)
    {
        printError("width to small, 5 will be used");
        this->MapWidth = 4;
    }
    else
        this->MapWidth = Width;
    this->MyMap = new char *[MapHeight];
    for (int i = 0; i < MapHeight; i++)
    {
        this->MyMap[i] = new char[MapWidth];
    }

    this->EnemyMap = new char *[MapHeight];
    for (int i = 0; i < MapHeight; i++)
    {
        this->EnemyMap[i] = new char[MapWidth];
    }
    //ne legyen benne semmi

    for (int i = 0; i < MapHeight; i++)
    {
        for (int j = 0; j < MapWidth; j++)
        {
            this->MyMap[i][j] = ' ';
            this->EnemyMap[i][j] = ' ';
        }
    }
}

BattleMap::~BattleMap()
{
    for (int i = 0; i < MapHeight; i++)
    {
        delete[] this->MyMap[i];
        delete[] this->EnemyMap[i];
    }
    delete[] this->MyMap;
    delete[] this->EnemyMap;
}

int BattleMap::getMapHeight()
{
    return this->MapHeight;
}

int BattleMap::getMapWidth()
{
    return this->MapWidth;
}

int BattleMap::getShipLength(char ship)
{
    int shipLength = (ship - 'F') * -1;
    //nincs ilyen hajo
    if (shipLength < 2 || shipLength > 5)
    {
        string errorShip(1, ship);
        printError("There is no such ship: " + errorShip);
        return -1;
    }
    return shipLength;
}

char BattleMap::getPosition(int x, int y, bool My)
{
    if (My)
    {
        return MyMap[x][y];
    }
    return EnemyMap[x][y];
}

void BattleMap::SetMap(int x, int y, char data, bool My)
{
    if (CoordinateExist(x, y))
    {
        if (My)
        {
            this->MyMap[x][y] = data;
        }
        else
        {
            this->EnemyMap[x][y] = data;
        }
    }
}

bool BattleMap::ShipStached(int x, int y, int length, char dir)
{
    int xnew = x;
    int ynew = y;
    while (length != 0)
    {
        //ha nem szokoz akkor egy hajo van a koordinatan
        if (getPosition(xnew, ynew, true) != ' ')
        {
            printError("The ships would be on top of eachother");
            return true;
        }
        switch (dir)
        {
        case 'N':
            xnew -= 1;
            break;
        case 'E':
            ynew += 1;
            break;
        case 'S':
            xnew += 1;
            break;
        case 'W':
            ynew -= 1;
            break;
        default:
            break;
        }
        length--;
    }
    return false;
}

bool BattleMap::SetShip(int x, int y, char ship, char dir)
{
    if (!(dir == 'n' || dir == 'e' || dir == 's' || dir == 'w' || dir == 'N' || dir == 'E' || dir == 'S' || dir == 'W'))
    {
        printError("No such direction!");
        return false;
    }
    int shipLength = getShipLength(ship);

    if (shipLength == -1)
    {
        printError("The ship is not set");
        return false;
    }
    //be kell ferjen es uresek a helyek
    if (FitShip(x, y, ship, dir) && (!ShipStached(x, y, shipLength, dir)))
    {
        int xnew = x;
        int ynew = y;
        while (shipLength != 0)
        {
            SetMap(xnew, ynew, ship, true);
            this->HP++;
            switch (dir)
            {
            case 'N':
                xnew -= 1;
                break;
            case 'E':
                ynew += 1;
                break;
            case 'S':
                xnew += 1;
                break;
            case 'W':
                ynew -= 1;
                break;
            }
            shipLength--;
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool BattleMap::FitShip(int x, int y, char ship, char dir)
{
    //mar a kezdo koordinata nem jo
    if (!CoordinateExist(x, y))
    {
        return false;
    }
    int shipLength = getShipLength(ship);
    //felfele
    if (dir == 'N' && x - shipLength < -1)
    {
        printError("The ships stucks out to the North ");
        return false;
    }
    //jobbra
    if (dir == 'E' && y + shipLength > getMapWidth())
    {
        printError("The ships stucks out to the East ");
        return false;
    }
    //lefele
    if (dir == 'S' && x + shipLength > getMapHeight())
    {
        printError("The ships stucks out to the South ");
        return false;
    }
    //balra
    if (dir == 'W' && y - shipLength < -1)
    {
        printError("The ships stucks out to the West ");
        return false;
    }
    //ha eljut ide akkor a hajo be kell ferjen
    return true;
}

bool BattleMap::CoordinateExist(int x, int y)
{
    if (x < 0 || y < 0)
    {
        printError("Negative coordinate");
        return false;
    }
    if (x >= getMapHeight() || y >= getMapWidth())
    {
        printError("Coordinate is to big, top left is 0-0");
        return false;
    }
    return true;
}

float BattleMap::getRatio(){
    return (float)((this->hits/this->total)*100.0);
}

int BattleMap::Shoot(int x, int y, bool My)
{
    if (!CoordinateExist(x, y))
    {
        return 2;
    }
    char poz = getPosition(x, y, My);
    //already shot place
    if (poz == 'O' || poz == 'X')
    {
        return 2;
    }
    if (poz == ' ')
    { //MISS
        cout<<"MISS\n";
        total++;
        SetMap(x, y, 'X', My);
        return 0;
    }
    //HIT SHOMETHING
    if (poz == 'A' || poz == 'B'|| poz == 'C'|| poz == 'D')
    { 
        cout<<"HIT\n";
        total++;
        hits++;
        HP--;
        cout<<HP<<" "<<hits<<" "<<total<<endl;
        SetMap(x, y, 'O', My);
        if(HP == 0){
            return 3;
        }
        return 1;
    }
    cout<<"SOMETHING WENT WRONG, TRY AGAIN\n";
    return 2;
}

void BattleMap::printMap(bool my)
{
    if (my)
    {
        cout << "My Map" << endl;
    }
    else
    {
        cout << "Enemy Map" << endl;
    }

    cout << "    ";
    for (int i = 0; i < MapWidth; i++)
    {
        cout << i << "    ";
    }
    cout << endl;
    for (int i = -1; i < MapHeight * 2; i++)
    {
        //adatsor irasa
        if (i % 2 == 0)
        {
            cout << i / 2 << " | ";
            for (int j = 0; j < MapWidth; j++)
            {
                if (my)
                {
                    cout << MyMap[i / 2][j] << "  | ";
                }
                else
                {
                    cout << EnemyMap[i / 2][j] << "  | ";
                }
            }
            cout << endl;
        }
        //tablazat irasa
        else
        {
            cout << "  ";
            for (int j = 0; j < MapWidth * 5; j++)
            {
                cout << "-";
            }
            cout << endl;
        }
    }
}
