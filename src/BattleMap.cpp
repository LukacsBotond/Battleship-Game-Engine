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
        printError("Nincs inlyen jelzesu hajo a flottaban: " + errorShip);
        return -1;
    }
    return shipLength;
}

char BattleMap::getPosition(int x, int y)
{
    return Map[x][y];
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

bool BattleMap::ShipStached(int x, int y, int length, char dir)
{
    int xnew = x;
    int ynew = y;
    while (length != 0)
    {
        //ha nem szokoz akkor egy hajo van a koordinatan
        if (getPosition(xnew, ynew) != ' ')
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
            printError("Nincs ilyen irany");
            return false;
            break;
        }
        length--;
    }
    return false;
}

void BattleMap::SetShip(int x, int y, char ship, char dir)
{
    int shipLength = getShipLength(ship);

    if (shipLength == -1)
    {
        printError("A hajo nem kerult beirasra");
        return;
    }
    //be kell ferjen es uresek a helyek
    if (FitShip(x, y, ship, dir) && (!ShipStached(x, y, shipLength, dir)))
    {
        int xnew = x;
        int ynew = y;
        while (shipLength != 0)
        {
            SetMap(xnew,ynew,ship);
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
                printError("Nincs ilyen irany");
                break;
            }
            shipLength--;
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
