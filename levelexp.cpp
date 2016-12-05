#include "levelexp.h"
#include <math.h>
#include <iostream>

using namespace std;

LevelExp::LevelExp()
{
    lv = 0;
    exp = 0;
}

int LevelExp::getLevel()
{
    return lv;
}

int LevelExp::getExp()
{
    return exp;
}

int LevelExp::getExpNeed2NextLevel()
{
    return exp2LevelUp(lv+1);
}

int LevelExp::addExp(int e)
{
    exp+=e;
    int checkLevel = 0;
    bool isLevelUp = true;
    while(isLevelUp){
        int aimExp = exp2LevelUp(lv+1);
        if(exp>=aimExp){
            checkLevel++;
            isLevelUp = true;
            lv++;
            cout<<__FUNCTION__<<" LevelUp!!!"<<endl;
        }else{
            isLevelUp = false;
        }
    }
    return checkLevel;
}

float LevelExp::expPercent2LevelUp()
{
    float ae = exp2LevelUp(lv+1);
    float ce = exp2LevelUp(lv);
    return ((float)exp - ce)/(ae-ce);
}

int LevelExp::exp2LevelUp(int level)
{
    return floor((39+pow(level,0.9))*(level));
}
