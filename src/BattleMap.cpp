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
    if (Height < 4)
    {
        printError("tul kicsi a magassag, 4 lesz alkalmazva");
        this->MapHeight = 4;
    }
    else
        this->MapHeight = Height;
    if (Width < 4)
    {
        printError("tul kicsi a szelesseg, 4 lesz alkalmazva");
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

char BattleMap::getMyPosition(int x, int y)
{
    return MyMap[x][y];
}

char BattleMap::getEnemyPosition(int x, int y)
{
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
    else
    {
        printError("az adat nem kerult beirasra");
    }
}

bool BattleMap::ShipStached(int x, int y, int length, char dir)
{
    int xnew = x;
    int ynew = y;
    while (length != 0)
    {
        //ha nem szokoz akkor egy hajo van a koordinatan
        if (getMyPosition(xnew, ynew) != ' ')
        {
            printError("A hajok egymasra kerultek es a jelenlegi hajo nem kerult beirasra");
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
        printError("A hajo nem kerult beirasra");
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
        printError("A hajo kilog a palyarol eszakra: ");
        return false;
    }
    //jobbra
    if (dir == 'E' && y + shipLength > getMapWidth())
    {
        printError("A hajo kilog a palyarol keletre: ");
        return false;
    }
    //lefele
    if (dir == 'S' && x + shipLength > getMapHeight())
    {
        printError("A hajo kilog a palyarol delre: ");
        return false;
    }
    //balra
    if (dir == 'W' && y - shipLength < -1)
    {
        printError("A hajo kilog a palyarol nyugatra: ");
        return false;
    }
    //ha eljut ide akkor a hajo be kell ferjen
    return true;
}

bool BattleMap::CoordinateExist(int x, int y)
{
    if (x < 0 || y < 0)
    {
        printError("negativ koordinata kerult megadasra");
        return false;
    }
    if (x >= getMapHeight() || y >= getMapWidth())
    {
        printError("a koordinata tul nagy, a szamozas 0-tol indul, igy egy 8*8-as palya eseten max 7-est lehet megadni");
        return false;
    }
    return true;
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
