#include "BattleMap.h"
#include "ColorChange.h"
#include "gameHeader.h"
#include "AI.h"

void AI::AIplaceShips()
{
    //turn off errors so when the AI randomly tries to place
    //ships it won't fill the screen with error messages when
    //it fails randomly
    errors = false;
    int width = MapWidth;
    int heigth = MapHeight;
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
    cout << "initial AI state" << endl;
    printMap(true);

    //turn it back on for the user
    errors = true;
}

int AI::shootAI(BattleMap &Player)
{
    cout << "AI SHOOTING..." << endl;
    BattleMap *Player_p;
    Player_p = &Player;
    switch (AILevel)
    {
    case 1:
        int res;
        do
        {
            res = shootEasy(*Player_p);
            if (res == 0 || res == 3)
            {
                break;
            }
        } while (true);
        return res;
        break;

    case 2:
        return shootMedium(*Player_p);
        break;

    case 3:
    {
        errors = false;
        int ret = 2;
        do
        {
            ret = shootHard(*Player_p);
            if (ret == 0 || ret == 3)
            {
                break;
            }
        } while (true);
        errors = true;
        return ret;
        break;
    }
    default:
        throw out_of_range("AI outside exepted range");
        break;
    }
}

int AI::shootEasy(BattleMap &Player)
{
    BattleMap *Player_p;
    Player_p = &Player;
    COORDINATE tmp;
    if (hitCoordinates.empty())
    {
        tmp.x = 0;
        tmp.y = 0;
        hitCoordinates.push_back(tmp);
        return BattleMap::Shoot(0, 0, *Player_p);
    }
    else
    {
        tmp = hitCoordinates.front();
        hitCoordinates.pop_front();
        //chessboard pattern
        if (tmp.y + 1 >= this->MapWidth)
        {
            tmp.y = 0;
            tmp.x++;
        }
        else
        {
            tmp.y += 1;
        }
        hitCoordinates.push_back(tmp);
        return BattleMap::Shoot(tmp.x, tmp.y, *Player_p);
    }
}

int AI::shootMedium(BattleMap &Player)
{
    srand(time(NULL));
    int ret = 2;
    int randHeight = 0;
    int randWidth = 0;
    BattleMap *Player_p;
    Player_p = &Player;
    do
    {
        randHeight = rand() % (MapHeight);
        randWidth = rand() % (MapWidth);
        ret = BattleMap::Shoot(randHeight, randWidth, *Player_p);
        if (ret == 0 || ret == 3)
        {
            break;
        }
    } while (true);
    cout << "AI done shooting..." << endl;
    return ret;
}

int AI::shootAround(BattleMap &Player)
{
    COORDINATE tmp;
    BattleMap *Player_p;
    Player_p = &Player;
    //a ship was hit and not cleared around it
    tmp = hitCoordinates.front();
    //ship or miss shot
    int ret = BattleMap::Shoot(tmp.x - 1, tmp.y, *Player_p);
    if (ret != 2)
    {
        if (ret == 1)
        {
            pushCoordinate(tmp.x - 1, tmp.y);
        }
        return ret;
    }
    ret = BattleMap::Shoot(tmp.x + 1, tmp.y, *Player_p);
    if (ret != 2)
    {
        if (ret == 1)
        {
            pushCoordinate(tmp.x + 1, tmp.y);
        }
        return ret;
    }
    ret = BattleMap::Shoot(tmp.x, tmp.y - 1, *Player_p);
    if (ret != 2)
    {
        if (ret == 1)
        {
            pushCoordinate(tmp.x, tmp.y - 1);
        }
        return ret;
    }
    ret = BattleMap::Shoot(tmp.x, tmp.y + 1, *Player_p);
    if (ret != 2)
    {
        if (ret == 1)
        {
            pushCoordinate(tmp.x, tmp.y + 1);
        }

        return ret;
    }

    return -1;
}

int AI::shootHard(BattleMap &Player)
{
    int ret = 2;
    int randHeight = 0;
    int randWidth = 0;
    BattleMap *Player_p;
    Player_p = &Player;
    //if there wasn't a ship hit and not cleared around
    //it then shoot randomly
    if (hitCoordinates.empty())
    {
        while (ret == 2)
        {
            randHeight = rand() % (MapHeight);
            randWidth = rand() % (MapWidth);

            if (hole(randHeight, randWidth))
            { //lik
                continue;
            }

            ret = BattleMap::Shoot(randHeight, randWidth, *Player_p);
        }
        //hit something, add it to the list
        if (ret == 1)
        {
            pushCoordinate(randHeight, randWidth);
        }
        return ret;
    }
    else
    {
        while (true)
        {
            ret = shootAround(*Player_p);
            if(ret == 0 || ret == 3){//miss or win
                cout << "AI done shooting..." << endl;
                return ret;
            }
            if(ret == -1 && !hitCoordinates.empty()){//still can shoot
                hitCoordinates.pop_front();
            }
        } 
    }
    return ret;
}

void AI::pushCoordinate(int x, int y)
{
    COORDINATE tmp;
    tmp.x = x;
    tmp.y = y;
    hitCoordinates.push_back(tmp);
}

bool AI::hole(int x, int y)
{
    if (x != 0)
    {
        if (this->EnemyMap[x - 1][y] == ' ')
        {
            return false;
        }
    }
    if (x != MapHeight - 1)
    {
        if (this->EnemyMap[x + 1][y] == ' ')
        {
            return false;
        }
    }

    if (y != 0)
    {
        if (this->EnemyMap[x][y - 1] == ' ')
        {
            return false;
        }
    }
    if (y != MapHeight - 1)
    {
        if (this->EnemyMap[x][y + 1] == ' ')
        {
            return false;
        }
    }

    return true;
}