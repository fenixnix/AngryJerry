#ifndef UNITSHOOTER_H
#define UNITSHOOTER_H

#include "unit.h"

class UnitShooter : public Unit
{
public:
    UnitShooter();
    void update();
    void draw();
    void signalDie();
};

#endif // UNITSHOOTER_H
