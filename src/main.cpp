#include <iostream>
#include "BattleMap.h"

using namespace std;

int main(){

    BattleMap Ures;
    
    //random shooting and ships, delete later
    Ures.SetMap(-5,0,'X');
    Ures.SetMap(1,1,'O');
    Ures.SetMap(0,1,'O');
    //random stuff end

    cout<<Ures;
    return 0;
}
