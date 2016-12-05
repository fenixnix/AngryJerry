#ifndef LEVELEXP_H
#define LEVELEXP_H

class LevelExp
{
public:
    LevelExp();
    int getLevel();
    int getExp();
    int getExpNeed2NextLevel();
    int addExp(int e);
    virtual float expPercent2LevelUp();
    static int exp2LevelUp(int level);
private:
    int lv;
    int exp;
};

#endif // LEVELEXP_H
