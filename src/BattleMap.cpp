#include <iostream>
#include "BattleMap.h"

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
        cout << "tul kicsi a magassag, 4 lesz alkalmazva\n";
        this->MapHeight = 4;
    }
    else
        this->MapHeight = Height;
    if (Width < 4)
    {
        cout << "tul kicsi a szelesseg, 4 lesz alkalmazva\n";
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
            this->Map[i][j] = 0;
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

bool BattleMap::CoordinateExist(int x,int y){
    if(x<0 || y<0){
        cout<<"negativ koordinata kerult megadasra\n";
        return false;
    }
    if(x> getMapHeight()|| y>getMapWidth()){
        cout<<"a koordinata tul nagy, a szamozas 0-tol indul, igy egy 8*8-as palya eseten max 7-est lehet megadni\n";
        return false;
    }
    return true;
}

void BattleMap::SetMap(int x,int y,char data){
    if(CoordinateExist(x,y)){
        this->Map[x][y] = data;
        //cout<<Map[x][y]<< " ";
    }
    else{
        cout<<"az adat nem kerult beirasra\n";
    }
}

int BattleMap::getMapHeight(){
    return this->MapHeight;
}

int BattleMap::getMapWidth(){
    return this->MapWidth;
}

ostream &operator<<(ostream &os, const BattleMap &what)
{
    cout << "   ";
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
                os << what.Map[i/2][j] << "  | ";
            }
            os << endl;
        }
        //tablazat irasa
        else
        {
            cout << "   ";
            for (int j = 0; j < what.MapWidth * 5; j++)
            {
                os << "-";
            }
            os << endl;
        }
    }
}

