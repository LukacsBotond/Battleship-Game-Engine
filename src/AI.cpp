#include "BattleMap.h"
#include "ColorChange.h"
#include "gameHeader.h"
#include "AI.h"

AI::AI(int hight, int width, int ships[4], int AILevel)
{
    BattleMap(hight, width);
    this->ships[0] = ships[0];
    this->ships[1] = ships[1];
    this->ships[2] = ships[2];
    this->ships[3] = ships[3];
    this->AILevel = AILevel;
}

void AI::AIplaceShips()
{
    //turn off errors so when the AI randomly tries to place
    //ships it won't fill the screen with error messages when
    //it fails randomly
    errors = false;
    int width = getMapWidth();
    int heigth = getMapHeight();
    srand((unsigned)time(0));
    char shipType = 'D';
    char shipDir;

    for (int i = 0; i < 4; i++)
    {
        //there is no ship from that type
        if (ships[i] == 0)
        {
            shipType--;
            continue;
        }
        int dir = (rand() % 4);
        switch (dir)
        {
        case 0:
            shipDir = 'N';
            break;
        case 1:
            shipDir = 'E';
            break;
        case 2:
            shipDir = 'S';
            break;
        case 3:
            shipDir = 'W';
            break;

        default:
            cout << "NOT SUPPOSED TO REACH THIS\n";
            throw out_of_range("unknown ship direction");
            break;
        }
        for (int j = 0; j < ships[i]; j++)
        {
            //repeat till find a random space to the ship
            //on small maps with a lot of ship it may turn into an
            //infinite loop
            while (!SetShip((rand() % width), (rand() % heigth), shipType, shipDir))
                ;
        }
        shipType--;
    }

    //turn it back on for the user
    errors = true;
}

int AI::shootAI(BattleMap Player)
{
    switch (AILevel)
    {
    case 1:
        return shootEasy(Player);
        break;

    default:
        throw out_of_range("AI outside exepted range");
        break;
    }
}

int AI::shootEasy(BattleMap Player)
{
    cout<<"AI SHOOTING..."<<endl;

    srand(time(NULL));
    int ret = 2;
    int randHeight = 0;
    int randWidth = 0;
    while (ret == 2)
    {
        randHeight = rand() % MapHeight-1;
        randWidth = rand() % MapWidth-1;
        ret = BattleMap::Shoot(randHeight, randWidth, Player);
    }

    total++;
    if (ret == 0)
    {
        Player.SetMap(randHeight, randWidth, 'X', true);
    }
    else
    {
        hits++;
        Player.SetMap(randHeight, randWidth, 'O', true);
    }
    printMap(true);
    printMap(false);
    cout<<"AI done shooting..."<<endl;
    return ret;
}