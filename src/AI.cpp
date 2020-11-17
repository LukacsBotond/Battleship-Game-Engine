#include "BattleMap.h"
#include "ColorChange.h"
#include "gameHeader.h"
#include "AI.h"

AI::AI(int hight, int width, int ships[4], int AILevel)
{
    BattleMap(hight, width);
    NrDestroyer = ships[0];
    NrCruiser = ships[1];
    NrBattleship = ships[2];
    NrAircraftCarrier = ships[3];
    this->AILevel = AILevel;
}

void AI::placeShips()
{
    //turn off errors so when the AI randomly tries to place
    //ships it won't fill the screen with error messages when
    //it fails randomly
    errors = false;
    int width = getMapWidth();
    int heigth = getMapHeight();

    

    //turn it back on for the user
    errors = true;
}