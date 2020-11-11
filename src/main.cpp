#include <iostream>
#include "gameHeader.h"
#include "ColorChange.h"
#include <fstream>

using namespace std;

int main()
{
    /* TESTING */
/*
    ofstream fout;
    fout.open("test.txt");
    if (fout.fail())
    {
        cout << "FILE fail\n";
        return 1;
    }

    int heigth = 5;
    int width = 5;

    BattleMap MAP;
    BattleMap MAP1(heigth, width);

    fout << "TEST results\n";
    {
        fout << "getMapHeight()";

        if (MAP.getMapHeight() != 8)
        {
            fout << "FAIL\n";
        }
        else
        {
            fout << " SUCCESS\n";
        }
        fout << "getMapHeight()";
        if (MAP.getMapWidth() != 8)
        {
            fout << "FAIL\n";
        }
        else
        {
            fout << " SUCCESS\n";
        }

        fout << "getMapHeight()";
        if (MAP1.getMapHeight() != heigth)
        {
            fout << "FAIL\n";
        }
        else
        {
            fout << " SUCCESS\n";
        }
        fout << "getMapHeight()";
        if (MAP1.getMapWidth() != width)
        {
            fout << "FAIL\n";
        }
        else
        {
            fout << " SUCCESS\n";
        }
    }
    {
        fout << "SETMAP()/getmap() my: ";
        MAP1.SetMap(0, 0, 'z', true);
        MAP1.SetMap(0, 0, 'z', false);
        if (MAP1.getPosition(0, 0, true) == 'z')
        {
            fout << "Success\n";
        }
        else
        {
            fout << "Fail\n";
        }
        fout << "SETMAP()/getmap() enemy: ";
        if (MAP1.getPosition(0, 0, false) == 'z')
        {
            fout << "Success\n";
        }
        else
        {
            fout << "Fail\n";
        }
        MAP1.SetMap(0, 0, 0, true);
        MAP1.SetMap(0, 0, 0, false);
    }
    {
        fout << "CoordinateExist: correct ";
        if (MAP1.CoordinateExist(0, 0) == true)
        {
            fout << "Success\n";
        }
        else
        {
            fout << "Fail\n";
        }
        fout << "CoordinateExist: big heigth ";
        if (MAP1.CoordinateExist(heigth, 0) == true)
        {
            fout << "Fail\n";
        }
        else
        {
            fout << "Success\n";
        }
        fout << "CoordinateExist: big width ";
        if (MAP1.CoordinateExist(0, width) == true)
        {
            fout << "Fail\n";
        }
        else
        {
            fout << "Success\n";
        }
        fout << "CoordinateExist: big both ";
        if (MAP1.CoordinateExist(heigth, width) == true)
        {
            fout << "Fail\n";
        }
        else
        {
            fout << "Success\n";
        }
        fout << "CoordinateExist: negative ";
        if (MAP1.CoordinateExist(-1, 0) == true)
        {
            fout << "Fail\n";
        }
        else
        {
            fout << "Success\n";
        }
    }

    {
        fout << "FitShip: ";
        if (MAP1.FitShip(0, 0, 'A', 'N'))
        {
            fout << "Fail\n";
        }
        else
        {
            fout << "Success\n";
        }
        if (MAP1.FitShip(0, 0, 'A', 'W'))
        {
            fout << "Fail\n";
        }
        else
        {
            fout << "Success\n";
        }
        if (MAP1.FitShip(heigth - 1, 0, 'A', 'S'))
        {
            fout << "Fail\n";
        }
        else
        {
            fout << "Success\n";
        }
        if (MAP1.FitShip(0, width-1, 'A', 'E'))
        {
            fout << "Fail\n";
        }
        else
        {
            fout << "Success\n";
        }
    }

    fout.close();
*/
    MainMenu();

    return 0;
}
