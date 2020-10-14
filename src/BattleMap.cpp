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
    this->Map = new char *[MapHeight];
    for (int i = 0; i < MapHeight; i++)
    {
        this->Map[i] = new char[MapWidth];
    }
    //ne legyen benne semmi
    for (int i = 0; i < MapHeight; i++)
    {
        for (int j = 0; j < MapWidth; j++)
        {
            this->Map[i][j] = ' ';
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
    this->Map = new char *[MapHeight];
    for (int i = 0; i < MapHeight; i++)
    {
        this->Map[i] = new char[MapWidth];
    }
    //ne legyen benne semmi

    for (int i = 0; i < MapHeight; i++)
    {
        for (int j = 0; j < MapWidth; j++)
        {
            this->Map[i][j] = ' ';
        }
    }
}

BattleMap::~BattleMap()
{
    for (int i = 0; i < MapHeight; i++)
    {
        delete[] this->Map[i];
    }
    delete[] this->Map;
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

void BattleMap::SetMap(int x, int y, char data)
{
    if (CoordinateExist(x, y))
    {
        this->Map[x][y] = data;
    }
    else
    {
        printError("az adat nem kerult beirasra");
    }
}

void BattleMap::SetShip(int x, int y, char ship, char dir)
{
    int shipLength = (ship - 'F') * -1;
    if (FitShip(x, y, ship, dir))
    {
        for (int i = 0; i < shipLength; i++)
        {
            if (dir == 'N')
            {
                SetMap(x - i, y, ship);
            }
            if (dir == 'E')
            {
                SetMap(x, y + i, ship);
            }
            if (dir == 'S')
            {
                SetMap(x + i, y, ship);
            }
            if (dir == 'W')
            {
                SetMap(x, y - 1, ship);
            }
        }
    }
}

bool BattleMap::FitShip(int x, int y, char ship, char dir)
{
    //mar a kezdo koordinata nem jo
    if (!CoordinateExist(x, y))
    {
        return false;
    }
    int shipLength = (ship - 'F') * -1;
    //nincs ilyen hajo
    if (shipLength < 2 || shipLength > 5)
    {
        string error(1, ship);
        printError("Nincs inlyen jelzesu hajo a flottaban: " + error);
        return false;
    }
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

int BattleMap::getMapHeight()
{
    return this->MapHeight;
}

int BattleMap::getMapWidth()
{
    return this->MapWidth;
}

ostream &operator<<(ostream &os, const BattleMap &what)
{
    cout << "    ";
    for (int i = 0; i < what.MapWidth; i++)
    {
        cout << i << "    ";
    }
    cout << endl;
    for (int i = -1; i < what.MapHeight * 2; i++)
    {
        //adatsor irasa
        if (i % 2 == 0)
        {
            os << i / 2 << " | ";
            for (int j = 0; j < what.MapWidth; j++)
            {
                os << what.Map[i / 2][j] << "  | ";
            }
            os << endl;
        }
        //tablazat irasa
        else
        {
            cout << "  ";
            for (int j = 0; j < what.MapWidth * 5; j++)
            {
                os << "-";
            }
            os << endl;
        }
    }
}

void BattleMap::printError(string error)
{
    printred(error);
}
